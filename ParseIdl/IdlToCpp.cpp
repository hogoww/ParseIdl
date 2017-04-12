#include "IdlToCpp.h"

const std::regex IdlToCpp::exprInterface("interface",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprComponent("component",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprException("exception",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprModule("module",std::regex::icase|std::regex::optimize);


#define SAY cout//For output like "i've done something!" , for quick debug

/******Constructeurs:******/


/* constructeurs public*/
IdlToCpp::IdlToCpp(std::string fileName,std::string DN):p(fileName),directoryName(DN),NameFileCreated(){
  directoryName="temp";
}


/******Methodes:******/
/* methodes private*/

/*private*/void IdlToCpp::CompleteInheritance(){
  p.checkForInterfaceInheritance();
}

void IdlToCpp::showMeThatFile() const{
  p.showMeThatFile();
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

void IdlToCpp::IterateOverContainer(Container* c,FilePair* f){//Shouldn't be usefull since we're only taking a one at a time container
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

void IdlToCpp::InterfaceTreatment(Container* Interface){
  std::SAY<<"i'm creating an Interface file!"<<std::endl;
  std::string InterfaceName=Interface->getName();
  FilePair* f=OpenFileDescriptors(InterfaceName);
  std::string upperName=toUpper(InterfaceName);
  //multidefinition Controle
  *f->h<<"#ifndef __"<<upperName<<"_H__\n";
  *f->h<<"#define __"<<upperName<<"_H__\n";

  *f->h<<"\n";//start Includes

  *f->h<<"#include <exception>\n";
  *f->h<<"#include <string>\n";
  //add type Controle for more inclusions 


  *f->h<<"\n";//end Includes

  *f->h<<"class "<<InterfaceName<<" : std::exception {\n";//start class

  //class
  *f->h<<"private:\n";
  *f->h<<"std::string errormsg;\n";
  *f->h<<"\npublic:\n";
  *f->h<<InterfaceName<<"(std::string errorMsg);\n";
  *f->h<<"virtual ~"<<InterfaceName<<"() throw();\n";
  *f->h<<"virtual const char* what() const throw();\n";
  
  //printWhatItContainInH(Interface,*f);
    
    
  *f->h<<"};\n\n";//end class    
  *f->h<<"#endif";//end multidefinitionControl



  *f->cpp<<"#include \""<<InterfaceName<<".h\"\n\n";
  *f->cpp<<InterfaceName<<"::"<<InterfaceName<<"(std::string errorMsg):errormsg(errorMsg){\n}\n\n";
  *f->cpp<<InterfaceName<<"::~"<<InterfaceName<<"() throw (){\n}\n\n";
  *f->cpp<<"const char* "<<InterfaceName<<"::what() const throw (){\n return errormsg.c_str();\n}\n";
  printWhatItContainIncpp(Interface,*f);
  delete f;
}

void IdlToCpp::ExceptionTreatment(Container* Exception){
  std::SAY<<"i'm creating an Exception file!"<<std::endl;
  // FilePair f;
  // f.connectFiles(ExceptionName);
  FilePair* f=OpenFileDescriptors(Exception->getName());
  ExceptionTreatmentInH(Exception,f);
  ExceptionTreatmentInCpp(Exception,f);
  delete f;
}

void IdlToCpp::ExceptionTreatmentInH(Container* Exception,FilePair* f){
  std::string ExceptionName=Exception->getName();
  std::string upperName=toUpper(ExceptionName);
  //multidefinition Controle
  *f->h<<"#ifndef __"<<upperName<<"_H__\n";
  *f->h<<"#define __"<<upperName<<"_H__\n";

  *f->h<<"\n";//start Includes

  *f->h<<"#include <exception>\n";
  *f->h<<"#include <string>\n";
  //add type Controle for more inclusions 


  *f->h<<"\n";//end Includes

  *f->h<<"class "<<ExceptionName<<" : std::exception {\n";//start class

  //class
  *f->h<<"private:\n";
  *f->h<<"std::string errormsg;\n";
  *f->h<<"\npublic:\n";
  *f->h<<ExceptionName<<"(std::string errorMsg);\n";
  *f->h<<"virtual ~"<<ExceptionName<<"() throw();\n";
  *f->h<<"virtual const char* what() const throw();\n";
  
  //printWhatItContainInH(Exception,*f);
    
    
  *f->h<<"};\n\n";//end class    
  *f->h<<"#endif";//end multidefinitionControl
}

void IdlToCpp::ExceptionTreatmentInCpp(Container* Exception,FilePair* f){
  std::string ExceptionName=Exception->getName();

  *f->cpp<<"#include \""<<ExceptionName<<".h\"\n\n";
  *f->cpp<<ExceptionName<<"::"<<ExceptionName<<"(std::string errorMsg):errormsg(errorMsg){\n}\n\n";
  *f->cpp<<ExceptionName<<"::~"<<ExceptionName<<"() throw (){\n}\n\n";
  *f->cpp<<"const char* "<<ExceptionName<<"::what() const throw (){\n return errormsg.c_str();\n}\n";
  printWhatItContainIncpp(Exception,*f);
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
      FunctionTreatmentInCpp(static_cast<Function*>(c));
    }
    else(
  }
  *f.cpp<<"\n";
}

void IdlToCpp::FunctionTreatmentInCpp(Function* func,FilePair f){
  *f.cpp<<(FunctionDeclaration(func))<<"{"<<std::endl<<"Todo"<<std::endl;
  if(func->getType()!="void"){
    *f.cpp<<"return "<<func->getType()<<" a;"<<std::endl;
  }
  *f.cpp<<"}\n";
}

void IdlToCpp::FunctionTreatmentInH(Function* func,FilePair f){
  *f.h<<FunctionDeclaration(func)<<";"<<std::endl;
}

FilePair* IdlToCpp::OpenFileDescriptors(std::string FileName){
  FilePair* res=new FilePair();
  res->connectFiles(FileName);
  NameFileCreated.push_back(FileName);
  return res;
}


void IdlToCpp::GenerateBasicMakefile(){
  //std::SAY<<"I'm generating a Makefile!"<<std::endl;
  // if(!NameFileCreated.size()){
  //   std::cerr<<"No files created, so no Makefile created either."<<std::endl;
  //   return;
  // }

  std::ofstream m;
  std::string path("./");
  path+=directoryName+"/Makefile";
  m.open(path);

  std::string compiler("g++");
  std::string flags("-Wall -ansi -pedantic");
  std::string progname("main");
  
  m<<"CC = "<<compiler<<"\n";
  m<<"PROGNAME = "<<progname<<"\n";
  m<<"FLAGS = "<<flags<<"\n";
  m<<"SOURCES = ";
  std::vector<std::string>::const_iterator end=NameFileCreated.cend();
  for(std::vector<std::string>::const_iterator it=NameFileCreated.cbegin();it!=end;++it){
    m<<*it<<".cpp ";
  }
  m<<"main.cpp";
  m<<"\n\n\n";

  m<<"all : $(PROGNAME)\n\n";
  m<<".cpp.o : $(CC) $(FLAGS) -c $^\n\n";
  m<<"$(PROGNAME) : $(SOURCES:.cpp=.o)\n\t$(CC) $(SOURCES:.cpp=.o) $(FLAGS) -o $(PROGNAME)\n\n";
  m<<"clean :\n\t@rm -f $(PROGNAME) *.o *~ *.h.gch *\\#\n\t@ls\n\n";
  m<<"cc:\n\tmake clean\n\t@make al\n\n"; 
}

void IdlToCpp::GenerateBasicMain(){
  // if(!NameFileCreated.size()){
  //   std::cerr<<"No files created, so no main created either."<<std::endl;
  //   return;
  // }

  std::ofstream m;
  std::string path("./");
  path+=directoryName+"/main.cpp";
  m.open(path);

  m<<"\n\nint main()\n{\nreturn 0;\n}"; 
}

void IdlToCpp::AttributeTreatmentInH(Atom* Attribute,FilePair* f){
  std::string AttribUsage=Attribute->getUsage();
  if(AttribUsage=="attribute"){
    *f->h<<Attribute->getType()<<" "<<Attribute->getName()<<";"<<std::endl;
    return;
  }

  if(AttribUsage=="uses"){
    *f->h<<Attribute->getType()<<"* "<<Attribute->getName()<<";"<<std::endl;
    *f->h<<"void connect_"<<Attribute->getName()<<"("<<Attribute->getType()<<"* a"<<") throw (Components::AlreadyConnected);"<<std::endl;
    *f->h<<Attribute->getType()<<"* disconnect_"<<Attribute->getName()<<"( ) throw ( Components::NoConnection );"<<std::endl;
    *f->h<<Attribute->getType()<<"* get_connection_"<<Attribute->getName()<<"() const;"<<std::endl;
    return;
  }

  if(AttribUsage=="provides"){
    //Nothing to do in .h, since it's inherit
    return;
  }

  if(AttribUsage=="consumes"){
    std::cerr<<"consumes (Event system) not supported by traductor yet"<<std::endl;
    return;
  }

  if(AttribUsage=="publishes"){
    std::cerr<<"publishes (Event system) not supported by traductor yet"<<std::endl;
    return;
  }

  if(AttribUsage=="emits"){
    std::cerr<<"emits (Event system) not supported by traductor yet"<<std::endl;
    return;
  }
}

void IdlToCpp::AttributeTreatmentInCpp(Atom* Attribute,FilePair* f,std::string Class){
  std::string AttribUsage=Attribute->getUsage();
  if(AttribUsage=="attribute"){
    //Nothing to do there. Maybe add in a constructor down the way...
    //*f->h<<Attribute->getType()<<" "<<AttribUsage<<";\n";
    return;
  }

  if(AttribUsage=="uses"){
    *f->cpp<<"void connect_"<<Attribute->getName()<<"("<<Attribute->getType()<<"* a"<<") throw ( Components::AlreadyConnected ){"<<std::endl;
    *f->cpp<<"if(a){"<<std::endl;
    *f->cpp<<" throw AlreadyConnected("<<Attribute->getName()<<");"<<std::endl;
    *f->cpp<<"}"<<std::endl;
    *f->cpp<<"else{"<<std::endl;
    *f->cpp<<Attribute->getName()<<"=a;"<<std::endl;
    *f->cpp<<"}"<<std::endl;
    *f->cpp<<"}"<<std::endl;

    *f->cpp<<std::endl;

    *f->cpp<<Attribute->getType()<<"* disconnect_"<<Attribute->getName()<<"( ) throw ( Components::NoConnection ){";
    *f->cpp<<"if(a){"<<std::endl;
    *f->cpp<<Attribute->getName()<<"=NULL;"<<std::endl;
    *f->cpp<<"}"<<std::endl;
    *f->cpp<<"else{"<<std::endl;
    *f->cpp<<" throw NoConnection("<<Attribute->getName()<<");"<<std::endl;
    *f->cpp<<"}"<<std::endl;
    *f->cpp<<"}"<<std::endl;

    *f->cpp<<std::endl;

    *f->cpp<<Attribute->getType()<<"* get_connection_"<<Attribute->getName()<<"() const;"<<std::endl;
    *f->cpp<<"return "<<Attribute->getName()<<";"<<std::endl;
    return;
  }

  if(AttribUsage=="provides"){
    //search the interface to add here.
    return;
  }

  if(AttribUsage=="consumes"){
    std::cerr<<"consumes (Event system) not supported by traductor yet"<<std::endl;
    return;
  }

  if(AttribUsage=="publishes"){
    std::cerr<<"publishes (Event system) not supported by traductor yet"<<std::endl;
    return;
  }

  if(AttribUsage=="emits"){
    std::cerr<<"emits (Event system) not supported by traductor yet"<<std::endl;
    return;
  }
}


std::string IdlToCpp::FunctionDeclaration(Function* f,std::string currentClass){
  std::string res=f->getType();
  res+=" ";
  if(!currentClass.empty()){
    res+=currentClass+"::";
  }
  res=f->getName();
  const std::vector<Parameter> Param=f->getParam();
  const std::vector<std::string> Exception=f->getException();

  res+="(";
  if(Param.size()){
    std::vector<Parameter>::const_iterator end=Param.cend();
    res+=showMeThatParameterCppStyle(*(Param.cbegin()));
    for(std::vector<Parameter>::const_iterator it=++Param.cbegin();it!=end;++it){
      res+=", "+showMeThatParameterCppStyle(*it);
    }
  }
  res+=")";
  
  if(Exception.size()){//forcement une
    std::vector<std::string>::const_iterator end=Exception.cend();
    res+=" raises ("+*Exception.begin();
    for(std::vector<std::string>::const_iterator it=++Exception.cbegin();it!=end;++it) {
      res+=", "+*it;
    }
    res+=")";
  }
  return res;
}


std::string IdlToCpp::showMeThatParameterCppStyle(Parameter p){
  std::string res="";
  switch(p.getTypeParameter()){
  case Parameter::TypeParam::In :
    {
      res+=p.getType()+" "+p.getName();
      break;
    }
  case Parameter::TypeParam::Out :
    {
      res+=p.getType()+"& "+p.getName();
      break;
    }
  case Parameter::TypeParam::InOut :
    {
      res+=p.getType()+"& "+p.getName();
      break;
    }
  }
  return res;
}
