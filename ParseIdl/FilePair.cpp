#include "FilePair.h"


std::string FilePair::directoryName("");

/* constructeurs public*/
FilePair::FilePair(std::string filename,int currentdepth,std::string Namespace,std::string directory):fileName(filename),depth(currentdepth),currentNamespace(Namespace){
  h=new std::ofstream();
  cpp=new std::ofstream();
  // if(directoryName.empty()){
  //   directoryName=directory;
  // }
  directoryName="temp";
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
  std::string hFileName;
  hFileName=directoryName+"/"+filename+".h";
  std::string cppFileName;
  cppFileName=directoryName+"/"+filename+".cpp";
  h->open(hFileName.c_str()); 
}
