#include "ParseurIdl.h"
#include <iostream>
#include <string>

int main(int argc,char** argv){
  if(argc!=2){
    std::cout<<"I need an a file to work!"<<std::endl;
    return 1;
  }
  std::string File(argv[1]);
  ParseurIdl p(File);
   p.showMeThatFile();

   return 0;
}
