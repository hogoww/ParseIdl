#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <exception>
#include <string>

class Component{
 public:
  class AlreadyConnected : public std::exception{
 private:
   std::string errormsg;
   
 public:
   AlreadyConnected(std::string errorMsg);
   virtual ~AlreadyConnected() throw();
   virtual const char* what() const throw();
 };

 class NoConnection : public std::exception{
 private:
   std::string errormsg;
   
 public:
   NoConnection(std::string errorMsg);
   virtual ~NoConnection() throw();
   virtual const char* what() const throw();
 };
 
 class InvalidConnection : public std::exception{
 private:
   std::string errormsg;
  
 public:
   InvalidConnection(std::string ComponentType,std::string typePort);
   virtual ~InvalidConnection() throw();
   virtual const char* what() const throw();
 };


  class InvalidConnection;
  class NoConnection;
};

#endif
