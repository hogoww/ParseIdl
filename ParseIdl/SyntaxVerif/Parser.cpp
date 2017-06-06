#include "Parser.h"
#include <iostream>

using namespace std;

bool alphanum(char c);
bool blank(char c);
char esc(char c); // A compl�ter ?

Rule* getRule(expElem* e) {
	while(e->parent != NULL) {e = e->parent;}
	return ((nonTerm*)e)->value;
}

void showCur(ruleCursor* c) {
	cout << getRule(c->cursor)->name << endl;
	c = c->parent;
	cout << "-----";
	while(c != NULL) {
		cout << ((nonTerm*)c->cursor)->value->name << " - ";
		c = c->parent;
	}
	cout << endl;
}

void seSwitch(expElem* e, string t) {
	expElem* i = e;
	switch(e->type()) {
		case 0 :
			cout << t << "'" << ((litteral*)e)->value << "' "
				<< (int)e->quant << " - " << e << endl;
			break;

		case 1 :
			cout << t << ((nonTerm*)e)->value->name << " "
				<< (int)e->quant << " - " << e << endl;
			break;

		case 2 :
			while(i != NULL) {
				cout << t << "| " << (int)i->quant << " - " << i << endl;
				seSwitch(((disjunction*)i)->value, t + "\t");
				i = ((disjunction*)i)->next;
			}
			break;

		case 3 :
			while(i != NULL) {
				cout << t << ". " << (int)i->quant << " - " << i << endl;
				seSwitch(((conjunction*)i)->value, t + "\t");
				i = ((conjunction*)i)->next;
			}
			break;
		default : break;
	}
}

void showExp(Rule* r) {
	cout << endl << "Rule : " << r->name << endl;
	cout << r << "-" << r->exp << endl;
	seSwitch(r->exp, "\t");
}

Parser::Parser() {
	keywords = NULL;
	rules = NULL;
	cursors = NULL;
	root = NULL;
	id = addRule("ID");
	digit = addRule("DIGIT");
	charlit = addRule("CHARLIT");
	strlit = addRule("STRLIT");
}

Parser::~Parser() {
	//Ne pas oublier de l'�crire !
}

Rule* Parser::addRule(string name) {
	KWList *cur = rules, *elem;
	Rule* rule;
	int l = name.size();
	while(cur && cur->next && name.compare(cur->next->value) >= 0) {cur = cur->next;}
	while(cur && name.substr(0, l).compare(cur->value.substr(0, l)) != 0) {l --;}
	if(cur && l == name.size()) {rule = ((nonTerm*)cur->parents->value)->value;}
	else {
		elem = new KWList;
		elem->value = name;
		cout << name << endl;
		rule = new Rule;
		rule->name = name;
		rule->handle = new nonTerm;
		((nonTerm*)rule->handle)->value = rule;
		rule->handle->quant = 0;
		rule->handle->parent = NULL;
		rule->exp = rule->handle;
		rule->parents = NULL;
		elem->parents = new ExpressionList;
		elem->parents->value = rule->handle;
		elem->parents->next = NULL;

		if(!cur || name.compare(cur->value) < 0)
		{elem->next = rules; rules = elem;}
		else {
			elem->next = cur->next;
			cur->next = elem;
		}
	}
	return rule;
}

KWList* Parser::getKeyWords() {return keywords;}
KWList* Parser::getRules() {return rules;}
seqList* Parser::getCursors() {return cursors;}

int Parser::init(ifstream& file) { // Une seule utilisation...
	
	while(!file.eof() && extract(file) != 1) {}

	// Si keywords ou rules vide, gueuler.

	/*expElem* e; KWList* tmp;
	while(rules) {
		if(!((nonTerm*)rules->parents->value)->value->parents) {
			if(root) {cout << "La grammaire a plus d'une racine" << endl; return 1;}
			root = rules->parents->value;
		}
		tmp = rules->next;
		delete rules;
		rules = tmp;
	}*/
	return 0;
}

int Parser::extract(ifstream& file) {
	string name, exp; char c = ' ';
	Rule* rule;
	explist parStack = NULL, par;
	KWList *kwle, *kwlc;
	expElem* res = NULL;
	expElem *cur = NULL, *elem;
	bool termReq = true;

	while(!file.eof() && blank(c)) {file.get(c);}

	if(alphanum(c) && (c < '0' || c > '9')) {
		while(!file.eof() && alphanum(c)) {name += c; file.get(c);}
	}

	while(!file.eof() && blank(c)) {file.get(c);}
	if(c != ':') {return 1;}

	rule = addRule(name);
	while(!file.eof() && c != ';') {
		do {file.get(c);} while(!file.eof() && blank(c));
		if(alphanum(c) && (c < '0' || c > '9')) {
			while(!file.eof() && alphanum(c)) {exp += c; file.get(c);}
		}

		if(!exp.empty()) {
			if(cur && cur->type() <= 1 && cur->parent && cur->parent->type() == 3
				&& (!parStack || cur->parent != parStack->value))
			{cur->parent->quant = cur->quant; cur = cur->parent;}
			if(!termReq) {addConj(cur, res);}

			elem = new nonTerm;
			elem->quant = 0;
			elem->parent = cur;
			if(cur != NULL) {
				if(cur->type() == 2) {((disjunction*)cur)->value = elem;}
				else {((conjunction*)cur)->value = elem;}
			}
			else {res = elem;}
			cur = elem;

			par = new ExpressionList;
			par->value = cur;
			((nonTerm*)cur)->value = addRule(exp);
			par->next = ((nonTerm*)cur)->value->parents;
			((nonTerm*)cur)->value->parents = par;

			exp.clear();
			termReq = false;
		}

		if(c == '|') {
			if(termReq) {return 1;}
			if(cur->type() == 3 && ((cur->parent == NULL && res == cur)
			|| (cur->parent && cur->parent->type() == 3
			&& ((conjunction*)cur->parent)->value == cur))) {
				elem = new disjunction;
				elem->quant = cur->quant;
				((disjunction*)elem)->value = ((conjunction*)cur)->value;
				((disjunction*)elem)->value->parent = elem;
				elem->parent = cur->parent;
				if(elem->parent != NULL) {
					if(elem->parent->type() == 2)
					{((disjunction*)elem->parent)->value = elem;}
					else {((conjunction*)elem->parent)->value = elem;}
				}
				else {res = elem;}
				delete cur; cur = elem;
			}

			while(cur->type() != 2 && cur->parent &&
			(!parStack || cur->parent != parStack->value)) {
				cur = cur->parent;
				if(cur->type() == 3 && (((conjunction*)cur)->value->type() <= 1
				|| (((conjunction*)((conjunction*)cur)->value)->next == NULL)))
				{cur->quant = ((conjunction*)cur)->value->quant;}
			}

			if(cur->type() != 2) {
				if(!cur->parent) {cur = res;}
				else {cur = ((conjunction*)cur->parent)->value;}
				expElem* elem = new disjunction;
				elem->parent = cur->parent;
				if(cur->parent) {((conjunction*)cur->parent)->value = elem;}
				else {res = elem;}
				((disjunction*)elem)->value = cur;
				if(cur->type() <= 1) {cur->parent = elem;}
				else {
					while(cur != NULL) {
						cur->parent = elem;
						cur = ((conjunction*)cur)->next;
					}
				}
				elem->quant = 0;
				cur = elem;
			}

			closeDisj(cur);
			elem = new disjunction;
			elem->quant = 0;
			((disjunction*)elem)->value = NULL;
			((disjunction*)elem)->next = NULL;
			elem->parent = cur->parent;
			((disjunction*)cur)->next = (disjunction*)elem;
			cur = elem;
			termReq = true;
		}

		else if(c == '?' || c == '*' || c == '+') {
			if(termReq) {return 1;}
			else {
				char q;
				if(c == '?') {q = 1;}
				else if(c == '*') {q = 2;}
				else {q = 3;}
				cur->quant = (cur->quant == 0 || cur->quant == q) ? q : 2;
			}
		}

		else if(c == '(') {
			if(cur && cur->type() <= 1 && cur->parent && cur->parent->type() == 3
				&& (!parStack || cur->parent != parStack->value))
			{cur->parent->quant = cur->quant; cur = cur->parent;}
			if(!termReq) {addConj(cur, res);}
			else {
				elem = new conjunction;
				elem->quant = 1;
				((conjunction*)elem)->value = NULL;
				((conjunction*)elem)->next = NULL;
				elem->parent = cur;
				if(cur) {
					if(cur->type() == 2)
					{((disjunction*)cur)->value = elem;}
					else {((conjunction*)cur)->value = elem;}
				}
				else {res = elem;}
				cur = elem;
			}

			par = new ExpressionList;
			par->next = parStack;
			par->value = cur;
			parStack = par;
			termReq = true;
		}

		else if(c == ')') {
			if(termReq) {return 1;}
			closeBlock(cur, parStack);

			par = parStack->next;
			cur = parStack->value;
			delete parStack; parStack = par;
			elem = cur; cur = ((conjunction*)elem)->value;

			if(elem->quant == 0) {
				if(cur->type() <= 1 || (cur->type() == 3 && ((conjunction*)cur)->next == NULL))
				{elem->quant = cur->quant;}
				cur = elem;
			}
			else if(cur->type() <= 1 || (cur->type() == 3 && ((conjunction*)cur)->next == NULL)) {
				cur->parent = elem->parent;
				if(elem->parent) {
					if(elem->parent->type() == 2)
					{((disjunction*)elem->parent)->value = cur;}
					else {((conjunction*)elem->parent)->value = cur;}
				}
				else {res = cur;}
				delete elem;
			}
			else {elem->quant = 0; cur = elem;}
		}

		else if(c == '\'') {
			do {
				if(file.eof()) {return 1;}
				file.get(c);
				if(c == '\\') {char e; file.get(e); exp += esc(e);}
				else {exp += c;}
			} while(c != '\'');
			exp.resize(exp.size() - 1);
			if(exp.empty()) {return 1;}

			if(cur && cur->type() <= 1 && cur->parent && cur->parent->type() == 3
				&& (!parStack || cur->parent != parStack->value))
			{cur->parent->quant = cur->quant; cur = cur->parent;}
			if(!termReq) {addConj(cur, res);}

			elem = new litteral;
			((litteral*)elem)->value = exp;
			elem->quant = 0;
			elem->parent = cur;
			if(cur != NULL) {
				if(cur->type() == 2) {((disjunction*)cur)->value = elem;}
				else {((conjunction*)cur)->value = elem;}
			}
			else {res = elem;}
			cur = elem;

			kwlc = keywords; int l = exp.size();
			if(kwlc) {
				while(kwlc->next && exp.compare(kwlc->next->value) >= 0) {kwlc = kwlc->next;}
				while(exp.substr(0, l).compare(kwlc->value.substr(0, l))) {l --;}
			}

			par = new ExpressionList;
			par->value = cur;
			if(kwlc && l == exp.size()) {
				par->next = kwlc->parents;
				kwlc->parents = par;
			}

			else {
				kwle = new KWList;
				kwle->value = exp;
				kwle->parents = par;
				par->next = NULL;
				if(!kwlc || exp.compare(kwlc->value) < 0)
				{kwle->next = keywords; keywords = kwle;}
				else {
					kwle->next = kwlc->next;
					kwlc->next = kwle;
				}
			}

			exp.clear();
			termReq = false;
		}

		else if(!blank(c) && c != ';') {return 1;}
	}

	if(c != ';' || termReq || parStack != NULL) {return 1;}
	if(res->type() == 3 && res->quant == 0 && ((conjunction*)res)->next == NULL) {
		cur = res;
		res = ((conjunction*)cur)->value;
		res->parent = NULL;
		delete cur;
	}

	closeBlock(cur, parStack);
	rule->exp = res;
	//cout << "Res : " << rule->exp << endl;
	//cout << "Name : " << rule->name << endl;
	if(res->type() <= 1) {res->parent = rule->handle;}
	else {
		while(res != NULL) {
			res->parent = rule->handle;
			if(res->type() == 2) {res = ((disjunction*)res)->next;}
			else {res = ((conjunction*)res)->next;}
		}
	}

	return 0;
}

void Parser::addConj(expElem* &cur, expElem* &res) {
	expElem* elem;
	if(cur->type() <= 1) {
		elem = new conjunction;
		elem->parent = cur->parent;
		if(cur->parent) {
			if(cur->parent->type() == 2)
			{((disjunction*)cur->parent)->value = elem;}
			else {((conjunction*)cur->parent)->value = elem;}
		}
		else {res = elem;}
		elem->quant = cur->quant;
		((conjunction*)elem)->value = cur;
		cur->parent = elem;
		cur = elem;
	}

	elem = new conjunction;
	elem->quant = 0;
	((conjunction*)elem)->value = NULL;
	((conjunction*)elem)->next = NULL;
	elem->parent = cur->parent;
	((conjunction*)cur)->next = (conjunction*)elem;
	cur = elem;
}

void Parser::closeBlock(expElem* cur, explist parStack) {
	if(cur->type() == 3 && cur->parent && cur->parent->type() == 2)
	{closeDisj(((conjunction*)cur)->parent);}
	else if(cur->type() <= 1 && cur->parent && cur->parent->type() == 3
		&& (!parStack || cur->parent != parStack->value))
	{cur->parent->quant = cur->quant;}
}

void Parser::closeDisj(expElem* cur) {
	if(((disjunction*)cur)->value->type() == 3
	&& ((conjunction*)((disjunction*)cur)->value)->next == NULL) {
		expElem* elem = ((disjunction*)cur)->value;
		expElem* tmp = ((conjunction*)elem)->value;
		cur->quant = elem->quant;
		((disjunction*)cur)->value = tmp;
		if(tmp->type() <= 1) {tmp->parent = cur;}
		else {
			while(tmp != NULL) {
				tmp->parent = cur;
				if(tmp->type() == 2) {tmp = ((disjunction*)tmp)->next;}
				else {tmp = ((conjunction*)tmp)->next;}
			}
		}
		delete elem;
	}
}

void Parser::blacklist(ifstream& file) {
	vector <string> kwQueue;
	KWList *cur, *tmp;
	string word;

	while(!file.eof()) {
		file >> word;
		cur = keywords; tmp = NULL;
		while(cur->next && word.compare(cur->next->value) >= 0) {
			tmp = cur;
			cur = cur->next;
		}

		if(word.compare(cur->value) == 0) {
			blkw.push_back(word);
			(tmp ? tmp->next : keywords) = cur->next;
		}
	}
}

bool Parser::banned(string word) {
	for(int i = 0; i < blkw.size(); i ++) {
		if(word == blkw[i]) {return true;}
	}
	return false;
}

int Parser::parse(ifstream& file) { // Corriger pour r�cup�rer les litt�raux.
	// D�gueu mais bon...
	cursors = NULL;
	
	char c = ' ';
	string word;
	KWList* cur;
	explist res;
	int L, l, i;
	seqList* sl;
	int ln = 1;

	while(blank(c) && !file.eof()) {
		if(c == '\n') {ln ++;}
		file.get(c);
	}

	while(!blank(c) && !file.eof())
	{word += c; file.get(c);}

	while(!word.empty()) {
		cout << endl << ln << " - New word :" << endl;
		cur = keywords;
		l = word.size(); i = 0;
		while(cur->next && word.compare(cur->next->value) >= 0) {cur = cur->next;}
		while(word.substr(0, l).compare(cur->value.substr(0, l))) {l --;}
		if(word[0] >= '0' && word[0] <= '9') {L = 1; res = digit->parents;}
		else {
			while(i < word.size() && alphanum(word[i])) {i ++;}
			if(i > l) {
				L = i; res = id->parents;
				if(banned(word)) {
					cout << "Mot " << word
					<< "blacklist�, trait� comme identifiant" << endl;
				}
				cout << "--- ID" << endl;
			}
			else if(l > 0) {L = l; res = cur->parents; cout << "--- " << cur->value << endl;}
			else if(word[0] == '\'') {
				do {
					i ++;
					if(i >= word.size()) {
						if(file.eof()) {
							cout << "Litt�ral cha�ne non ferm�." << endl;
							return 1;
						}
						file >> word; i = 0;
					}
					if(word[i] == '\\') {i += 2;}
				} while(word[i] != '\'');
				res = charlit->parents; L = i + 1;
			}
			else if(word[0] == '"') {
				do {
					i ++;
					if(i >= word.size()) {
						while(blank(c) && !file.eof()) {
							if(c == '\n') {ln ++;}
							file.get(c);
						}
						while(!blank(c) && !file.eof())
						{word += c; file.get(c);}
						if(file.eof()) {
							cout << "Litt�ral cha�ne non ferm�." << endl;
							return 1;
						}
						i = 0;
					}
					if(word[i] == '\\') {i += 2;}
				} while(word[i] != '"');
				res = strlit->parents; L = i + 1;
			}
			else {return 1;}
		}

		step(res);

		if(cursors == NULL) {
			cout << "Jeton " << word.substr(0, L)
			<< " inattendu ligne " << ln << "." << endl;
			return 1;
		}

		sl = cursors;
		while(sl != NULL) {
			showCur(sl->value->value);
			sl = sl->next;
		}
		word = word.substr(L);
		if(word.empty()) {
			while(blank(c) && !file.eof()) {
				if(c == '\n') {ln ++;}
				file.get(c);
			}

			while(!blank(c) && !file.eof())
			{word += c; file.get(c);}
		}
	}

	return 0;
}

void Parser::step(explist el) {
	seqList *res = NULL, *sl, *sl2;
	ruleCursor *cur2 = NULL;
	expElem* cur3;
	cursorList *cls = NULL, *elem, *cli;
	explist exps = NULL, elem2, expi;
	cursorList *elemQueue, *rear;
	bool ctn;

	while(el != NULL) {
		cur3 = el->value;
		elemQueue = new cursorList;
		elemQueue->value = new ruleCursor;
		elemQueue->value->cursor = cur3;
		elemQueue->value->parent = elemQueue->value->child = NULL;
		elemQueue->next = NULL;
		rear = elemQueue;

		while(elemQueue != NULL) {
			ctn =  true;
			do {
				elem = new cursorList;
				elem->value = dwCopy(elemQueue->value);
				elem->next = cls; cls = elem;
				elem2 = new ExpressionList;
				elem2->value = cur3;
				elem2->next = exps; exps = elem2;

				if(cur3->type() == 3) {
					conjunction* cur4;
					if(cur3->parent->type() == 2)
					{cur4 = (conjunction*)((disjunction*)(cur3->parent))->value;}
					else if(cur3->parent->type() == 3)
					{cur4 = (conjunction*)((conjunction*)(cur3->parent))->value;}
					else {cur4 = (conjunction*)((nonTerm*)(cur3->parent))->value->exp;}
					while(ctn && cur4 != cur3) {
						if(cur4->quant == 0 || cur4->quant == 3) {ctn = false;}
						else {cur4 = cur4->next;}
					}
				}

				if(ctn) {
					cur3 = cur3->parent;
					if(cur3->type() == 1 && cur3->parent == NULL) {
						Rule* rule = ((nonTerm*)cur3)->value;
						if(rule->parents == NULL) {ctn = false;}

						if(ctn) {
							explist cur4 = rule->parents;
							cur2 = elemQueue->value;
							while(cur2 && cur2->cursor != cur4->value)
							{cur2 = cur2->child;}
							if(cur2) {ctn = false;}
							else {
								cur3 = cur4->value;
								elemQueue->value = uwExtend(elemQueue->value, cur3);
							}

							cur4 = cur4->next;
							while(cur4 != NULL) {
								cur2 = elemQueue->value;
								while(cur2 && cur2->cursor != cur4->value)
								{cur2 = cur2->child;}
								if(!cur2) {
									elem = new cursorList;
									elem->value = dwCopy(elemQueue->value->child);
									elem->value = upperEnd(elem->value);
									elem->value = uwExtend(elem->value, cur4->value);
									rear->next = elem; rear = elem;
									elem->next = NULL;
								}
								cur4 = cur4->next;
							}
						}
					}
				}
			} while(ctn);

			elem = elemQueue->next;
			uwDelete(elemQueue->value);
			delete elemQueue;
			elemQueue = elem;
			if(elemQueue) {cur3 = elemQueue->value->cursor;}
		}
		el = el->next;
	}

	if(!cursors) {
		while(cls != NULL) {
			sl = new seqList;
			sl->value = new cursorSeq;
			sl->value->value = cls->value;
			sl->value->prev = NULL;
			sl->value->next = NULL;
			sl->next = cursors; cursors = sl;
			cls = cls->next;
		}
		return;
	}

	while(cursors != NULL) {
		cur2 = cursors->value->value;
		if(cur2 && cur2->cursor) {cur3 = cur2->cursor; ctn = true;}
		else {ctn = false;}
		while(ctn) {
			if(cur3->quant > 1) {
				cli = cls; expi = exps;
				while(cli != NULL) {
					if(cur3 == expi->value) {
						sl = new seqList;
						sl->value = new cursorSeq;
						sl->value->value = fuse(cur2, cli->value);
						sl->value->prev = cursors->value;
						sl->value->next = NULL;
						sl2 = new seqList; sl2->value = sl->value;
						sl2->next = cursors->value->next;
						cursors->value->next = sl2;
						sl->next = res; res = sl;
					}
					cli = cli->next; expi = expi->next;
				}
			}

			if(cur3->type() == 3) {
				conjunction* cur4 = (conjunction*)cur3;
				while(ctn && cur4->next != NULL) {
					cur4 = cur4->next;
					if(cur4->quant == 0 || cur4->quant == 3) {
						if(cur4->value->type() == 1) {
							char q = ((nonTerm*)cur4->value)->value->exp->quant;
							ctn = (q == 1 || q == 2);
						}
						else {ctn = false;}
					}

					cli = cls; expi = exps;
					while(cli != NULL) {
						if(cur4 == expi->value) {
							sl = new seqList;
							sl->value = new cursorSeq;
							sl->value->value = fuse(cur2, cli->value);
							sl->value->prev = cursors->value;
							sl->value->next = NULL;
							sl2 = new seqList; sl2->value = sl->value;
							sl2->next = cursors->value->next;
							cursors->value->next = sl2;
							sl->next = res; res = sl;
						}
						cli = cli->next; expi = expi->next;
					}
				}
			}

			if(ctn) {
				cur3 = cur3->parent;
				if(cur3->type() == 1 && cur3->parent == NULL) {
					cur2 = cur2->parent;
					if(cur2 && cur2->cursor) {cur3 = cur2->cursor;}
					else {ctn = false;}
				}
			}
		}

		if(cursors->value->next == NULL)
			{delSeq(cursors->value);}
		cursors = cursors->next;
	}

	cursors = res;
}

bool Parser::endParsing() {
	seqList* sli = cursors;
	ruleCursor* cur; expElem* e;
	bool ctn;
	while(sli) {
		cur = upperEnd(sli->value->value);
		e = cur->cursor;
		while(e->parent) {e = e->parent;}
		if(((nonTerm*)e)->value->parents == NULL) {
			cur = sli->value->value;
			e = cur->cursor; ctn = true;
			while(ctn) {
				if(e->type() == 3) {
					conjunction* cur4 = (conjunction*)e;
					while(ctn && cur4->next != NULL) {
						cur4 = cur4->next;
						if(cur4->quant == 0 || cur4->quant == 3) {
							if(cur4->value->type() == 1) {
								char q = ((nonTerm*)cur4->value)->value->exp->quant;
								ctn = (q == 1 || q == 2);
							}
							else {ctn = false;}
						}
					}
				}

				if(ctn) {
					e = e->parent;
					if(e->type() == 1 && e->parent == NULL) {
						cur = cur->parent;
						if(cur && cur->cursor) {e = cur->cursor;}
						else {return true;}
					}
				}
			}
		}
		sli = sli->next;
	}
	return false;
}

bool alphanum(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_';
}

bool blank(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

char esc(char c) {
	switch(c) {
		case 'n' : return '\n';
		case 't' : return '\t';
		default : return c;
	}

}
