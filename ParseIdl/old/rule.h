#ifndef RULE_H
#define RULE_H

#include <vector>
#include <string>
#include <exception>
#include <iostream>

class Rule{
 private:
  std::string nom;
  std::string regex;

  bool atome;
 public:
  Rule();
  ~Rule();
  void setName(std::string nom);
  void setRegex(std::string regex);
  void setAtome();
  void reset();
  bool isAtome() const;
  std::vector<std::string>* checkIfIsAtome() const;
  std::string toString() const;
};

#endif
