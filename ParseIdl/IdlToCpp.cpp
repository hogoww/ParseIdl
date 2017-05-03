#include "IdlToCpp.h"

const std::regex IdlToCpp::exprInterface("interface",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprComponent("component",std::regex::icase|std::regex::optimize);
const std::regex IdlToCpp::exprException("exception",std::regex::icase|std::regex::optimize);
//const std::regex IdlToCpp::exprModule("module",std::regex::icase|std::regex::optimize);


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
	std::cerr<<"Identifiant \""<<s<<"\"non valide\n";
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
  
  switch(i->whoAreYou()){
  case 0:{//Item
    std::cerr<<i->getName()<<" wasn't traduce since it wasn't recognize while parsing (ignored).\n";
    break;
  }
  case 1:{//Atom
    std::cerr<<i->getName()<<" (Atome) should be in a container (ignored)!\n";
    break;
  }
  case 2:{//function
    std::cerr<<i->getName()<<" (Function) should be in a container (ignored)!\n";
   break;
  }
  case 3:{//Container
    if(std::regex_search(i->getType(),bogus,exprException)){
      ExceptionTreatment(static_cast<Container*>(i));
    }
    else{
      std::cerr<<i->Declaration()<<" should be an exception, what didn't I recognise? :( (ignored).\n";
    }
    break;
  }
  case 4:{//ContainerInherit
    if(std::regex_search(i->getType(),bogus,exprComponent)){
      ComponentTreatment(static_cast<ContainerInherit*>(i));
      break;
    }
    if(std::regex_search(i->getType(),bogus,exprInterface)){
      InterfaceTreatment(static_cast<ContainerInherit*>(i));
      break;
    }
    std::cerr<<"if this isn't an Interface nor a Component, what is it? :O\n";
    break;
  }
  }
}




std::string toUpper(std::string s){//Just to be more legible
  return IDStringToCharUpper(s);
}

void IdlToCpp::InterfaceTreatment(Container* Interface){
  std::SAY<<"i'm creating an Interface file!"<<std::endl;
  std::string InterfaceName=Interface->getName();
  FilePair* f=OpenFileDescriptors(InterfaceName,true);
  InterfaceTreatmentInH(Interface,f);
  //InterfaceTreatmentInCpp(Interface,f);//since it's suppose to not exit.
  f->deleteCpp();//since we systematicly do an equivalent to touch
  delete f;
}

void IdlToCpp::InterfaceTreatmentInH(Container* Interface,FilePair* f){
  std::string InterfaceName=Interface->getName();
  std::string upperName=toUpper(InterfaceName);
  //multidefinition Controle
  *f->h<<"#ifndef __"<<upperName<<"_H__\n";
  *f->h<<"#define __"<<upperName<<"_H__\n";

  *f->h<<"\n";//start Includes

  *f->h<<"#include <exception>\n";
  *f->h<<"#include <string>\n";
  *f->h<<"#include \"Component.h\"\n";

  //add type Controle for more inclusions 

  *f->h<<"\n";//end Includes

  *f->h<<"class "<<InterfaceName<<"{\n";//start class

  //class
  *f->h<<"public:\n";
  printWhatItContainInH(Interface,f,true);
  *f->h<<"};\n"<<"\n";//end class    
  *f->h<<"#endif";//end multidefinitionControl
}

void IdlToCpp::InterfaceTreatmentInCpp(Container* Interface,FilePair* f){
  //In an interface, thinking about no code for now.

  // std::string InterfaceName=Interface->getName();
  // *f->cpp<<"#include \""<<InterfaceName<<".h\"\n\n";
  // printWhatItContainInCpp(Interface,f,true);
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
  *f->h<<"#include \"Component.h\"\n";
  //add type Controle for more inclusions 


  *f->h<<"\n";//end Includes

  *f->h<<"class "<<ExceptionName<<" : std::exception {\n";//start class

  //class
  *f->h<<"private:\n";
  *f->h<<"std::string errormsg;\n";
  *f->h<<"public:\n";
  *f->h<<ExceptionName<<"(std::string errorMsg);\n";
  *f->h<<"virtual ~"<<ExceptionName<<"() throw();\n";
  *f->h<<"virtual const char* what() const throw();\n";
  
  printWhatItContainInH(Exception,f);
    
    
  *f->h<<"};\n\n";//end class    
  *f->h<<"#endif";//end multidefinitionControl
}

void IdlToCpp::ExceptionTreatmentInCpp(Container* Exception,FilePair* f){
  std::string ExceptionName=Exception->getName();

  *f->cpp<<"#include \""<<ExceptionName<<".h\"\n";
  *f->cpp<<ExceptionName<<"::"<<ExceptionName<<"(std::string errorMsg):errormsg(errorMsg){\n"<<"}\n";
  *f->cpp<<ExceptionName<<"::~"<<ExceptionName<<"() throw (){\n"<<"}\n";
  *f->cpp<<"const char* "<<ExceptionName<<"::what() const throw (){\n"<<" return errormsg.c_str();}\n";
  printWhatItContainInCpp(Exception,f);
}


void  IdlToCpp::printWhatItContainInH(Container* c,FilePair* f,bool isInterface){
  if(!*f->h){
    std::cout<<"The File must be already open in printWhatItContainInH !\n";
    std::terminate();
  }
  const std::vector<Item*> Content=c->getContent();
  std::vector<Item*>::const_iterator end=Content.cend();
  for(std::vector<Item*>::const_iterator it=Content.cbegin();it!=end;++it){
    switch((*it)->whoAreYou()){
    case 0:{//Item
      std::cerr<<(*it)->getName()<<" wasn't traduce since it wasn't recognize while parsing (ignored).\n";
      break;
    }
    case 1:{//atom
      AttributeTreatmentInH(static_cast<Atom*>(*it),f,isInterface);
      break;
    }
    case 2:{//Function
      FunctionTreatmentInH(static_cast<Function*>(*it),f,isInterface);
      break;
    }
    case 3:{//Container
      std::cerr<<"Traductor doesn't support inner stuff yet.( "<<(*it)->Declaration()<<" ) (ignored)\n";
      break;
    }
    case 4:{//ContainerInherit
      std::cerr<<"Traductor doesn't support inner stuff yet.( "<<(*it)->Declaration()<<" ) (ignored)\n";
      break;
    }

    }
    *f->cpp<<"\n";
  }
  *f->h<<"\n";
}

void IdlToCpp::printWhatItContainInCpp(Container* c,FilePair* f,bool isInterface){  
  *f->cpp<<"\n";
  std::string Name=c->getName();
  const std::vector<Item*> Content=c->getContent();
  std::vector<Item*>::const_iterator end=Content.cend();
  for(std::vector<Item*>::const_iterator it=Content.cbegin();it!=end;++it){
    switch((*it)->whoAreYou()){
    case 0:{//item
      std::cerr<<(*it)->getName()<<" wasn't traduce since it wasn't recognize while parsing (ignored).\n";
      break;
    }
    case 1:{//atom
      AttributeTreatmentInCpp(static_cast<Atom*>(*it),f,Name);
      break;
    }
    case 2:{//function
      FunctionTreatmentInCpp(static_cast<Function*>(*it),f,c->getName());
      break;
    }
    case 3:{//container
      std::cerr<<"Traductor doesn't support inner stuff yet.( "<<(*it)->Declaration()<<" ) (ignored)\n";
      break;
    }
    case 4:{//ContainerInherit
      std::cerr<<"Traductor doesn't support inner stuff yet.( "<<(*it)->Declaration()<<" ) (ignored)\n";
      break;
    }

    }
    *f->cpp<<"\n";
  }
}

void IdlToCpp::FunctionTreatmentInCpp(Function* func,FilePair* f,std::string Class,bool isInterface){
  *f->cpp<<(FunctionDeclaration(func,Class))<<"{\n"<<"//Todo\n";
  if(func->getType()!="void"){
    *f->cpp<<func->getType()<<" tempReturn;\n";
    *f->cpp<<"return tempReturn;\n";
  }
  *f->cpp<<"}\n";
}

void IdlToCpp::FunctionTreatmentInH(Function* func,FilePair* f,bool isInterface){
  *f->h<<FunctionDeclaration(func)<<(isInterface?"=0":"")<<";\n";
}

FilePair* IdlToCpp::OpenFileDescriptors(std::string FileName,bool isInterface){
  FilePair* res=new FilePair();
  res->connectFiles(FileName);
  if(!isInterface)
    NameFileCreated.push_back(FileName);
  return res;
}


void IdlToCpp::GenerateBasicMakefile(){
  //std::SAY<<"I'm generating a Makefile!"<<std::endl;
  // if(!NameFileCreated.size()){
  //   std::cerr<<"No files created, so no Makefile created either.\n";
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
  m<<" Component.cpp main.cpp";
  m<<"\n\n\n";

  m<<"all : $(PROGNAME)\n\n";
  m<<".cpp.o : $(CC) $(FLAGS) -c $^\n\n";
  m<<"$(PROGNAME) : $(SOURCES:.cpp=.o)\n\t$(CC) $(SOURCES:.cpp=.o) $(FLAGS) -o $(PROGNAME)\n\n";
  m<<"clean :\n\t@rm -f $(PROGNAME) *.o *~ *.h.gch *\\#\n\t@ls\n\n";
  m<<"cc:\n\tmake clean\n\t@make al\n\n"; 
}

void IdlToCpp::GenerateBasicMain(){
  // if(!NameFileCreated.size()){
  //   std::cerr<<"No files created, so no main created either.\n";
  //   return;
  // }

  std::ofstream m;
  std::string path("./");
  path+=directoryName+"/main.cpp";
  m.open(path);

  m<<"\n\nint main()\n{\nreturn 0;\n}"; 
}

void IdlToCpp::AttributeTreatmentInH(Atom* Attribute,FilePair* f,bool isInterface){
  *f->h<<"\n";
  std::string AttribUsage=Attribute->getUsage();
  if(AttribUsage=="attribute"){
    if(isInterface){
      std::cerr<<"There shouldn't be any attribute types of attributes inside an interface ("<<Attribute->Declaration()<<").\n";
    }
    else{
      *f->h<<Attribute->getType()<<" "<<Attribute->getName()<<";\n";
      return;
    }
  }
  if(AttribUsage=="uses"){
    if(isInterface){
      std::cerr<<"There shouldn't be any uses types of attributes inside an interface ("<<Attribute->Declaration()<<").\n";
    }
    else{
      *f->h<<Attribute->getType()<<"* "<<Attribute->getName()<<";\n";
      *f->h<<"void connect_"<<Attribute->getName()<<"("<<Attribute->getType()<<"* a"<<") throw (Component::AlreadyConnected);\n";
      *f->h<<Attribute->getType()<<"* disconnect_"<<Attribute->getName()<<"() throw ( Component::NoConnection );\n";
      *f->h<<Attribute->getType()<<"* get_connection_"<<Attribute->getName()<<"() const;\n";
      return;
    }
  }
  if(AttribUsage=="provides"){
    //Nothing to do in .h, since it's inherit
    return;
  }

  if(AttribUsage=="consumes"){
    std::cerr<<"consumes (Event system) not supported by traductor yet\n";
    return;
  }

  if(AttribUsage=="publishes"){
    std::cerr<<"publishes (Event system) not supported by traductor yet\n";
    return;
  }

  if(AttribUsage=="emits"){
    std::cerr<<"emits (Event system) not supported by traductor yet\n";
    return;
  }
}

void IdlToCpp::AttributeTreatmentInCpp(Atom* Attribute,FilePair* f,std::string Class,bool isInterface){
  *f->cpp<<"\n";
  std::string AttribUsage=Attribute->getUsage();
  if(AttribUsage=="attribute"){
    if(isInterface){
      std::cerr<<"There shouldn't be any attribute types of attributes inside an interface ("<<Attribute->Declaration()<<").\n";
    }
    else{
    }
    //Nothing to do there. Maybe add in a constructor down the way...
    //*f->h<<Attribute->getType()<<" "<<AttribUsage<<";\n";
    return;
  }

  if(AttribUsage=="uses"){
    if(isInterface){
      std::cerr<<"There shouldn't be any uses types of attributes inside an interface ("<<Attribute->Declaration()<<").\n";
    }
    else{
      *f->cpp<<"void "<<Class<<"::connect_"<<Attribute->getName()<<"("<<Attribute->getType()<<"* a"<<") throw ( Component::AlreadyConnected ){\n";
      *f->cpp<<"if("<<Attribute->getName()<<"){\n";
      *f->cpp<<" throw Component::AlreadyConnected(\""<<Attribute->getName()<<"\");\n";
      *f->cpp<<"}\n";
      *f->cpp<<"else{\n";
      *f->cpp<<"this->"<<Attribute->getName()<<"=a;\n";
      *f->cpp<<"}\n";
      *f->cpp<<"}\n";

      *f->cpp<<"\n";

      *f->cpp<<Attribute->getType()<<"* "<<Class<<"::disconnect_"<<Attribute->getName()<<"() throw ( Component::NoConnection ){\n";
      *f->cpp<<"if("<<Attribute->getName()<<"){\n";
      *f->cpp<<"this->"<<Attribute->getName()<<"=NULL;\n";
      *f->cpp<<"}\n";
      *f->cpp<<"else{\n";
      *f->cpp<<" throw Component::NoConnection(\""<<Attribute->getName()<<"\");\n";
      *f->cpp<<"}\n";
      *f->cpp<<"}\n";

      *f->cpp<<"\n";

      *f->cpp<<Attribute->getType()<<"* "<<Class<<"::get_connection_"<<Attribute->getName()<<"() const{\n";
      *f->cpp<<"return "<<"this->"<<Attribute->getName()<<";\n";
      *f->cpp<<"}\n";
      return;
    }
  }
  if(AttribUsage=="provides"){
    //search the interface to add here.
    return;
  }

  if(AttribUsage=="consumes"){
    std::cerr<<"consumes (Event system) not supported by traductor yet\n";
    return;
  }

  if(AttribUsage=="publishes"){
    std::cerr<<"publishes (Event system) not supported by traductor yet\n";
    return;
  }

  if(AttribUsage=="emits"){
    std::cerr<<"emits (Event system) not supported by traductor yet\n";
    return;
  }
}


std::string IdlToCpp::FunctionDeclaration(Function* f,std::string currentClass){
  std::string res=f->getType();
  res+=" ";
  if(!currentClass.empty()){
    res+=currentClass+"::";
  }
  res+=f->getName();
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



void IdlToCpp::ComponentTreatment(Container* Component){
  std::SAY<<"i'm creating an Component file!"<<std::endl;
  // FilePair f;
  // f.connectFiles(ComponentName);
  FilePair* f=OpenFileDescriptors(Component->getName());
  ComponentTreatmentInH(Component,f);
  ComponentTreatmentInCpp(Component,f);
  delete f;
}

void IdlToCpp::ComponentTreatmentInH(Container* Component,FilePair* f){
  std::string ComponentName=Component->getName();
  std::string upperName=toUpper(ComponentName);
  //multidefinition Controle
  *f->h<<"#ifndef __"<<upperName<<"_H__\n";
  *f->h<<"#define __"<<upperName<<"_H__\n";

  *f->h<<"\n";//start Includes

  *f->h<<"#include <string>\n";
  *f->h<<"#include \"Component.h\"\n";
  //add type Controle for more inclusions 


  *f->h<<"\n";//end Includes

  *f->h<<"class "<<ComponentName<<"{\n";//start class

  //class
  *f->h<<"public:\n";
  
  printWhatItContainInH(Component,f);
    
    
  *f->h<<"};\n\n";//end class    
  *f->h<<"#endif";//end multidefinitionControl
}

void IdlToCpp::ComponentTreatmentInCpp(Container* Component,FilePair* f){
  std::string ComponentName=Component->getName();

  *f->cpp<<"#include \""<<ComponentName<<".h\"\n";
  printWhatItContainInCpp(Component,f);
}
