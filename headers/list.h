
#include "../headers/input.h"
typedef struct linfo *listinfo;
typedef struct lnode *listnode;

struct linfo {
    int Num_Elems;
    listnode Head;
    listnode tail;
};

struct lnode {
    inputForm* data;
    int manh_dist;
    listnode next;
    listnode prev;
};

listinfo CreateList();
listnode InsertKNearestList(listinfo,inputForm*,int,int);
listnode InsertList(listinfo,inputForm*,int);
listnode SearchKNearestList(listinfo,int,int);
listnode SearchListID(listinfo,int);
void DeleteList(listinfo);
void DeleteListNodes(listinfo,listnode);
void PrintList(listinfo);
int ReturnListSize(listinfo);
