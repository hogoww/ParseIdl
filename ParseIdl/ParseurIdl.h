#ifndef __ParseurIdl_h__
#define __ParseurIdl_h__

#include "Atom.h"
#include "ContainerInherit.h"
#include "Function.h"
#include "Item.h"
#include "DidNotFoundFileExcep.h"

#include <string>
#include <vector>
#include <set>
#include <regex>
#include <iostream>
#include <fstream>
#include <exception>
#include <stack>

class ParseurIdl{
 private:
  //Only get access
  std::set<std::string>* includes;
  std::vector<Container*> file;
  std::string fileName;
  //std::vector<std::string> includes;

  //parse function, not to be avaible.
  void multiplePop(int& numberOfTime,Container*& endOfPile);
  void emptyStack(Container*& endOfPile);
  std::string FileToString(std::string fileName) throw (DidNotFoundFileExcep);
  void fillMe(std::string& ToBeParse);
  Item* createItem(std::string line);
  std::string fillMeWasHarderThanExpected(std::string& toBeParse,Container*& endOfPile);
  int getDepth(std::smatch& res)const;
  void addItemInStack(Item*& I);
  void nameAppearedTwice(std::string& name);//Terminate, is an error;
  std::set<std::string>* getIncludes(std::string& ToBeParse);
  void getFile(std::string& fileame,std::string& content) throw (DidNotFoundFileExcep);
  void treatmentIncludedFiles(std::string name);
  void launchTreatmentIncludedFiles(std::set<std::string>* newIncludes);
  void getNamesInIncludedFiles(std::string& content);  

  //regex expr, to avoid multiple creation of the same thing.
  static const std::regex exprLine;
  static const std::regex exprSemiColon;
  static const std::regex exprGetLine;
  static const std::regex exprSemiColonAndBackN;

  static const std::regex exprInclude;
  static const std::regex exprParenthesis;
  static const std::regex exprFunction;
  static const std::regex exprAtom;
  static const std::regex exprC_E_I;
  static const std::regex exprComponent;
  static const std::regex exprException;
  
  static const std::regex exprInterface;
  static const std::regex exprIncludedWithColon;
  static const std::regex exprIncludedFunction;
  static const std::regex exprIncludedNormal;
  
  //Variables, no access to them
  std::stack<Container*>* S;//set to NULL after parsing is done.
  std::set<std::string>* componentNames;

  static bool isContainerFlag;

 public:
  ParseurIdl(std::string fileToParse);
  virtual ~ParseurIdl();
  const std::vector<Container*> getFileContent()const;  
  void showMeThatFile()const;
  std::string getFileName()const;
  void checkForInterfaceInheritance();//when using a langage that implements interfaces with multiple inheritance
};


#endif
