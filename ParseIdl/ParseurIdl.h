#ifndef __ParseurIdl_h__
#define __ParseurIdl_h__

#include "Atom.h"
#include "ContainerInherit.h"
#include "Function.h"
#include "Item.h"


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
  std::vector<Container*> file;
  std::string fileName;
  std::vector<std::string> includes;

  //parse function, not to be avaible.
  void multiplePop(int& numberOfTime,Container*& endOfPile);
  void emptyStack(Container*& endOfPile);
  std::string FileToString(std::string fileName);
  void fillMe(std::string& ToBeParse);
  Item* createItem(std::string line);
  std::string fillMeWasHarderThanExpected(std::string& toBeParse,Container*& endOfPile);
  int getDepth(std::smatch& res)const;
  void addItemInStack(Item*& I);
  void nameAppearedTwice(std::string& name);//Terminate, is an error;
  void getIncludes(std::string& ToBeParse);

  //regex expr, to avoid multiple creation of the same thing.
  static const std::regex exprLine;
  static const std::regex exprSemiColon;
  static const std::regex exprGetLine;

  static const std::regex exprInclude;
  static const std::regex exprParenthesis;
  static const std::regex exprFunction;
  static const std::regex exprAtom;
  static const std::regex exprC_E_I;
  static const std::regex exprComponent;
  static const std::regex exprException;
  
  static const std::regex exprInterface;
  
  //Variables, no access to them
  std::stack<Container*>* S;//set to NULL after parsing is done.
  std::set<std::string>* componentNames;
  static bool isContainerFlag;

 public:
  ParseurIdl(std::string fileToParse);
  virtual ~ParseurIdl();
  const std::vector<Container*> getFile()const;  
  void showMeThatFile()const;
  /* std::vector<std::string> getAllIdInFile()const; */
};


#endif
