#include "Logger.hpp"

int main() {
    Logger::GetInstance().Log("Application started.", LogLevel::Debug);

    Logger::GetInstance().SetLogLevel(LogLevel::Warning);

    Logger::GetInstance().Log("Info message.", LogLevel::Info);
    Logger::GetInstance().Log("Debug message.", LogLevel::Debug);
    Logger::GetInstance().Log("Warning message.", LogLevel::Warning);
    Logger::GetInstance().Log("Error message.", LogLevel::Error);
    Logger::GetInstance().Log("Fatal message.", LogLevel::Fatal);

    Logger::GetInstance().SetConsoleOutput(false);
    Logger::GetInstance().Log("This should not be printed on console.");

    Logger::GetInstance().SetFileOutput(false);
    Logger::GetInstance().Log("This should not be written to file.");

    return 0;
}