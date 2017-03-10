#include "ContainerInherit.h"
#include <unistd.h>

const std::regex ContainerInherit::exprInheritSomething(":",std::regex::optimize);
const std::regex ContainerInherit::exprInherit("^ ?(\\w+),?",std::regex::optimize);

/******Constructeurs:******/


/* constructeurs public*/
ContainerInherit::ContainerInherit(std::string name,std::string type,std::string inheritFrom):Container(name,type),InheritFrom(){
  ParseEnd(inheritFrom);
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
  InheritFrom.push_back(i);
}

const std::vector<std::string> ContainerInherit::getInheritFrom()const{
  return InheritFrom;
}

void ContainerInherit::showMeWhatYouGot(size_t depth)const{
  showMeThatName(depth);

  if(InheritFrom.size()){
    std::cout<<" : ";
    std::cout<<*InheritFrom.begin();
    for(std::vector<std::string>::const_iterator it=++InheritFrom.begin();it!=InheritFrom.end();++it){
      std::cout<<", "<<*it;
    }
  }
  std::cout<<"\n";
  showMeThatContent(depth);
}
