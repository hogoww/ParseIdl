#include "IdlToCpp.h"

const std::regex IdlToCpp::exprInterface("interface",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprComponent("component",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprException("exception",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprModule("module",std::regex::icase|std::regex::optimize);


/******Constructeurs:******/


/* constructeurs public*/
IdlToCpp::IdlToCpp(std::string fileName,std::string DN):p(fileName),currentNamespace(),directoryName(DN){
}


/******Methodes:******/
/* methodes private*/

/*private*/void IdlToCpp::CompleteInheritance(){
  p.checkForInterfaceInheritance();
}


char* IDStringToCharUpper(std::string s){
  size_t len=s.length();
  char* res=new char[len];
  int charNumber;
  for(size_t i=0;i<len;++i){ 
    charNumber=(int)s[i];
    if((charNumber<91 && charNumber>64) || charNumber==95 || (charNumber>47 && charNumber<58)){//uppercase/underscore/number
      res[i]=s[i];
    }
    else{
      if(charNumber>96 && charNumber<122){
	res[i]=(char)(charNumber-32);
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
  const std::vector<Container *> c=p.getFile();
  std::vector<Container*>::const_iterator end=c.cend();
  p.fileName();
  for(std::vector<Container*>::const_iterator it=c.cbegin();it!=end;++it){
    FilePair* f=NULL;
    ItemTreatment(*it,f);
  }
}

void IdlToCpp::IterateOtherContainer(Container* c,FilePair* f){
  std::vector<Item*>::const_iterator end=c.cend();
  p.fileName();
  for(std::vector<Container*>::const_iterator it=c.cbegin();it!=end;++it){
    FilePair* f=NULL;
    ItemTreatment(*it,f);
  }
}

void IdlToCpp::ItemTreatment(Item* i,FilePair* f){
  std::smatch bogus;
  std::string name=i.getName();
  
  if(std::regex_search(name,bogus,exprException)){
    if(depth<2 && !f->currentNamespace.empty()){}
    f=new FilePair();
    ExceptionTreatment(i,f);
    delete f;
    f=NULL;
    return;
  }
  if(std::regex_search(name,bogus,exprModule)){
    f=new FilePair();
    f->depth++;
    f->currentNamespace=name;
    
    delete f;
    f=NULL;
    return;
  }

  
}

void moduleTreatment(Container* module,FilePair *f){

}



char* toUpper(std::string s){//Just to be more legible
  return IDStringToCharUpper(s);
}


void IdlToCpp::ExceptionTreatment(Container* Exception){
  if(depth<2){//not innerclass
    std::string ExceptionName=Exception->getName();
    FilePair f(ExceptionName,directoryName);
    char * upperName=toUpper(ExceptionName)
    //multidefinition Controle
    f.h<<"#ifndef __"<<upperName<<"_H\n";
    f.h<<"#define __"<<upperName<<"_H\n";
    delete upperName;

    f.h<<"\n";//start Includes

    f.h<<"#include <exception>\n";
    f.h<<"#include <string>\n";
    //add type Controle for more inclusions 
    
    if(!currentNamespace.empty()){
      f.h<<"namespace "<<currentNamespace<<"{\n";
      f.h<<"class"<<ExceptionName()<<"};\n\n";
    }
  }


  f.h<<"\n";//end Includes

  f.h<<"class "<<ExceptionName<<" : Exception{\n";//start class
    
  //class
  f.h<<"private:\n";
  f.h<<"std::string errormsg;\n";
  f.h<<"\npublic:\n";
  f.h<<ExceptionName<<"(std::string errorMsg);\n";
  f.h<<"virtual ~"<<ExceptionName<<"() throw();\n";
  f.h<<"virtual const char* what() const throw();\n";
    
    
  f.h<<"};\n";//end class    

  if(depth<2){
    f.h<<"#endif";//end multidefinitionControll
  }
}
