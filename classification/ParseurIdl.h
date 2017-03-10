#ifndef __ParseurIdl_h__
#define __ParseurIdl_h__

#include "Atom.h"
#include "ContainerInherit.h"
#include "Function.h"
#include "Item.h"


#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include <exception>
#include <stack>

class ParseurIdl{
 private:
  //Only get access
  std::vector<Container> file;



  //parse function, not to be avaible.
  void multiplePop(int numberOfTime,Container*& endOfPile);
  void emptyStack(Container*& endOfPile);
  std::string FileToString(std::string fileName);
  void fillMe(std::string ToBeParse);
  Item* createItem(std::string line);
  std::string fillMeWasHarderThanExpected(std::string& toBeParse,Container*& endOfPile);
  int getDepth(std::smatch& res)const;
  void showMeTheTrueIdentityOfYourItems();
  void addItemInStack(Item*& I);

  //regex expr, to avoid multiple creation of the same thing.
  static const std::regex exprLine;
  static const std::regex exprSemiColon;
  static const std::regex exprGetLine;

  static const std::regex exprParenthesis;
  static const std::regex exprFunction;
  static const std::regex exprAtom;
  static const std::regex exprC_E_I;
  static const std::regex exprComponent;
  static const std::regex exprException;
  
  static const std::regex exprInterface;
  
  //Variables, no access to them
  std::stack<Container*> S;  
  static bool isContainerFlag;
 public:
  ParseurIdl(std::string fileToParse);
  const std::vector<Container> getFile()const;  
  void showMeThatFile()const;
};


#endif
