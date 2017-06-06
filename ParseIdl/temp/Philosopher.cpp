


#include "Philosopher.h"


void Philosopher::setname(std::string a){
this->name=a;
}

std::string Philosopher::getname(){
return this->name;
}



void Philosopher::setleft(Fork_Item* a){
this->left=a;
}

Fork_Item* Philosopher::getleft(){
return this->left;
}

void Philosopher::connect_left(Fork_Item* a) throw ( Component::AlreadyConnected ){
if(left){
 throw Component::AlreadyConnected("left");
}
else{
this->left=a;
}
}

Fork_Item* Philosopher::disconnect_left() throw ( Component::NoConnection ){
if(left){
this->left=NULL;
}
else{
 throw Component::NoConnection("left");
}
}

Fork_Item* Philosopher::get_connection_left() const{
return this->left;
}


void Philosopher::setright(Fork_Item* a){
this->right=a;
}

Fork_Item* Philosopher::getright(){
return this->right;
}

void Philosopher::connect_right(Fork_Item* a) throw ( Component::AlreadyConnected ){
if(right){
 throw Component::AlreadyConnected("right");
}
else{
this->right=a;
}
}

Fork_Item* Philosopher::disconnect_right() throw ( Component::NoConnection ){
if(right){
this->right=NULL;
}
else{
 throw Component::NoConnection("right");
}
}

Fork_Item* Philosopher::get_connection_right() const{
return this->right;
}

