#include "Atom.h"


/******Constructeurs:******/


/* constructeurs public*/
Atom::Atom(std::string name,std::string type,std::string usage):Item(name,type),Usage(usage){
}


/******Methodes:******/
/* methodes public*/
const std::string Atom::getUsage()const{
  return Usage;
}


void Atom::showMeWhatYouGot(size_t depth)const{
  Item::showMeWhatYouGot(depth);
  std::cout<<" "<<Usage<<"\n";
  std::cout<<Usage<<std::endl;
}
