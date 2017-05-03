#ifndef __ContainerInherit__
#define __ContainerInherit__

#include "Container.h"
#include <regex>
#include <set>

class ContainerInherit : public Container{
 private:
  std::set<std::string> InheritFrom;
  
  //Parsing functions.
  void ParseEnd(std::string inheritFrom);
  void addInheritance(std::string i);
  
  //Parsing Regex.
  static const std::regex exprInheritSomething;
  static const std::regex exprInherit;
  
 public:
  ContainerInherit(std::string name,std::string type,std::string inheritFrom);
  virtual ~ContainerInherit();
  virtual const std::set<std::string> getInheritFrom()const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
  virtual bool doIInheritFromYou();
  virtual std::string Declaration()const;
  virtual const int whoAreYou()const;
};

#endif
