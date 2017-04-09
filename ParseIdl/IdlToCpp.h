#ifndef __IDLTOCPP_H__
#define __IDLTOCPP_H__

#include "ParseurIdl.h"
#include "FilePair.h"

#include <exception>
#include <iostream>
#include <regex>
#include <vector>

class IdlToCpp{
 private:
  ParseurIdl p;
  std::string directoryName;
  std::vector<std::string> NameFileCreated;//For makefile generation
  
  void printWhatItContainInH(Container* c,FilePair& f);
  void printWhatItContainIncpp(Container* c,FilePair& f);
  void ItemTreatment(Item* i,FilePair* f);
  void CompleteInheritance();//check if it does implement some interfaces beforehand

  void ExceptionTreatment(Container* Exception);
  void InterfaceTreatment(Container* Interface);
  void IterateOtherContainer(Container* c,FilePair* f);
  FilePair* OpenFileDescriptors(std::string FileName);


  static const std::regex exprInterface;
  static const std::regex exprComponent;
  static const std::regex exprException;
  static const std::regex exprModule;
 public:
  IdlToCpp(std::string fileName,std::string DirectoryName="");
  void start();
  void GenerateBasicMakefile();
  void GenerateBasicMain();
  void showMeThatFile()const;
};

#endif
