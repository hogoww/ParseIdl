#ifndef __DIDNOTFOUNDFILEEXCEP_H__
#define __DIDNOTFOUNDFILEEXCEP_H__

#include <iostream>
#include <exception>
#include <string>

class DidNotFoundFileExcep : public std::exception {
 private:
  std::string errormsg;
  
 public:
  DidNotFoundFileExcep(std::string errorMsg);
  virtual ~DidNotFoundFileExcep() throw();
  virtual const char* what() const throw();

};

#endif
