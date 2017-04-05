#include "InvalidConnection.h"

Component::InvalidConnection::InvalidConnection(std::string ComponentName,std::string TypePort):errormsg(ComponentName+" can't get connected to type port."){
}

Component::InvalidConnection::~InvalidConnection() throw(){}


const char* Component::InvalidConnection::what() const throw(){
  return errormsg.c_str();
}


