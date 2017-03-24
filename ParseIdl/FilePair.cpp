#include "FilePair.h"


/******Constructeurs:******/


/* constructeurs public*/
FilePair::FilePair(std::string fileName,std::string directory):directoryName(directory){
  std::string hFileName;
  hFileName=directoryName+"/"+hFileName+".h";
  std::string cppFileName;
  cppFileName=directoryName+"/"+cppFileName+".cpp";
  
  h.open(hFileName.c_str());
  cpp.open(cppFileName.c_str());
}

/******Methodes:******/
/* methodes public*/
void FilePair::writeInCpp(std::string s){
  h<<s;
}

void FilePair::writeInH(std::string s){
  cpp<<s;
}

void FilePair::writeInCpp(char* s){
  h<<s;
}

void FilePair::writeInH(char* s){
  cpp<<s;
}


