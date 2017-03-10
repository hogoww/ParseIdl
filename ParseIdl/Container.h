#ifndef __Container__
#define __Container__

#include <vector>
#include "Item.h"

class Container : public Item {
 private:
  std::vector<Item*> Content;
 public:
  Container(std::string name,std::string type);
  virtual void addItem(Item* i);
  virtual const std::vector<Item*> getContent()const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
};

#endif
