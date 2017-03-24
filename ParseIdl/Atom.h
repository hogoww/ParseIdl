#ifndef __Atom__
#define __Atom__

#include "Item.h"

class Atom : public Item{
 private:
  std::string Usage;
 public:
  Atom(std::string name,std::string type,std::string usage);
  virtual ~Atom();
  virtual const std::string getUsage() const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
  virtual bool doIInheritFromYou();

};

#endif
