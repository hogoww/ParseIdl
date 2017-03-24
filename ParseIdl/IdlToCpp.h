#ifndef __IDLTOCPP_H__
#define __IDLTOCPP_H__

#include "ParseurIdl.h"
#include "FilePair.h"

#include <exception>
#include <iostream>

class IdlToCpp{
 private:
  ParseurIdl p;
  std::string currentNamespace;
  std::string directoryName;
  int depth;
  
  void ItemTreatment();
  void CompleteInheritance();//check if it does implement some interfaces beforehand

  void ExceptionTreatment(Container* Exception);

 public:
  IdlToCpp(std::string fileName,std::string DirectoryName);
};

#endif
