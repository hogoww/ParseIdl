#include "ContainerInherit.h"

const std::regex ContainerInherit::exprInheritSomething(":");
const std::regex ContainerInherit::exprInherit("^ ?(.*?),");

/******Constructeurs:******/


/* constructeurs public*/
ContainerInherit::ContainerInherit(std::string name,std::string type,std::string inheritFrom):Container(name,type),InheritFrom(){
  ParseEnd(inheritFrom);
}

/******Methodes:******/
/* methodes private*/
/*private*/void ContainerInherit::ParseEnd(std::string inheritFrom){
  std::smatch bogus;
  if(std::regex_match(inheritFrom,bogus,exprInheritSomething)){
    std::smatch res;
    inheritFrom=bogus.suffix().str();//Remove the ';'
    while(std::regex_search(inheritFrom,res,exprInherit)){
      addInheritance(res.suffix().str());
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


