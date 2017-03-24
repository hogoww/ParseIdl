#include "ContainerInherit.h"
#include <unistd.h>

const std::regex ContainerInherit::exprInheritSomething(":",std::regex::optimize);
const std::regex ContainerInherit::exprInherit("^ ?(\\w+),?",std::regex::optimize);

/******Constructeurs:******/


/* constructeurs public*/
ContainerInherit::ContainerInherit(std::string name,std::string type,std::string inheritFrom):Container(name,type),InheritFrom(){
  ParseEnd(inheritFrom);
}

ContainerInherit::~ContainerInherit(){
  InheritFrom.clear();
}

/******Methodes:******/
/* methodes private*/
/*private*/void ContainerInherit::ParseEnd(std::string inheritFrom){
  std::smatch bogus;
  if(std::regex_search(inheritFrom,bogus,exprInheritSomething)){
    inheritFrom=bogus.suffix().str();//Remove the ';
    std::smatch res;
    while(std::regex_search(inheritFrom,res,exprInherit)){
      addInheritance(res[1].str());
      inheritFrom=res.suffix().str();
    }
  }
}



/* methodes public*/
void ContainerInherit::addInheritance(std::string i){
  InheritFrom.insert(i);
}

const std::set<std::string> ContainerInherit::getInheritFrom()const{
  return InheritFrom;
}

void ContainerInherit::showMeWhatYouGot(size_t depth)const{
  showMeThatName(depth);

  if(InheritFrom.size()){
    std::set<std::string>::const_iterator end=InheritFrom.cend();
    std::cout<<" : ";
    std::cout<<*InheritFrom.cbegin();
    for(std::set<std::string>::const_iterator it=++InheritFrom.cbegin();it!=end;++it){
      std::cout<<", "<<*it;
    }
  }
  std::cout<<"\n";
  showMeThatContent(depth);
}


bool ContainerInherit::doIInheritFromYou(){
  std::vector<Item*>::iterator end=Content.end();
  for(std::vector<Item*>::iterator it=Content.begin();it!=end;++it){
    if((*it)->doIInheritFromYou()){
      addInheritance((*it)->getName());
    }
  }
  return false;
}
