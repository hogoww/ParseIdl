#ifndef __ContainerInherit__
#define __ContainerInherit__

#include "Container.h"
#include <regex>

class ContainerInherit : public Container{
 private:
  std::vector<std::string> InheritFrom;
  
  //Parsing functions.
  void ParseEnd(std::string inheritFrom);
  void addInheritance(std::string i);
  
  //Parsing Regex.
  static const std::regex exprInheritSomething;
  static const std::regex exprInherit;
  
 public:
  ContainerInherit(std::string name,std::string type,std::string inheritFrom);
  virtual const std::vector<std::string> getInheritFrom()const;
};

#endif
