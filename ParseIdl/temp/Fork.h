#ifndef __FORK_H__
#define __FORK_H__

#include <exception>
#include <string>
#include "Component.h"
#include "InUse.h"

class Fork{
 public:
  virtual void get() throw (InUse)=0;
  virtual void release()=0;

};
#endif
