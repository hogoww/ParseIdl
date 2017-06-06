#include "Cursor.h"
#include <iostream>

using namespace std;

void uwDelete(ruleCursor* cur) {
	ruleCursor* c = cur;
	while(c->parent) {
		c = c->parent;
		delete c->child;
	}
	delete c;
}

void dwDelete(ruleCursor* cur) {
	ruleCursor* c = cur;
	while(c->child) {
		c = c->child;
		delete c->parent;
	}
	delete c;
}

ruleCursor* uwCopy(ruleCursor* cur) {
	ruleCursor *elem = NULL, *tmp = NULL;
	while(cur != NULL) {
		elem = new ruleCursor;
		elem->cursor = cur->cursor;
		elem->parent = NULL; elem->child = tmp;
		if(tmp != NULL) {tmp->parent = elem;}
		tmp = elem; cur = cur->parent;
	}
	return elem;
}

ruleCursor* dwCopy(ruleCursor* cur) {
	ruleCursor *elem = NULL, *tmp = NULL;
	while(cur != NULL) {
		elem = new ruleCursor;
		elem->cursor = cur->cursor;
		elem->child = NULL; elem->parent = tmp;
		if(tmp != NULL) {tmp->child = elem;}
		tmp = elem; cur = cur->child;
	}
	return elem;
}

ruleCursor* uwExtend(ruleCursor* c, expElem* e) {
	ruleCursor* p = new ruleCursor;
	p->cursor = e;
	p->parent = NULL;
	p->child = c;
	c->parent = p;
	return p;
}

ruleCursor* upperEnd(ruleCursor* c) {
	while(c->parent != NULL) {c = c->parent;}
	return c;
}

ruleCursor* lowerEnd(ruleCursor* c) {
	while(c->child != NULL) {c = c->child;}
	return c;
}

ruleCursor* fuse(ruleCursor* uc, ruleCursor* lc) {
	ruleCursor *up = uwCopy(uc), *lp = uwCopy(lc);
	if(up) {
		up = lowerEnd(up);
		if(up->parent) {
			up = up->parent; delete up->child;
			up->child = lp; lp->parent = up;
		}
		else {delete up;}
	}

	return lowerEnd(lp);
}

void delSeq(cursorSeq* seq) {
	if(seq->value) {uwDelete(seq->value);}
	cursorSeq* p = seq->prev;
	if(p) {
		seqList *sli = p->next, *tmp;
		if(sli && sli->value == seq) {
			tmp = sli->next; delete sli; p->next = tmp;
			if(!p->next) {delSeq(p);}
		}
		else {
			while(sli && sli->next && sli->next->value != seq) {sli = sli->next;}
			if(sli && sli->next) {
				tmp = sli->next->next;
				delete sli->next;
				sli->next = tmp;
			}
		}
	}
	delete seq;
}
