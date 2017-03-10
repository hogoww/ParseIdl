#ifndef _GRAMMAR_H
#define _GRAMMAR_H

#include "rule.h"
#include <vector>
#include <fstream>

class Grammar{
 private:
  std::vector<Rule> Rules;
 public:
  Grammar();
  ~Grammar();
  void addRule(Rule r);
  void getGrammar(std::string filename);
  void Depth();
  void DepthRec(bool* seen,int* time);
  void showMeThatGrammar() const;
};



#endif
