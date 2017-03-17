#include "DidNotFoundFileExcep.h"

DidNotFoundFileExcep::DidNotFoundFileExcep(std::string File):errormsg(File+" couldn't be foud in the current repository"){
}
DidNotFoundFileExcep::
~DidNotFoundFileExcep() throw(){}


const char* DidNotFoundFileExcep::what() const throw(){
  return errormsg.c_str();
}


