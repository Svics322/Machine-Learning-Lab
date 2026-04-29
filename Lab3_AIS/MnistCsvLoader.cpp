#include "MnistCsvLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

namespace app
{
    bool MnistCsvLoader::IsNumber(const std::string& value)
    {
        if (value.empty())
            return false;

        for (char ch : value)
        {
            if (!std::isdigit(static_cast<unsigned char>(ch)))
                return false;
        }

        return true;
    }

    bool MnistCsvLoader::Load(const std::string& fileName,
        std::size_t limit,
        MnistDataset& output)
    {
        constexpr std::size_t imageSize = 784;

        std::ifstream file(fileName);

        if (!file.is_open())
        {
            std::cout << "Не вдалося відкрити файл: " << fileName << "\n";
            return false;
        }

        output.features.set_size(imageSize, limit);
        output.labels.set_size(1, limit);

        std::string line;
        std::size_t column = 0;

        while (std::getline(file, line) && column < limit)
        {
            std::stringstream ss(line);
            std::string token;

            if (!std::getline(ss, token, ','))
                continue;

            if (!IsNumber(token))
                continue;

            const std::size_t label = static_cast<std::size_t>(std::stoul(token));

            if (label > 9)
                continue;

            output.labels(0, column) = static_cast<double>(label);

            for (std::size_t pixel = 0; pixel < imageSize; pixel++)
            {
                if (!std::getline(ss, token, ','))
                {
                    std::cout << "Некоректний рядок у файлі: " << fileName << "\n";
                    return false;
                }

                output.features(pixel, column) = std::stod(token) / 255.0;
            }

            column++;
        }

        if (column == 0)
        {
            std::cout << "Файл не містить коректних даних: " << fileName << "\n";
            return false;
        }

        output.features = output.features.cols(0, column - 1);
        output.labels = output.labels.cols(0, column - 1);

        std::cout << "Завантажено " << column << " прикладів із файлу " << fileName << "\n";
        return true;
    }
}