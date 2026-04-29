#pragma once

#include <armadillo>
#include <string>
#include <cstddef>

namespace app
{
    struct MnistDataset
    {
        arma::mat features;
        arma::mat labels;
    };

    class MnistCsvLoader
    {
    public:
        static bool Load(const std::string& fileName,
            std::size_t limit,
            MnistDataset& output);

    private:
        static bool IsNumber(const std::string& value);
    };
}
