#ifndef __POUET_H__
#define __POUET_H__

#include <string>
#include "Component.h"

class pouet{
public:


int* s;
void connect_s(int* a) throw (Component::AlreadyConnected);
int* disconnect_s() throw ( Component::NoConnection );
int* get_connection_s() const;

bool e;
int smth(bool e);

};

#endif