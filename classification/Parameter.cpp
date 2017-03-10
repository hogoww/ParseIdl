#include "Parameter.h"


/******Constructeurs:******/


/* constructeurs public*/
Parameter::Parameter(std::string name,std::string type,bool in):Item(name,type),In(in){
  //à implementer
}


/******Methodes:******/
/* methodes public*/
const bool Parameter::getIn() const{
  return In;
}


void Parameter::showMeThatParameter()const{
  std::cout<<(In?"In":"Out")<<" "<<Type<<" "<<Name;
}

void Parameter::showMeWhatYouGot(size_t depth)const {
  std::cout<<"ShowMeWhatYouGot() shouldn't be used on a Parameter Object, how the hell could you do it?"<<std::endl;
  std::terminate();
}

