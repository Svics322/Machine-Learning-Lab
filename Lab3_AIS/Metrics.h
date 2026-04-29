#pragma once

#include <armadillo>
#include <cstddef>

namespace app
{
    class Metrics
    {
    public:
        static double Accuracy(const arma::mat& predictions,
            const arma::mat& expectedLabels,
            std::size_t& correct);

        static void PrintPredictionTable(const arma::mat& predictions,
            const arma::mat& expectedLabels,
            std::size_t count);

        static void PrintAsciiDigit(const arma::vec& image);

        static void PrintFirstMistake(const arma::mat& testX,
            const arma::mat& expectedLabels,
            const arma::mat& predictions);
    };
}