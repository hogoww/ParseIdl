#ifndef __Item__
#define __Item__

#include <string>
#include <exception>//Utile débugg sous classes
#include <iostream>//utile débugg sous classes

class Item{
 protected:
  std::string Name;
  std::string Type;
 
 public:
  Item(std::string name,std::string type);
  virtual ~Item();
  virtual const std::string getType() const;
  virtual const std::string getName() const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
};

#endif
