#ifndef __PHILOSOPHER_H__
#define __PHILOSOPHER_H__

#include <string>
#include "Component.h"

class Philosopher{
public:

bool name;

int* left;
void connect_left(int* a) throw (Component::AlreadyConnected);
int* disconnect_left() throw ( Component::NoConnection );
int* get_connection_left() const;

int* right;
void connect_right(int* a) throw (Component::AlreadyConnected);
int* disconnect_right() throw ( Component::NoConnection );
int* get_connection_right() const;

void get();
void release(int p, int& f, int& e);

};

#endif