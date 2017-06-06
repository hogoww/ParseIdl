#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"

using namespace std;

int main() {
	// Rajouter commentaires dans Idl.g
	ifstream file;
	string fn;
	cout << "Veuillez indiquer un fichier de grammaire : ";
	cin >> fn;
	file.open(fn.c_str());

	Parser p;
	p.init(file);
	file.close();
	cout << endl << endl << endl << endl;
	KWList* kw = p.getKeyWords();
	explist cur; expElem* exp;

	while(kw != NULL) {
		cur = kw->parents;
		cout << kw->value << " :";
		while(cur != NULL) {
			exp = cur->value;
			while(exp->parent != NULL) {exp = exp->parent;}
			cout << " " << ((nonTerm*)exp)->value->name;
			cur = cur->next;
		}
		cout << endl;
		kw = kw->next;
	}

	cout << endl << endl << endl << endl;

	kw = p.getRules();
	while(kw != NULL) {
		showExp(((nonTerm*)kw->parents->value)->value);
		cout << endl;
		kw = kw->next;
	}

	ifstream idl;
	while(1) {
		cout << endl << "Veuillez indiquer un fichier à traiter "
			<< "(:quit pour terminer) : ";
		cin >> fn;
		if(fn == ":quit") {return 0;}
		idl.open(fn.c_str());
		if(idl.is_open()) {
			cout << endl;
			if(p.parse(idl))
			{cout << "Fichier syntaxiquement incorrect.";}
			else {
				if(p.endParsing())
				{cout << "Fichier syntaxiquement correct.";}
				else {cout << endl << "Fichier incomplet.";}
				idl.close();
			}
			cout << endl;
		}
		else {cout << "Impossible d'ouvrir le fichier." << endl;}
	}

/*	seqList* i = p.getCursors();
	cursorSeq* i2;
	while(i) {
		cout << "----------------------" << endl;
		i2 = i->value;
		while(i2) {
			showCur(i2->value);
			i2 = i2->prev;
		}
		i = i->next;
	}
*/
}
