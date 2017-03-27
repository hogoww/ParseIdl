#ifndef __Parameter__
#define __Parameter__

#include "Item.h"

class Parameter : public Item {
 private:
  bool In;//True if "in" parameter False if "out" parameter
 public:
  virtual ~Parameter();
  Parameter(std::string name,std::string type,bool in);
  const bool getIn() const;
  std::string showMeThatParameter()const;
  void showMeWhatYouGot(size_t depth=0)const;//Ne devrais pas etre utilisée.
};

#endif
