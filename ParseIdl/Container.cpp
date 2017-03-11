#include "Container.h"


/******Constructeurs:******/


/* constructeurs public*/
Container::Container(std::string name,std::string type):Item(name,type),Content(){
}

// Container::~Container(){
// for(std::vector<Item*>::iterator it=Content.begin();it!=Content.end();++it) {
//   delete (*it);
//  }
//  Content.clear();
// }

/******Methodes:******/
/* methodes public*/
void Container::addItem(Item* i){
  Content.push_back(i);
}

const std::vector<Item*> Container::getContent()const {
  return Content;
}


void Container::showMeThatName(size_t depth)const{
  Item::showMeWhatYouGot(depth);
}

void Container::showMeThatContent(size_t depth)const{
  std::vector<Item*>::const_iterator end=Content.end();
  for(std::vector<Item*>::const_iterator it=Content.begin();it!=end;++it) {
   (*it)->showMeWhatYouGot(depth+1);
 }
}

void Container::showMeWhatYouGot(size_t depth)const{
  showMeThatName(depth);
  std::cout<<"\n";
  showMeThatContent(depth);
}

