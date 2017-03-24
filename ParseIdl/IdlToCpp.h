#ifndef __IDLTOCPP_H__
#define __IDLTOCPP_H__

#include "ParseurIdl.h"
#include "FilePair.h"

class IdlToCpp{
 private:
  ParseurIdl p;
  
  void containerTreatment();
  void CompleteInheritance(Container* c);//check if it does implement some interfaces beforehand
  void AttributeTreatement();
 public:
  IdlToCpp(std::string fileName);
};

#endif
