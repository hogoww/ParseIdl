#ifndef __Function__
#define __Function__

#include "Item.h"
#include <vector>
#include "Parameter.h"
#include <regex>

class Function : public Item{
 private:
  std::vector<Parameter> Param;
  std::vector<std::string> Exception; 

  //Parse function.
  void parseEnd(std::string ToBeParse);
  
  //Parsing regex
  static const std::regex exprParam;
  static const std::regex exprExcep;
  static const std::regex exprParseParam;
  static const std::regex exprParseExcept; 

 public:
  Function(std::string name,std::string type,std::string ToBeParsed);
  virtual ~Function();
  virtual const std::vector<Parameter> getParam() const;
  virtual const std::vector<std::string> getException() const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
  virtual std::string Declaration()const;
  virtual const int whoAreYou()const;
};

#endif
