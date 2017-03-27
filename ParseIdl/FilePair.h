#ifndef __FILEPAIR_H__
#define __FILEPAIR_H__

#include <string>
#include <fstream>

class FilePair{
 public:
  std::string fileName;
  std::ofstream* h;
  std::ofstream*  cpp;
  static std::string directoryName;
  int depth;
  std::string currentNamespace;

  void connectFiles(std::string filename);

  FilePair(std::string filename="",int currentdepth=0,std::string Namespace="",std::string directoryName="");
  ~FilePair();
  FilePair& operator=(const FilePair& other);
};

#endif
