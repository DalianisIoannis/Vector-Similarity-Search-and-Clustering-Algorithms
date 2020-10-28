#include <iostream>
#include "list.h"

listinfo CreateList(){
    listinfo NewList = (listinfo)malloc(sizeof(struct linfo));
    NewList->Head = NULL;
    NewList->tail = NULL;
    NewList->Num_Elems = 0;
    return NewList;
}

listnode InsertList(listinfo MyList,int ToInsert){
    listnode NodeInsert = (listnode)malloc(sizeof(struct lnode));
    NodeInsert->data = ToInsert;
    NodeInsert->next = NULL;
    NodeInsert->prev = NULL;
    if (MyList->Num_Elems == 0) {
        MyList->Head = NodeInsert;
        MyList->tail = NodeInsert;
    }
    else {
        MyList->tail->next = NodeInsert;
        MyList->tail = NodeInsert;
    }
    MyList->Num_Elems++;
    return NodeInsert;
}

listnode SearchList(listinfo Mylist,char* searchRecord){
    listnode searchnode;
    searchnode = Mylist->Head;
    while  (searchnode != NULL) {
        if (strcmp(getRecordID(searchnode->Data),searchRecord) == 0){
            return searchnode;
        }
        searchnode = searchnode->next;
    }
 //   printf("There is no such record '%s' in this list",searchRecord);
    return NULL;
}

void PrintList(listinfo Mylist){
    listnode printnode;
    printnode = Mylist->Head;
    while (printnode != NULL) {
        printf("%s\n",getRecordID(printnode->Data));
        printnode = printnode->next;
    }
}

int ReturnListSize(listinfo MyList){
    return MyList->Num_Elems;
}

void DeleteList(listinfo Mylist){
    DeleteListNodes(Mylist,Mylist->Head);
    free(Mylist);
}

void DeleteListNodes(listinfo MyList,listnode MyListNode){
    if (MyListNode->next != NULL) {
        DeleteListNodes(MyList,MyListNode->next);
    }
    FreeRecord(MyListNode->Data);
    free(MyListNode);
}
