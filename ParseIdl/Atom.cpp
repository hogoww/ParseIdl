#include "Atom.h"
#define MY_TYPE 1

/******Constructeurs:******/


/* constructeurs public*/
Atom::Atom(std::string name,std::string type,std::string usage):Item(name,type),Usage(usage){
}

Atom::~Atom(){
}

/******Methodes:******/
/* methodes public*/
const std::string Atom::getUsage()const{
  return Usage;
}


void Atom::showMeWhatYouGot(size_t depth)const{
  Item::showMeWhatYouGot(depth);
  std::cout<<"\n";
}


bool Atom::doIInheritFromYou(){
  return (Usage=="provides");
}

std::string Atom::Declaration() const{
  return Item::Declaration()+" "+Usage;
}

const int Atom::whoAreYou()const{
  return MY_TYPE;
}
