#include "ConsoleUi.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace app
{
    void ConsoleUi::SetupUtf8Console()
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
    }

    void ConsoleUi::PrintHeader()
    {
        std::cout << "============================================================\n";
        std::cout << " Лабораторна робота: навчання нейронної мережі\n";
        std::cout << " Бібліотека: mlpack | Мова: C++ | Набір даних: MNIST\n";
        std::cout << "============================================================\n\n";
    }

    void ConsoleUi::PrintConfig(const AppConfig& config)
    {
        std::cout << "Параметри запуску:\n";
        std::cout << "  Навчальний файл: " << config.trainFile << "\n";
        std::cout << "  Тестовий файл:   " << config.testFile << "\n";
        std::cout << "  Навчальних прикладів: " << config.trainLimit << "\n";
        std::cout << "  Тестових прикладів:   " << config.testLimit << "\n";
        std::cout << "  Архітектура: 784 -> " << config.hiddenNeurons << " -> 10\n";
        std::cout << "  Епохи: " << config.epochs << "\n";
        std::cout << "  Batch size: " << config.batchSize << "\n\n";
    }

    void ConsoleUi::PrintError(const std::string& message)
    {
        std::cout << "[Помилка] " << message << "\n";
    }

    void ConsoleUi::PrintStage(const std::string& message)
    {
        std::cout << "\n[Етап] " << message << "\n";
    }

    void ConsoleUi::PrintSuccess(const std::string& message)
    {
        std::cout << "[Готово] " << message << "\n";
    }
}
