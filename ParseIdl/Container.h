#ifndef __Container__
#define __Container__

#include <vector>
#include "Item.h"

class Container : public Item {
 protected:
  std::vector<Item*> Content;
  /* virtual void showMeThatName(size_t depth)const; */
  virtual void showMeThatContent(size_t depth)const;
 public:
  Container(std::string name,std::string type);
  virtual ~Container();

  virtual void addItem(Item* i);
  virtual const std::vector<Item*> getContent()const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
  virtual bool doIInheritFromYou();
  virtual std::string Declaration()const;
  virtual const ClassType whoAreYou()const;
};

#endif
