#include "max_heap.h"
    typedef struct linfo *listinfo;
    typedef struct lnode *listnode;

    struct linfo {
        int Num_Elems;
        listnode Head;
        listnode tail;
    };

    struct lnode {
        int data;
        listnode next;
    };
    listinfo CreateList();
    listnode InsertList(listinfo,PatientRecord);
    listnode SearchList(listinfo,char*);
    void DeleteList(listinfo);
    void DeleteListNodes(listinfo,listnode);
    void PrintList(listinfo);
    int ReturnListSize(listinfo);
