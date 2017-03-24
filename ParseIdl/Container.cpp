#include "Container.h"


/******Constructeurs:******/


/* constructeurs public*/
Container::Container(std::string name,std::string type):Item(name,type),Content(){
}

Container::~Container(){
  std::vector<Item*>::iterator end=Content.end();
  for(std::vector<Item*>::iterator it=Content.begin();it!=end;++it) {
    delete (*it);
  }
  Content.clear();
}

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

bool Container::doIInheritFromYou(){
  std::vector<Item*>::iterator end=Content.end();
  for(std::vector<Item*>::iterator it=Content.begin();it!=end;++it){
    if((*it)->doIInheritFromYou()){
      std::cerr<<getName()<<" shouldn't inherit from anything, much less :"<<(*it)->getName()<<std::endl;
    }
  }  
  return false;
}
