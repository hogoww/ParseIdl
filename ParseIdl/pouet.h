#ifndef __POUET_H__
#define __POUET_H__

#include <exception>
#include <string>

class pouet : std::exception {
private:
std::string errormsg;

public:
pouet(std::string errorMsg);
virtual ~pouet() throw();
virtual const char* what() const throw();
};

#endif