#include <iostream>
#include <fstream>
#include <string>
#include <memory>
using namespace std;

class Logger {
public:
    virtual void log(const string& msg) = 0;
    virtual ~Logger() = default;
};

class ConsoleLogger : public Logger {
public:
    void log(const string& msg) override {
        cout << "[CONSOLE] " << msg << endl;
    }
};

class FileLogger : public Logger {
    ofstream file;
public:
    FileLogger() {
        file.open("app.log", ios::app);
    }
    void log(const string& msg) override {
        file << "[FILE] " << msg << endl;
    }
    ~FileLogger() {
        file.close();
    }
};

class NullLogger : public Logger {
public:
    void log(const string& msg) override {
    }
};

class LoggerFactory {
public:
    virtual unique_ptr<Logger> createLogger() = 0;
    virtual ~LoggerFactory() = default;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    unique_ptr<Logger> createLogger() override {
        return make_unique<ConsoleLogger>();
    }
};

class FileLoggerFactory : public LoggerFactory {
public:
    unique_ptr<Logger> createLogger() override {
        return make_unique<FileLogger>();
    }
};

class NullLoggerFactory : public LoggerFactory {
public:
    unique_ptr<Logger> createLogger() override {
        return make_unique<NullLogger>();
    }
};

class Application {
    unique_ptr<Logger> logger;
public:
    Application(unique_ptr<LoggerFactory> factory) {
        logger = factory->createLogger();
    }

    void run() {
        logger->log("Application started");
        logger->log("Doing some work...");
        logger->log("Application finished");
    }
};

int main() {
    cout << "console" << endl;
    Application app1(make_unique<ConsoleLoggerFactory>());
    app1.run();

    cout << "infile" << endl;
    Application app2(make_unique<FileLoggerFactory>());
    app2.run();
    cout << "(записано в app.log)" << endl;

    cout << "dont work" << endl;
    Application app3(make_unique<NullLoggerFactory>());
    app3.run();
    cout << "(ничего не вывелось)" << endl;

    return 0;
}