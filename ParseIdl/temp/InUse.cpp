#include "InUse.h"

InUse::InUse(std::string errorMsg):errormsg(errorMsg){
}

InUse::~InUse() throw (){
}

const char* InUse::what() const throw (){
 return errormsg.c_str();
}


