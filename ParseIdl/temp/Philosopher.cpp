






#include "Philosopher.h"




void Philosopher::connect_left(int* a) throw ( Component::AlreadyConnected ){
if(left){
 throw Component::AlreadyConnected("left");
}
else{
this->left=a;
}
}

int* Philosopher::disconnect_left() throw ( Component::NoConnection ){
if(left){
this->left=NULL;
}
else{
 throw Component::NoConnection("left");
}
}

int* Philosopher::get_connection_left() const{
return this->left;
}


void Philosopher::connect_right(int* a) throw ( Component::AlreadyConnected ){
if(right){
 throw Component::AlreadyConnected("right");
}
else{
this->right=a;
}
}

int* Philosopher::disconnect_right() throw ( Component::NoConnection ){
if(right){
this->right=NULL;
}
else{
 throw Component::NoConnection("right");
}
}

int* Philosopher::get_connection_right() const{
return this->right;
}




void Philosopher::get(){
//Todo
}

void Philosopher::release(int p, int& f, int& e){
//Todo
}

