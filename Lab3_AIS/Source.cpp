#pragma warning(disable: 4996)

#include "AppConfig.h"
#include "ConsoleUi.h"
#include "MnistCsvLoader.h"
#include "DigitClassifier.h"
#include "Metrics.h"

#include <iostream>
#include <iomanip>

int main()
{
    app::ConsoleUi::SetupUtf8Console();
    app::ConsoleUi::PrintHeader();

    app::AppConfig config;
    app::ConsoleUi::PrintConfig(config);

    app::MnistDataset trainData;
    app::MnistDataset testData;

    app::ConsoleUi::PrintStage("Завантаження навчальної вибірки");
    if (!app::MnistCsvLoader::Load(config.trainFile, config.trainLimit, trainData))
    {
        app::ConsoleUi::PrintError("Навчальні дані не завантажено.");
        return 1;
    }

    app::ConsoleUi::PrintStage("Завантаження тестової вибірки");
    if (!app::MnistCsvLoader::Load(config.testFile, config.testLimit, testData))
    {
        app::ConsoleUi::PrintError("Тестові дані не завантажено.");
        return 1;
    }

    app::ConsoleUi::PrintStage("Побудова нейронної мережі");

    app::DigitClassifier classifier(config);

    app::ConsoleUi::PrintSuccess(
        "Модель створено: " + classifier.GetArchitectureDescription()
    );

    app::ConsoleUi::PrintStage("Навчання нейронної мережі");
    classifier.Train(trainData.features, trainData.labels);
    app::ConsoleUi::PrintSuccess("Навчання завершено.");

    app::ConsoleUi::PrintStage("Оцінювання на тестових даних");
    arma::mat predictions = classifier.Predict(testData.features);

    std::size_t correct = 0;
    const double accuracy = app::Metrics::Accuracy(predictions, testData.labels, correct);

    std::cout << "\nПравильних прогнозів: "
        << correct << " / " << predictions.n_cols << "\n";

    std::cout << "Точність: "
        << std::fixed << std::setprecision(2)
        << accuracy << "%\n";

    app::Metrics::PrintPredictionTable(predictions, testData.labels, 10);

    std::cout << "\nASCII-перегляд першої тестової цифри:\n";
    app::Metrics::PrintAsciiDigit(testData.features.col(0));

    app::Metrics::PrintFirstMistake(
        testData.features,
        testData.labels,
        predictions
    );

    return 0;
}