#ifndef __FILEPAIR_H__
#define __FILEPAIR_H__

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

class FilePair{
 private:
  std::ofstream h;
  std::ofstream cpp;
  std::string directoryName;
 public:
  FilePair(std::string ifileName,std::string directoryName);
  void writeInCpp(std::string s);
  void writeInH(std::string s);
};

#endif
