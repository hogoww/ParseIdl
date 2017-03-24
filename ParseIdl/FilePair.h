#ifndef __FILEPAIR_H__
#define __FILEPAIR_H__

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

class FilePair{
 public:
  std::ofstream h;
  std::ofstream cpp;
  std::string directoryName;

  FilePair(std::string fileName,std::string directoryName="");
  void writeInCpp(std::string s);
  void writeInH(std::string s);
  void writeInCpp(char* s);
  void writeInH(char* s);
};

#endif
