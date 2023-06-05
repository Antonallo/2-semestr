#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

enum class LogLevel {
    All = 0,
    Info = 1,
    Debug = 2,
    Warning = 3,
    Error = 4,
    Fatal = 5,
    Off = 6
};

class Logger {
public:
    static Logger& GetInstance() { // метод получени€ ссылки на экземпл€р класса
        static Logger instance;
        return instance;
    }

    // ћетоды изменени€ параметров логировани€
    void SetConsoleOutput(bool state) { m_IsConsoleOutputEnabled = state; }
    void SetFileOutput(bool state) { m_IsFileOutputEnabled = state; }
    void SetLogLevel(LogLevel level) { m_LogLevel = level; }

    // ћетод логировани€ сообщений в файл и/или на консоль
    void Log(const std::string& message, const LogLevel level = LogLevel::Info) {
        if (level >= m_LogLevel) { // если уровень логировани€ больше или равен текущему уровню логировани€
            std::string logLevelString;

            switch (level) {
            case LogLevel::Info:
                logLevelString = "[INFO]";
                break;
            case LogLevel::Debug:
                logLevelString = "[DEBUG]";
                break;
            case LogLevel::Warning:
                logLevelString = "[WARNING]";
                break;
            case LogLevel::Error:
                logLevelString = "[ERROR]";
                break;
            case LogLevel::Fatal:
                logLevelString = "[FATAL]";
                break;
            default:
                logLevelString = "[UNKNOWN]";
                break;
            }

            std::time_t time = std::time(nullptr); // получаем текущее врем€
            std::string timeString = std::ctime(&time); // преобразуем его в строку
            timeString.pop_back(); // удал€ем завершающий символ переноса строки

            // выводим лог в файл, если включена соответствующа€ опци€
            if (m_IsFileOutputEnabled) {
                std::ofstream file("log.txt", std::ios_base::app);
                file << logLevelString << " [" << timeString << "] " << message << '\n';
            }

            // выводим лог на консоль, если включена соответствующа€ опци€
            if (m_IsConsoleOutputEnabled) {
                std::cout << logLevelString << " [" << timeString << "] " << message << '\n';
            }
        }
    }

private:
    bool m_IsConsoleOutputEnabled = true; // вывод логов на консоль включен по умолчанию
    bool m_IsFileOutputEnabled = true; // вывод логов в файл включен по умолчанию
    LogLevel m_LogLevel = LogLevel::Info; // текущий уровень логировани€

    Logger() {}
};