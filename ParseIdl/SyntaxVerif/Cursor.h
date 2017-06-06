#include "Rule.h"

struct ruleCursor {
	expElem* cursor;
	struct ruleCursor* parent;
	struct ruleCursor* child;
};

struct cursorList {
	struct ruleCursor* value;
	struct cursorList* next;
};

struct cursorSeq {
	struct ruleCursor* value;
	struct cursorSeq* prev;
	struct seqList* next;
};

struct seqList {
	struct cursorSeq* value;
	struct seqList* next;
};

void uwDelete(ruleCursor* cur);
void dwDelete(ruleCursor* cur);
ruleCursor* uwCopy(ruleCursor* cur);
ruleCursor* dwCopy(ruleCursor* cur);
ruleCursor* uwExtend(ruleCursor* c, expElem* e);
ruleCursor* upperEnd(ruleCursor* c);
ruleCursor* lowerEnd(ruleCursor* c);
ruleCursor* fuse(ruleCursor* uc, ruleCursor* lc);
void delSeq(cursorSeq* seq);
