//
//  main.cpp
//  29_Inheritance_Practice_3
//
//  Created by 세광 on 2021/07/23.
//

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

enum LogLevels {
    DEBUGING,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

const char* const LEVEL_HEADINGS[] = {
    "DEBUGING", "INFO", "WARNING", "ERROR", "FATAL"
};

class Logger {
public:
    Logger(int minLevel) : minLevel(minLevel) {}
    virtual ~Logger() {}
    
    void Log(const string &s, int level) {
        if (level >= minLevel) {
            doLogJob(s, level);
        }
    }
    
    int GetMinLevel() const { return minLevel; }
    
protected:
    virtual void doLogJob(const string &s, int level) = 0;
    int minLevel;
};

class FileLogger : public Logger {
public:
    FileLogger(int minLevel, const string &fileName) : Logger(minLevel) {
        logFile = fopen(fileName.c_str(), "a");
    }
    ~FileLogger() {
        fclose(logFile);
    }

protected:
    void doLogJob(const string &s, int level) {
        fprintf(logFile, "[%s] %s\n", LEVEL_HEADINGS[level], s.c_str());
    }

private:
    FILE *logFile;
};

class ConsoleLogger : public Logger {
public:
    ConsoleLogger(int minLevel) : Logger(minLevel) {}

protected:
    void doLogJob(const string &s, int level) {
        printf("[%s] %s\n", LEVEL_HEADINGS[level], s.c_str());
    }
};

void testLogger(Logger &logger) {
    logger.Log("abc", LogLevels::ERROR);
    logger.Log("def", LogLevels::INFO);
    logger.Log("ghi", LogLevels::WARNING);
}

int main() {
    ConsoleLogger c(LogLevels::WARNING);
    testLogger(c);

    FileLogger f(LogLevels::DEBUGING, "log.txt");
    testLogger(f);
}
