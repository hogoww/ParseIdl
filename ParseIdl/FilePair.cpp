#include "FilePair.h"


std::string FilePair::directoryName("");

/* constructeurs public*/
FilePair::FilePair(std::string filename,int currentdepth,std::string Namespace,std::string directory):fileName(filename),depth(currentdepth),currentNamespace(Namespace){
  if(directoryName.empty()){
    directoryName=directory;
  }
}

FilePair::~FilePair(){
  delete h;
  delete cpp;
}

FilePair& FilePair::operator=(const FilePair& other){
  if(this != &other){
    this->h=other.h;
    this->cpp=other.cpp;
  }
  return *this;
}


void FilePair::connectFiles(std::string filename){
  fileName=filename;
  std::string hFileName;
  hFileName=directoryName+"/"+hFileName+".h";
  std::string cppFileName;
  cppFileName=directoryName+"/"+cppFileName+".cpp";
  
  h->open(hFileName.c_str());
  cpp->open(cppFileName.c_str());

}
