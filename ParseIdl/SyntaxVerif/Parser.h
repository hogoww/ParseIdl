#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <vector>
#include "Cursor.h"

struct KWList {
	std::string value;
	explist parents;
	struct KWList* next;
};

void showCur(ruleCursor* c);
void showExp(Rule* r);

class Parser {
	public :
	Parser();
	~Parser();
	Rule* addRule(std::string name);
	KWList* getKeyWords();
	KWList* getRules();
	seqList* getCursors();
	int init(std::ifstream& file);
	int extract(std::ifstream& file);
	void addConj(expElem* &cur, expElem* &res);
	void closeBlock(expElem* cur, explist parStack);
	void closeDisj(expElem* cur);
	void blacklist(std::ifstream& file);
	bool banned(std::string word);
	int parse(std::ifstream& file);
	void step(explist el);
	bool endParsing();

	private :
	KWList* keywords;
	std::vector <std::string> blkw;
	KWList* rules;
	expElem* root;
	seqList* cursors;
	Rule* id;
	Rule* digit;
	Rule* charlit;
	Rule* strlit;
};

#endif
