#ifndef __IDLTOCPP_H__
#define __IDLTOCPP_H__

#include "ParseurIdl.h"
#include "FilePair.h"


class IdlToCpp{
 private:
  ParseurIdl p;
  std::string directoryName;
  std::vector<std::string> NameFileCreated;//For makefile generation
  
  void printWhatItContainInH(Container* c,FilePair* f,bool isInterface=false);
  void printWhatItContainInCpp(Container* c,FilePair* f,bool isInterface=false);

  void CompleteInheritance();//check if it does implement some interfaces beforehand

  void ItemTreatment(Item* i,FilePair* f);
  void FunctionTreatmentInH(Function* func,FilePair* f,bool isInterface=false);
  void FunctionTreatmentInCpp(Function* func,FilePair* f,std::string Class,bool isInterface=false);
  void AttributeTreatmentInH(Atom* Attribute,FilePair* f,bool isInterface=false);
  void AttributeTreatmentInCpp(Atom* Attribute,FilePair* f,std::string Class,bool isInterface=false);

  void ExceptionTreatment(Container* Exception);
  void ExceptionTreatmentInH(Container* Exception,FilePair* f);
  void ExceptionTreatmentInCpp(Container* Exception,FilePair* f);

  void InterfaceTreatment(Container* Interface);
  void InterfaceTreatmentInH(Container* Interface,FilePair* f);
  void InterfaceTreatmentInCpp(Container* Interface,FilePair* f);

  void ComponentTreatment(Container* Component);
  void ComponentTreatmentInH(Container* Component,FilePair* f);
  void ComponentTreatmentInCpp(Container* Component,FilePair* f);

  void IterateOverContainer(Container* c,FilePair* f);
  FilePair* OpenFileDescriptors(std::string FileName,bool isInterface=false);

  std::string FunctionDeclaration(Function* f,std::string currentClass="");//If current class, we're in .cpp else, we're in .h.
  std::string showMeThatParameterCppStyle(Parameter p);

  static const std::regex exprInterface;
  static const std::regex exprComponent;
  static const std::regex exprException;
  //static const std::regex exprModule;
 public:
  IdlToCpp(std::string fileName,std::string DirectoryName="");
  void start();
  void GenerateBasicMakefile();
  void GenerateBasicMain();
  void showMeThatFile()const;
};

#endif
