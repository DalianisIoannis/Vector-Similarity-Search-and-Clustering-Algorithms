#include <iostream>
#include "../headers/LSH.h"

listinfo CreateList(){
    listinfo NewList = (listinfo)malloc(sizeof(struct linfo));
    NewList->Head = NULL;
    NewList->tail = NULL;
    NewList->Num_Elems = 0;
    return NewList;
}

listnode InsertKNearestList(listinfo MyList,inputForm* ToInsert,int manhattan_dist,int MaxElems){
    // initialise node
    listnode NodeInsert = (listnode)malloc(sizeof(struct lnode));
    NodeInsert->data = ToInsert;
    NodeInsert->next = NULL;
    NodeInsert->prev = NULL;
    NodeInsert->manh_dist = manhattan_dist;
    //////////////////
    listnode checknode = MyList->Head;
    if (MyList->Num_Elems == 0) {
        MyList->Head = NodeInsert;
        MyList->tail = NodeInsert;
    }
    else {
        while (checknode != NULL){                              //insert elems sorted by manh
            if (manhattan_dist < checknode->manh_dist){
                NodeInsert->prev =  checknode->prev;
                NodeInsert->next = checknode;
                checknode->prev = NodeInsert;
                if (checknode == MyList->Head){
                    MyList->Head = NodeInsert;
                }
                else{
                    NodeInsert->prev->next = NodeInsert;
                }
                break;
            }
            else {
                checknode = checknode->next;
            }
        }
        if (MyList->Num_Elems < MaxElems && checknode == NULL){ //insert first k elems even if they are tail
            MyList->tail->next = NodeInsert;
            NodeInsert->prev = MyList->tail;
            MyList->tail = NodeInsert;
        }
        if (MyList->Num_Elems == MaxElems){     //delete last element in case we inserted a new one and list is full
            listnode todel = MyList->tail;
            MyList->tail = MyList->tail->prev;
            MyList->tail->next = NULL;
            delete todel;
            MyList->Num_Elems--;
        }
    }
    MyList->Num_Elems++;
    return NodeInsert;
}

listnode SearchKNearestList(listinfo Mylist,int id,int manhattanval){
    listnode searchnode;
    searchnode = Mylist->Head;
    while  (searchnode != NULL) {
        if (id == searchnode->data->Id){
            if (searchnode->manh_dist <= manhattanval){     //if we find elem we compare distances
                return searchnode;
            }
            else {
                searchnode->prev->next = searchnode->next;      //if our new dist is smaller we delete and then we insert at LSH
                searchnode->next->prev = searchnode->prev;
                free(searchnode);
                Mylist->Num_Elems--;
                return NULL;
            }
        }
        searchnode = searchnode->next;
    }
    return NULL;
}

listnode InsertList(listinfo Mylist,inputForm* toInsert,int manhDist){
    listnode NodeInsert =(listnode)malloc(sizeof(struct lnode));
    NodeInsert->data = toInsert;
    NodeInsert->prev = NULL;
    NodeInsert->next = NULL;
    NodeInsert->manh_dist= manhDist;
    if (Mylist->Num_Elems == 0) {
        Mylist->Head = NodeInsert;
        Mylist->tail = NodeInsert;
    }
    else {
        Mylist->tail->next = NodeInsert;
        NodeInsert->prev = Mylist->tail;
        Mylist->tail = NodeInsert;
    }
    Mylist->Num_Elems++;
    return NodeInsert;
}

listnode SearchListID(listinfo Mylist,int id){
    listnode searchnode;
    searchnode = Mylist->Head;
    while (searchnode != NULL){
        if (id == searchnode->data->Id){
            return searchnode;
        }
        searchnode = searchnode->next;
    }
    return NULL;
}

void PrintList(listinfo Mylist){
    listnode printnode;
    printnode = Mylist->Head;
    while (printnode != NULL) {
        cout <<"ID "<< printnode->data->Id << " with distance " << printnode->manh_dist<<endl;
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
    //free(MyListNode->data);
    free(MyListNode);
}
