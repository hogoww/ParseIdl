#include "Item.h"
#define MY_TYPE 0


/******Constructeurs:******/


/* constructeurs public*/
Item::Item(std::string name,std::string type):Name(name),Type(type){
}

Item::~Item(){
}

/******Methodes:******/
/* methodes public*/
const std::string Item::getType() const{
  return Type;
}

const std::string Item::getName() const{
  return Name;
}


void Item::showMeWhatYouGot(size_t depth)const{
  // for(size_t i=0;i<depth;i++){
  //   std::cout<<"-";
  // }
  // std::cout<<Type<<" "<<Name;
  std::cout<<getDepth(depth)<<Declaration();
}

std::string Item::getDepth(size_t depth) const{
  std::string s="";
  for(size_t i=0;i<depth;i++){
    s+="-";
  }
  return s;
}

bool Item::doIInheritFromYou(){
  return false;
}


std::string Item::Declaration() const{
  std::string s;
  s=Type;
  s+=" ";
  s+=Name;
  return s;
}

const int Item::whoAreYou()const{
  return MY_TYPE;
}
