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
  enum ClassType{Itemt,Atomt,Containert,ContainerInheritt,Functiont};
  Item(std::string name,std::string type);
  virtual ~Item();
  virtual const std::string getType() const;
  virtual const std::string getName() const;
  virtual void showMeWhatYouGot(size_t depth=0)const;
  virtual bool doIInheritFromYou();//Only does things in containers class.
  virtual std::string Declaration() const;
  std::string getDepth(size_t depth) const;
  virtual const ClassType whoAreYou()const;
  virtual bool isFunction() const;
};

#endif
