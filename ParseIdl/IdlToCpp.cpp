#include "IdlToCpp.h"

const std::regex IdlToCpp::exprInterface("interface",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprComponent("component",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprException("exception",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprModule("module",std::regex::icase|std::regex::optimize);


#define SAY cout//For output like "i've done something!"

/******Constructeurs:******/


/* constructeurs public*/
IdlToCpp::IdlToCpp(std::string fileName,std::string DN):p(fileName),directoryName(DN){
}


/******Methodes:******/
/* methodes private*/

/*private*/void IdlToCpp::CompleteInheritance(){
  p.checkForInterfaceInheritance();
}

std::string IDStringToCharUpper(std::string s){
  size_t len=s.length();
  std::string res("");
  int charNumber;
  for(size_t i=0;i<len;++i){ 
    charNumber=(int)s[i];
    if((charNumber<91 && charNumber>64) || charNumber==95 || (charNumber>47 && charNumber<58)){//uppercase/underscore/number
      res+=s[i];
    }
    else{
      if(charNumber>96 && charNumber<123){
	res+=(char)(charNumber-32);
      }
      else{
	std::cerr<<"Identifiant \""<<s<<"\"non valide"<<std::endl;
	std::terminate();
      }
    }
  }
  return res;
}

void IdlToCpp::start(){
  const std::vector<Container *> c=p.getFileContent();
  std::vector<Container*>::const_iterator end=c.cend();
  p.getFileName();
  for(std::vector<Container*>::const_iterator it=c.cbegin();it!=end;++it){
    FilePair* f=NULL;
    ItemTreatment(*it,f);
  }
}

void IdlToCpp::IterateOtherContainer(Container* c,FilePair* f){//Shouldn't be usefull since we're only taking a one at a time container
  std::vector<Item*> Content=c->getContent();
  std::vector<Item*>::iterator end=Content.end();
  p.getFileName();
  for(std::vector<Item*>::iterator it=Content.begin();it!=end;++it){
    FilePair* f=NULL;
    ItemTreatment(*it,f);
  }
}

void IdlToCpp::ItemTreatment(Item* i,FilePair* f){
  std::SAY<<"i'm treating an item"<<std::endl;
  std::smatch bogus;
  std::string name=i->getName();
  
  if(std::regex_search(i->getType(),bogus,exprException)){
    f=new FilePair();
    f->connectFiles(i->getName());
    ExceptionTreatment(static_cast<Container*>(i));
    delete f;
    f=NULL;
    return;
  }
  // if(std::regex_search(name,bogus,exprModule)){
  //   f=new FilePair();
  //   f->depth++;
  //   f->currentNamespace=name;
  //   IdlToCpp::(Container* c,f);

  //   delete f;
  //   f=NULL;
  //   return;
  // }

  
}

void moduleTreatment(Container* module,FilePair *f){
  
}



std::string toUpper(std::string s){//Just to be more legible
  return IDStringToCharUpper(s);
}


void IdlToCpp::ExceptionTreatment(Container* Exception){
  std::SAY<<"i'm creating an Exception file!"<<std::endl;
  std::string ExceptionName=Exception->getName();
  FilePair f;
  f.connectFiles(ExceptionName);
  std::string upperName=toUpper(ExceptionName);
  //multidefinition Controle
  *f.h<<"#ifndef __"<<upperName<<"_H__\n";
  *f.h<<"#define __"<<upperName<<"_H__\n";

  *f.h<<"\n";//start Includes

  *f.h<<"#include <exception>\n";
  *f.h<<"#include <string>\n";
  //add type Controle for more inclusions 


  *f.h<<"\n";//end Includes

  *f.h<<"class "<<ExceptionName<<" : std::exception {\n";//start class

  //class
  *f.h<<"private:\n";
  *f.h<<"std::string errormsg;\n";
  *f.h<<"\npublic:\n";
  *f.h<<ExceptionName<<"(std::string errorMsg);\n";
  *f.h<<"virtual ~"<<ExceptionName<<"() throw();\n";
  *f.h<<"virtual const char* what() const throw();\n";
  
  //printWhatItContainInH(Exception,f);
    
    
  *f.h<<"};\n\n";//end class    
  *f.h<<"#endif";//end multidefinitionControl

  *f.cpp<<"#include \""<<ExceptionName<<".h\"\n\n";
  *f.cpp<<ExceptionName<<"::"<<ExceptionName<<"(std::string errorMsg):errormsg(errorMsg){\n}\n\n";
  *f.cpp<<ExceptionName<<"::~"<<ExceptionName<<"() throw (){\n}\n\n";
  *f.cpp<<"const char* "<<ExceptionName<<"::what() const throw (){\n return errormsg.c_str();\n}\n";
  printWhatItContainIncpp(Exception,f);
}


void  IdlToCpp::printWhatItContainInH(Container* c,FilePair& f){
  if(!*f.h){
    std::cout<<"The File must be already open in printWhatItContainInH !"<<std::endl;
    std::terminate();
  }
  const std::vector<Item*> Content=c->getContent();
  std::vector<Item*>::const_iterator end=Content.cend();
  for(std::vector<Item*>::const_iterator it=Content.cbegin();it!=end;++it){
    *f.h<<(*it)->Declaration()<<";\n";
  }
  *f.h<<"\n";
}

void IdlToCpp::printWhatItContainIncpp(Container* c,FilePair& f){  
  *f.cpp<<"\n";
  const std::vector<Item*> Content=c->getContent();
  std::vector<Item*>::const_iterator end=Content.cend();
  for(std::vector<Item*>::const_iterator it=Content.cbegin();it!=end;++it){
    if((*it)->isFunction()){
      *f.cpp<<(*it)->Declaration()<<"{\n Todo\n";
      
      if((*it)->getType()!="void"){
	*f.cpp<<"return "<<(*it)->getType()<<" a;\n";
      }

      *f.cpp<<"}\n";
      
    }
  }
  *f.cpp<<"\n";
}
