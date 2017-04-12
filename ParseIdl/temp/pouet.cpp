#include "pouet.h"

pouet::pouet(std::string errorMsg):errormsg(errorMsg){
}

pouet::~pouet() throw (){
}

const char* pouet::what() const throw (){
 return errormsg.c_str();
}


