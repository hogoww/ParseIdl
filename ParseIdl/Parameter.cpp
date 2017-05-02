#include "Parameter.h"

const std::regex Parameter::exprIn("In",std::regex::icase|std::regex::optimize);
const std::regex Parameter::exprOut("Out",std::regex::icase|std::regex::optimize);
const std::regex Parameter::exprInOut("InOut",std::regex::icase|std::regex::optimize);


/******Constructeurs:******/


/* constructeurs public*/
Parameter::Parameter(std::string name,std::string type,std::string typeparam):Item(name,type){
  std::smatch bogus;
  if(std::regex_search(typeparam,bogus,exprInOut)){
    t=TypeParam::InOut;
  }
  else{
    if(std::regex_search(typeparam,bogus,exprOut))
      t=TypeParam::Out;
    else{
      if(std::regex_search(typeparam,bogus,exprIn)){
	t=TypeParam::In;
      }
      else{
	std::cerr<<typeparam<<"isn't a parameter type for "<<name<<" "<<type<<std::endl;
	std::terminate();
      }
    }
  }
}



/******Methodes:******/
/* methodes public*/
const Parameter::TypeParam Parameter::getTypeParameter() const{
  return t;
}

Parameter::~Parameter(){
}

std::string Parameter::showMeThatParameter()const{
  // std::cout<<(In?"In":"Out")<<" "<<Type<<" "<<Name;
  return (t==TypeParam::In?"in ":(t==TypeParam::Out?"out ":"inout "))+Item::Declaration();
}

void Parameter::showMeWhatYouGot(size_t depth)const {
  std::cout<<"ShowMeWhatYouGot() shouldn't be used on a Parameter Object, how the hell could you do it?"<<std::endl;
  std::terminate();
}

