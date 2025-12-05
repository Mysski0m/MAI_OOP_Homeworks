#pragma once

#include <fstream>

#include "observer.h"

class FileObserver : public Observer {
private:
  std::ofstream logFile;

public:
  FileObserver(const std::string &filename = "log.txt");
  ~FileObserver();
  void update(const std::string &message) override;
};