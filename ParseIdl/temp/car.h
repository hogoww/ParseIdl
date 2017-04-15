#ifndef __CAR_H__
#define __CAR_H__

#include <exception>
#include <string>
#include "Component.h"

class car : std::exception {
private:
std::string errormsg;
public:
car(std::string errorMsg);
virtual ~car() throw();
virtual const char* what() const throw();


int* sze;
void connect_sze(int* a) throw (Component::AlreadyConnected);
int* disconnect_sze() throw ( Component::NoConnection );
int* get_connection_sze() const;

bool eac;
int smteahasa(bool e);

};

#endif