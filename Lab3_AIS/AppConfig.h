#pragma once

#include <string>
#include <cstddef>

namespace app
{
    struct AppConfig
    {
        std::string trainFile = "mnist_train.csv";
        std::string testFile = "mnist_test.csv";

        std::size_t trainLimit = 100'000;
        std::size_t testLimit = 5000;

        std::size_t inputSize = 784;
        std::size_t hiddenNeurons = 128;
        std::size_t secondHiddenNeurons = 64;
        bool useSecondHiddenLayer = true;

        std::size_t classes = 10;

        std::size_t epochs = 10;
        std::size_t batchSize = 32;

        double learningRate = 0.001;
    };
}