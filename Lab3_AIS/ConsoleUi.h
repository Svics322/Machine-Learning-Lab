#pragma once

#include <string>
#include "AppConfig.h"

namespace app
{
    class ConsoleUi
    {
    public:
        static void SetupUtf8Console();
        static void PrintHeader();
        static void PrintConfig(const AppConfig& config);
        static void PrintError(const std::string& message);
        static void PrintStage(const std::string& message);
        static void PrintSuccess(const std::string& message);
    };
}
