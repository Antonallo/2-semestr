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
    static Logger& GetInstance() { // ����� ��������� ������ �� ��������� ������
        static Logger instance;
        return instance;
    }

    // ������ ��������� ���������� �����������
    void SetConsoleOutput(bool state) { m_IsConsoleOutputEnabled = state; }
    void SetFileOutput(bool state) { m_IsFileOutputEnabled = state; }
    void SetLogLevel(LogLevel level) { m_LogLevel = level; }

    // ����� ����������� ��������� � ���� �/��� �� �������
    void Log(const std::string& message, const LogLevel level = LogLevel::Info) {
        if (level >= m_LogLevel) { // ���� ������� ����������� ������ ��� ����� �������� ������ �����������
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

            std::time_t time = std::time(nullptr); // �������� ������� �����
            std::string timeString = std::ctime(&time); // ����������� ��� � ������
            timeString.pop_back(); // ������� ����������� ������ �������� ������

            // ������� ��� � ����, ���� �������� ��������������� �����
            if (m_IsFileOutputEnabled) {
                std::ofstream file("log.txt", std::ios_base::app);
                file << logLevelString << " [" << timeString << "] " << message << '\n';
            }

            // ������� ��� �� �������, ���� �������� ��������������� �����
            if (m_IsConsoleOutputEnabled) {
                std::cout << logLevelString << " [" << timeString << "] " << message << '\n';
            }
        }
    }

private:
    bool m_IsConsoleOutputEnabled = true; // ����� ����� �� ������� ������� �� ���������
    bool m_IsFileOutputEnabled = true; // ����� ����� � ���� ������� �� ���������
    LogLevel m_LogLevel = LogLevel::Info; // ������� ������� �����������

    Logger() {}
};