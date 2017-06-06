#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <string>

struct expElem {
	char type() {return t;}
	char t;
	char quant;
	expElem* parent;
};

struct litteral : expElem {
	litteral() {t = 0;}
	std::string value;
};

struct Rule;
struct nonTerm : expElem {
	nonTerm() {t = 1;}
	Rule* value;
};

struct conjunction;
struct disjunction : expElem {
	disjunction() {t = 2;}
	expElem* value;
	disjunction* next;
};

struct conjunction : public expElem {
	conjunction() {t = 3;}
	expElem* value;
	conjunction* next;
};

struct ExpressionList {
	expElem* value;
	struct ExpressionList* next;
};

typedef struct ExpressionList* explist;

struct Rule {
	std::string name;
	nonTerm* handle;
	expElem* exp;
	explist parents;
};

#endif
