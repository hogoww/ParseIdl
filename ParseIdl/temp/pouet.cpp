


#include "pouet.h"

pouet::pouet(std::string errorMsg):errormsg(errorMsg){
}

pouet::~pouet() throw (){
}

const char* pouet::what() const throw (){
 return errormsg.c_str();
}




void pouet::connect_s(int* a) throw ( Component::AlreadyConnected ){
if(a){
 throw Component::AlreadyConnected("s");
}
else{
this->s=a;
}
}

int* pouet::disconnect_s() throw ( Component::NoConnection ){if(s){
this->s=NULL;
}
else{
 throw Component::NoConnection("s");
}
}

int* pouet::get_connection_s() const{
return this->s;
}



