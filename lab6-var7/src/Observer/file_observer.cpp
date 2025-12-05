#include <iostream>

#include "Observer/file_observer.h"

FileObserver::FileObserver(const std::string &filename) {
  logFile.open(filename, std::ios::app);
  if (!logFile.is_open()) {
    std::cerr << "Cannot open log file" << std::endl;
  }
}

FileObserver::~FileObserver() {
  if (logFile.is_open()) {
    logFile.close();
  }
}

void FileObserver::update(const std::string &message) {
  if (logFile.is_open()) {
    logFile << message << std::endl;
  }
}