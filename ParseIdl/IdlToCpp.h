#ifndef __IDLTOCPP_H__
#define __IDLTOCPP_H__

#include "ParseurIdl.h"
#include "FilePair.h"

#include <exception>
#include <iostream>
#include <regex>

class IdlToCpp{
 private:
  ParseurIdl p;
  std::string directoryName;
  
  void printWhatItContainInH(Container* c,FilePair& f);
  void printWhatItContainIncpp(Container* c,FilePair& f);
  void ItemTreatment(Item* i,FilePair* f);
  void CompleteInheritance();//check if it does implement some interfaces beforehand

  void ExceptionTreatment(Container* Exception);
  void IterateOtherContainer(Container* c,FilePair* f);

  static const std::regex exprInterface;
  static const std::regex exprComponent;
  static const std::regex exprException;
  static const std::regex exprModule;
 public:
  IdlToCpp(std::string fileName,std::string DirectoryName="");
  void start();
};

#endif
