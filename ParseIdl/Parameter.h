#ifndef __Parameter__
#define __Parameter__

#include "Item.h"

#include <regex>


class Parameter : public Item {
 private:
  enum TypeParam { In, Out, InOut };
  TypeParam t;//True if "in" parameter False if "out" parameter

  static const std::regex exprIn;
  static const std::regex exprOut;
  static const std::regex exprInOut;

 public:
  Parameter(std::string name,std::string type,std::string typeparam);
  virtual ~Parameter();
  const bool getTypeParameter() const;
  std::string showMeThatParameter()const;
  void showMeWhatYouGot(size_t depth=0)const;//shouldn't be used
};

#endif
