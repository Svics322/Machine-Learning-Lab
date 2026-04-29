#include "Metrics.h"

#include <iostream>
#include <iomanip>

namespace app
{
    double Metrics::Accuracy(const arma::mat& predictions,
        const arma::mat& expectedLabels,
        std::size_t& correct)
    {
        correct = 0;

        for (std::size_t i = 0; i < predictions.n_cols; i++)
        {
            const arma::uword predictedClass = predictions.col(i).index_max();
            const std::size_t expectedClass = static_cast<std::size_t>(expectedLabels(0, i));

            if (predictedClass == expectedClass)
                correct++;
        }

        return static_cast<double>(correct) / predictions.n_cols * 100.0;
    }

    void Metrics::PrintPredictionTable(const arma::mat& predictions,
        const arma::mat& expectedLabels,
        std::size_t count)
    {
        std::cout << "\nПерші " << count << " прогнозів:\n";
        std::cout << "№    | Очікувана цифра | Прогноз мережі\n";
        std::cout << "---------------------------------------\n";

        const std::size_t rows = std::min<std::size_t>(count, predictions.n_cols);

        for (std::size_t i = 0; i < rows; i++)
        {
            const arma::uword predictedClass = predictions.col(i).index_max();
            const std::size_t expectedClass = static_cast<std::size_t>(expectedLabels(0, i));

            std::cout << std::setw(4) << i
                << " | "
                << std::setw(15) << expectedClass
                << " | "
                << std::setw(13) << predictedClass
                << "\n";
        }
    }

    void Metrics::PrintFirstMistake(const arma::mat& testX,
        const arma::mat& expectedLabels,
        const arma::mat& predictions)
    {
        for (std::size_t i = 0; i < predictions.n_cols; i++)
        {
            const arma::uword predictedClass = predictions.col(i).index_max();
            const std::size_t expectedClass = static_cast<std::size_t>(expectedLabels(0, i));

            if (predictedClass != expectedClass)
            {
                std::cout << "\nПерша знайдена помилка мережі:\n";
                std::cout << "Індекс прикладу: " << i << "\n";
                std::cout << "Очікувана цифра: " << expectedClass << "\n";
                std::cout << "Прогноз мережі: " << predictedClass << "\n";

                std::cout << "\nASCII-перегляд зображення з помилкою:\n";
                Metrics::PrintAsciiDigit(testX.col(i));

                return;
            }
        }

        std::cout << "\nНа перевірених прикладах помилок не знайдено.\n";
    }

    void Metrics::PrintAsciiDigit(const arma::vec& image)
    {
        for (std::size_t row = 0; row < 28; row++)
        {
            for (std::size_t col = 0; col < 28; col++)
            {
                const double pixel = image(row * 28 + col);

                if (pixel > 0.75)
                    std::cout << "#";
                else if (pixel > 0.45)
                    std::cout << "*";
                else if (pixel > 0.20)
                    std::cout << ".";
                else
                    std::cout << " ";
            }

            std::cout << "\n";
        }
    }
}