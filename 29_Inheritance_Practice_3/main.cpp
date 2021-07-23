//
//  main.cpp
//  29_Inheritance_Practice_3
//
//  Created by 세광 on 2021/07/23.
//

// 상속과 가상함수를 이용하여 코드 줄이기

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

class FileLogger {
public:
    FileLogger(int minLevel, const string &fileName) : minLevel(minLevel) {
        logFile = fopen(fileName.c_str(), "a");
    }
    ~FileLogger() {
        fclose(logFile);
    }

    void Log(const string &s, int level) {
        if (level >= minLevel)
            fprintf(logFile, "[%s] %s\n", LEVEL_HEADINGS[level], s.c_str());
    }
    
    int GetMinLevel() const { return minLevel; }

private:
    int minLevel;
    FILE *logFile;
};

class ConsoleLogger {
public:
    ConsoleLogger(int minLevel) : minLevel(minLevel) {}

    void Log(const string &s, int level) {
        if (level >= minLevel)
            printf("[%s] %s\n", LEVEL_HEADINGS[level], s.c_str());
    }
    
    int GetMinLevel() const { return minLevel; }

private:
    int minLevel;
};

int main() {
    ConsoleLogger c(LogLevels::WARNING);
    c.Log("abc", LogLevels::ERROR);
    c.Log("def", LogLevels::INFO);
    c.Log("ghi", LogLevels::WARNING);

    FileLogger f(LogLevels::DEBUGING, "log.txt");
    f.Log("abc", LogLevels::ERROR);
    f.Log("def", LogLevels::INFO);
    f.Log("ghi", LogLevels::WARNING);
}
