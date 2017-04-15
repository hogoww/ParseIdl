



#include "car.h"
car::car(std::string errorMsg):errormsg(errorMsg){
}
car::~car() throw (){
}
const char* car::what() const throw (){
 return errormsg.c_str();}




void car::connect_sze(int* a) throw ( Component::AlreadyConnected ){
if(a){
 throw Component::AlreadyConnected("sze");
}
else{
this->sze=a;
}
}

int* car::disconnect_sze() throw ( Component::NoConnection ){
if(sze){
this->sze=NULL;
}
else{
 throw Component::NoConnection("sze");
}
}

int* car::get_connection_sze() const{
return this->sze;
}



int car::smteahasa(bool e){
//Todo
int tempReturn;
return tempReturn;
}

