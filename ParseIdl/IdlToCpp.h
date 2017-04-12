#ifndef __IDLTOCPP_H__
#define __IDLTOCPP_H__

#include "ParseurIdl.h"
#include "FilePair.h"


class IdlToCpp{
 private:
  ParseurIdl p;
  std::string directoryName;
  std::vector<std::string> NameFileCreated;//For makefile generation
  
  void printWhatItContainInH(Container* c,FilePair& f);
  void printWhatItContainIncpp(Container* c,FilePair& f);

  void CompleteInheritance();//check if it does implement some interfaces beforehand

  void ItemTreatment(Item* i,FilePair* f);
  void FunctionTreatmentInH(Function* func,FilePair f);
  void FunctionTreatmentInCpp(Function* func,FilePair f);

  void ExceptionTreatment(Container* Exception);
  void ExceptionTreatmentInH(Container* Exception,FilePair* f);
  void ExceptionTreatmentInCpp(Container* Exception,FilePair* f);

  void InterfaceTreatment(Container* Interface);
  void AttributeTreatmentInH(Atom* Attribute,FilePair* f);
  void AttributeTreatmentInCpp(Atom* Attribute,FilePair* f,std::string Class);

  void IterateOverContainer(Container* c,FilePair* f);
  FilePair* OpenFileDescriptors(std::string FileName);

  std::string FunctionDeclaration(Function* f,std::string currentClass="");//If current class, we're in .cpp else, we're in .h.
  std::string showMeThatParameterCppStyle(Parameter p);

  static const std::regex exprInterface;
  static const std::regex exprComponent;
  static const std::regex exprException;
  static const std::regex exprModule;
 public:
  IdlToCpp(std::string fileName,std::string DirectoryName="");
  void start();
  void GenerateBasicMakefile();
  void GenerateBasicMain();
  void showMeThatFile()const;
};

#endif
