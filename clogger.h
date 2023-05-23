#ifndef CLOGGER_H
#define CLOGGER_H
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

#define LOG_FILE_NAME "message"
#define MAX_FILE_SIZE 1024*1024
#define MAX_BACKUP_FILES 5

// Log levels
enum class LogLevel {
    ALL,
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filename, int maxFileSize, int maxBackupFiles)
        : filename_(filename),
        maxFileSize_(maxFileSize),
        maxBackupFiles_(maxBackupFiles) {}

    void Log(LogLevel level, std::string function, const int lineNumber, const char *format, ...) {
        // Get current timestamp
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::asctime(std::localtime(&now));
        timestamp.pop_back();  // Remove trailing newline character

        // Format log entry
        std::string logEntry = "[" + timestamp + "] ";

        switch (level) {
        case LogLevel::DEBUG:
            logEntry += "[DEBUG] ";
            break;
        case LogLevel::INFO:
            logEntry += "[INFO] ";
            break;
        case LogLevel::WARNING:
            logEntry += "[WARNING] ";
            break;
        case LogLevel::ERROR:
            logEntry += "[ERROR] ";
            break;
        }
        logEntry += function + " (" +std::to_string(lineNumber) + ") : ";

        char message[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);

        logEntry += message;

        // Output to console
        std::cout << logEntry << std::endl;

        // Output to log file
        WriteToFile(logEntry);
    }

    static Logger& GetInstance() {
        return instance;
    }

private:
    std::string filename_;
    int maxFileSize_;
    int maxBackupFiles_;
    std::ofstream fileStream_;

    static Logger instance;

    void WriteToFile(const std::string& message) {
        // Check if the file is already open
        if (!fileStream_.is_open()) {
            fileStream_.open(filename_, std::ios::out | std::ios::app);
        }

        // Check if the file is successfully opened
        if (fileStream_.is_open()) {
            // Rotate log file if it exceeds the maximum file size
            if (fileStream_.tellp() > maxFileSize_) {
                fileStream_.close();
                RotateFiles();
                fileStream_.open(filename_, std::ios::out | std::ios::app);
            }

            // Write to the log file
            fileStream_ << message << std::endl;
        }
    }

    void RotateFiles() {
        // Delete the oldest log file if the maximum number of backup files is reached
        std::string oldestFile = filename_ + "." + std::to_string(maxBackupFiles_);
        remove(oldestFile.c_str());

        // Rename existing log files
        for (int i = maxBackupFiles_ - 1; i >= 1; --i) {
            std::string currentFile = filename_ + "." + std::to_string(i);
            std::string newFile = filename_ + "." + std::to_string(i + 1);
            rename(currentFile.c_str(), newFile.c_str());
        }

        // Rename the current log file to .1
        rename(filename_.c_str(), (filename_ + ".1").c_str());
    }
};

// Define macros for log levels
#define LOG_DEBUG(format, ...) Logger::GetInstance().Log(LogLevel::DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) Logger::GetInstance().Log(LogLevel::INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) Logger::GetInstance().Log(LogLevel::WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) Logger::GetInstance().Log(LogLevel::ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)


#include <fstream>
#include <string>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QComboBox>
#include <QVBoxLayout>

class FileDisplayer : public QDialog {
    Q_OBJECT

public:
    FileDisplayer(const std::string& filename = LOG_FILE_NAME, QWidget* parent = nullptr)
        : QDialog(parent), filename_(filename) {
        InitializeUI();
        LoadLogFileContent();
    }

private slots:
    void FilterLogEntries(int index) {
        LogLevel filterLevel = static_cast<LogLevel>(index);
        ApplyLogFilter(filterLevel);
    }

private:
    std::string filename_;
    QPlainTextEdit* textEdit_;
    QComboBox* filterComboBox_;

    void InitializeUI() {
        textEdit_ = new QPlainTextEdit(this);
        textEdit_->setReadOnly(true);

        filterComboBox_ = new QComboBox(this);
        filterComboBox_->addItem("All");
        filterComboBox_->addItem("DEBUG");
        filterComboBox_->addItem("INFO");
        filterComboBox_->addItem("WARNING");
        filterComboBox_->addItem("ERROR");
        connect(filterComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &FileDisplayer::FilterLogEntries);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(filterComboBox_);
        layout->addWidget(textEdit_);
        this->resize(600,400);

        setLayout(layout);
    }

    void LoadLogFileContent() {
        QFile file(QString::fromStdString(filename_));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "Failed to open the log file.");
            return;
        }

        QTextStream in(&file);
        QString content = in.readAll();

        textEdit_->setPlainText(content);
        file.close();
    }

    void ApplyLogFilter(LogLevel filterLevel) {
        LoadLogFileContent();
        QString filterText = filterComboBox_->currentText();
        QString content = textEdit_->toPlainText();

        QStringList logEntries = content.split('\n');
        QStringList filteredEntries;

        for (const QString& entry : logEntries) {
            if (entry.trimmed().isEmpty()) {
                continue;
            }

            QString logLevelString = entry.section(']', 1, 1).trimmed().remove('[').remove(']');
            LogLevel entryLevel = LogLevelFromString(logLevelString);

            if (entryLevel >= filterLevel || filterLevel == LogLevel::ALL) {
                filteredEntries.append(entry.trimmed());
            }
        }

        content = filteredEntries.join("\n");
        textEdit_->setPlainText(content);
    }

    LogLevel LogLevelFromString(const QString& logLevelString) {
        if (logLevelString == "DEBUG") {
            return LogLevel::DEBUG;
        } else if (logLevelString == "INFO") {
            return LogLevel::INFO;
        } else if (logLevelString == "WARNING") {
            return LogLevel::WARNING;
        } else if (logLevelString == "ERROR") {
            return LogLevel::ERROR;
        }

        // Default to LogLevel::ALL if the log level string is unknown
        return LogLevel::ALL;
    }

};

#endif // CLOGGER_H
