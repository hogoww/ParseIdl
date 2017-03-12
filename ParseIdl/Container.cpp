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

Container::~Container(){
  std::vector<Item*>::iterator end=Content.end();
  for (std::vector<Item*>::iterator it = Content.begin();it!=end;++it){
    delete *it;
  }
  Content.clear();
}

// Container::~Container(const Container toBeCopied){
//   if(this!=toBeCopied){
//     Container c;
//     std::vector<Item*>::const_iterator end=toBeCopied.Container.end();
//     for(std::vector<Item*>::const_iterator it=toBeCopied.Container.begin();it!=end;++it){
//       c.addItem(*it);
//     }
//   }
//   else{
//     return this;
//   }
// }

void Container::showMeThatName(size_t depth)const{
  Item::showMeWhatYouGot(depth);
}

void Container::showMeThatContent(size_t depth)const{
  std::vector<Item*>::const_iterator end=Content.cend();
  for(std::vector<Item*>::const_iterator it=Content.cbegin();it!=end;++it) {
   (*it)->showMeWhatYouGot(depth+1);
 }
}

void Container::showMeWhatYouGot(size_t depth)const{
  showMeThatName(depth);
  std::cout<<"\n";
  showMeThatContent(depth);
}

