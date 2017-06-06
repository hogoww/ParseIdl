#ifndef __FILEPAIR_H__
#define __FILEPAIR_H__

#include <string>
#include <fstream>
#include <iostream>


class FilePair{
 public:
  std::string fileName;
  std::ofstream* h;
  std::ofstream*  cpp;
  static std::string directoryName;
  int depth;
  std::string currentNamespace;
  bool interface;
  
  void connectFiles(std::string filename,bool isInterface=false);
  void deleteCpp();

  FilePair(std::string filename="",int currentdepth=0,std::string Namespace="",std::string directoryName="");
  ~FilePair();
  FilePair& operator=(const FilePair& other);

};

#endif
