#include "Item.h"


/******Constructeurs:******/


/* constructeurs public*/
Item::Item(std::string name,std::string type):Name(name),Type(type){
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
  for(size_t i=0;i<depth;i++){
    std::cout<<"-";
  }
  std::cout<<Type<<" "<<Name;
}
