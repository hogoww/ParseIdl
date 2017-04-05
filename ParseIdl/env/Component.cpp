#include "Component.h"

Component::AlreadyConnected::AlreadyConnected(std::string ComponentName):errormsg(ComponentName+" is already connected."){
}

Component::AlreadyConnected::~AlreadyConnected() throw(){}


const char* Component::AlreadyConnected::what() const throw(){
  return errormsg.c_str();
}



Component::NoConnection::NoConnection(std::string ComponentName):errormsg("You can't disconnect something that isn't connected ("+ComponentName+")."){
}

Component::NoConnection::~NoConnection() throw(){}


const char* Component::NoConnection::what() const throw(){
  return errormsg.c_str();
}



Component::InvalidConnection::InvalidConnection(std::string ComponentName,std::string TypePort):errormsg(ComponentName+" can't get connected to type port."){
}

Component::InvalidConnection::~InvalidConnection() throw(){}


const char* Component::InvalidConnection::what() const throw(){
  return errormsg.c_str();
}
