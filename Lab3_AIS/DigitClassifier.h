#pragma once

#include "AppConfig.h"

#include <mlpack.hpp>
#include <mlpack/methods/ann/ffn.hpp>
#include <string>

namespace app
{
    class DigitClassifier
    {
    public:
        explicit DigitClassifier(const AppConfig& config);

        void Train(const arma::mat& trainX, const arma::mat& trainLabels);
        arma::mat Predict(const arma::mat& testX);

        std::string GetArchitectureDescription() const;

    private:
        AppConfig config;

        mlpack::ann::FFN<
            mlpack::ann::NegativeLogLikelihood,
            mlpack::ann::RandomInitialization
        > model;

        void BuildModel();
    };
}