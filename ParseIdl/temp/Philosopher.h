#ifndef __PHILOSOPHER_H__
#define __PHILOSOPHER_H__

#include <string>
#include "Component.h"

class Philosopher{
 private:
  std::string name;
  Fork_Item* left;
  Fork_Item* right;

 public:
  void setname(std::string a);
  std::string getname();
  void setleft(Fork_Item* a);
  Fork_Item* getleft();
  void connect_left(Fork_Item* a) throw (Component::AlreadyConnected);
  Fork_Item* disconnect_left() throw ( Component::NoConnection );
  Fork_Item* get_connection_left() const;
  void setright(Fork_Item* a);
  Fork_Item* getright();
  void connect_right(Fork_Item* a) throw (Component::AlreadyConnected);
  Fork_Item* disconnect_right() throw ( Component::NoConnection );
  Fork_Item* get_connection_right() const;

};
#endif
