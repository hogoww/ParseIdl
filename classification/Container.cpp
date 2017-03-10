#include "Container.h"


/******Constructeurs:******/


/* constructeurs public*/
Container::Container(std::string name,std::string type):Item(name,type),Content(std::vector<Item>()){
}


/******Methodes:******/
/* methodes public*/
void Container::addItem(Item i){
  Content.push_back(i);
}

const std::vector<Item> Container::getContent()const {
  return Content;
}


void Container::showMeWhatYouGot(size_t depth)const{
  Item::showMeWhatYouGot(depth);
  std::cout<<"\n";


  for(std::vector<Item>::const_iterator it=Content.begin();it!=Content.end();++it) {
    it->showMeWhatYouGot(depth+1);
    std::cout<<"\n";
  }
  std::cout<<"\n";
}


std::ostream& operator<<(std::ostream& os, const Container& obj)
{
  os<<"type";
  return os;
}
