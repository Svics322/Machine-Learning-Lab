#include "DigitClassifier.h"

namespace app
{
    DigitClassifier::DigitClassifier(const AppConfig& config)
        : config(config)
    {
        arma::arma_rng::set_seed(123);
        BuildModel();
    }

    void DigitClassifier::BuildModel()
    {
        model.Add<mlpack::ann::Linear>(config.hiddenNeurons);
        model.Add<mlpack::ann::ReLU>();

        if (config.useSecondHiddenLayer)
        {
            model.Add<mlpack::ann::Linear>(config.secondHiddenNeurons);
            model.Add<mlpack::ann::ReLU>();
        }

        model.Add<mlpack::ann::Linear>(config.classes);
        model.Add<mlpack::ann::LogSoftMax>();
    }

    void DigitClassifier::Train(const arma::mat& trainX, const arma::mat& trainLabels)
    {
        const std::size_t maxIterations =
            config.epochs * (trainX.n_cols / config.batchSize);

        ens::Adam optimizer(
            config.learningRate,
            config.batchSize,
            0.9,
            0.999,
            1e-8,
            maxIterations,
            1e-8,
            true
        );

        model.Train(trainX, trainLabels, optimizer);
    }

    arma::mat DigitClassifier::Predict(const arma::mat& testX)
    {
        arma::mat predictions;
        model.Predict(testX, predictions);
        return predictions;
    }

    std::string DigitClassifier::GetArchitectureDescription() const
    {
        std::ostringstream oss;

        oss << config.inputSize
            << " -> "
            << config.hiddenNeurons
            << " ReLU";

        if (config.useSecondHiddenLayer)
        {
            oss << " -> "
                << config.secondHiddenNeurons
                << " ReLU";
        }

        oss << " -> "
            << config.classes
            << " LogSoftMax";

        return oss.str();
    }
}