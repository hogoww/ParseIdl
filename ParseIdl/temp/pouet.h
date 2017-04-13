#ifndef __POUET_H__
#define __POUET_H__

#include <exception>
#include <string>
#include "Component.h"
class pouet : std::exception {
private:
std::string errormsg;

public:
pouet(std::string errorMsg);
virtual ~pouet() throw();
virtual const char* what() const throw();


int* s;
void connect_s(int* a) throw (Component::AlreadyConnected);
int* disconnect_s() throw ( Component::NoConnection );
int* get_connection_s() const;

bool e;

};

#endif