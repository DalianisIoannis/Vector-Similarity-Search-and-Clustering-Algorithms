#include <iostream>
#include <string>
#include "../headers/RedBlack.h"

struct RedBlackNode {
  RBdataPtr data;         //includes h and f match
  node parent;
  node leftchild;
  node rightchild;
  char colour;                        // 0 = black 1 = red
};

struct RedBlackTree{
  node root;
  int NumElems;
};

tree Rbtcreate(){
  tree Redblackt = (tree)malloc(sizeof(struct RedBlackTree));
  Redblackt->root = NULL;
  Redblackt->NumElems = 0;
  //printf("Red Black tree is created\n");
  return Redblackt;
}

node insert(tree rbtree,RBdataPtr datainsert) {
  node tinsert;
 /* node checker;
  checker = RBsearch(rbtree,datainsert->hValue);
  if (checker != NULL) {
    printf("%d Duplicate\n",datainsert->hValue);
    return NULL;
  }*/
  tinsert = (node)malloc(sizeof(struct RedBlackNode));
  tinsert->data = datainsert;
  tinsert->parent = NULL;
  tinsert->leftchild = NULL;
  tinsert->rightchild = NULL;
  tinsert->colour = 1;
  if (!(rbtree->NumElems)){                             //then we need to make root
    tinsert->colour = 0;
    rbtree->root = tinsert;
    rbtree->NumElems++;
//    printf("Root inserted\n");
    return tinsert;
  }
  node leader=rbtree->root;
  while (leader!=NULL) {
    if (datainsert->hValue >= leader->data->hValue) {
      if (leader->rightchild == NULL){
        leader->rightchild = tinsert;
        tinsert->parent = leader;
	      rbtree->NumElems++;
  //      printf("I have just inserted an element\n");
        break;
      }
      else leader = leader->rightchild;
    }
    else if (datainsert->hValue  < leader->data->hValue){
      if (leader->leftchild == NULL){
        leader->leftchild = tinsert;
        tinsert->parent = leader;
	      rbtree->NumElems++;
  //      printf("I've just inserted an element\n");
        break;
      }
      else leader = leader->leftchild;
    }
  }
  balance(tinsert,rbtree);
  return tinsert;
}

void balance(node balanceAround,tree rbt){
  while (!(isblack(balanceAround->parent))){
    if (balanceAround->parent->parent->rightchild == balanceAround->parent){    //if parent is the rightchild then uncle is the leftchild
      node uncle = balanceAround->parent->parent->leftchild;              //check = uncle if it exists
      if (uncle != NULL) {
        if (uncle->colour){                                       //if uncle is red then we recolour grandparent-parent-uncle
          balanceAround->parent->colour=0;
          balanceAround->parent->parent->colour=1;
          uncle->colour=0;
          balanceAround=balanceAround->parent->parent;
          continue;
        }
      }
      if (balanceAround->parent->leftchild == balanceAround){        //child parent grandparent form a triangle and uncle black
        RightRotation(balanceAround->parent,rbt);
        balanceAround = balanceAround->rightchild;
      }
      LeftRotation(balanceAround->parent->parent,rbt);
      balanceAround->parent->colour = 0;
      balanceAround->parent->leftchild->colour = 1;
    }
    else if (balanceAround->parent->parent->leftchild == balanceAround->parent){
      node uncle = balanceAround->parent->parent->rightchild;
      if (uncle != NULL) {
        if  (uncle->colour){
          balanceAround->parent->colour=0;
          balanceAround->parent->parent->colour=1;
          uncle->colour=0;
          balanceAround=balanceAround->parent->parent;
          continue;
        }
      }
      if (balanceAround->parent->rightchild == balanceAround){
        LeftRotation(balanceAround->parent,rbt);
        balanceAround = balanceAround->leftchild;
      }
      RightRotation(balanceAround->parent->parent,rbt);
      balanceAround->parent->colour = 0;
      balanceAround->parent->rightchild->colour=1;
     }
    }
  rbt->root->colour = 0;
}

void RightRotation(node torotate,tree rbt){
  node keep;
  keep = torotate->leftchild;
  torotate->leftchild = keep->rightchild;
  if (torotate->leftchild !=NULL)
    torotate->leftchild->parent = torotate;
  keep->parent = torotate->parent;
  if (keep->parent == NULL)
    rbt->root = keep;
  else if (keep->parent->leftchild == torotate)
    keep->parent->leftchild = keep;
  else keep->parent->rightchild = keep;
  keep->rightchild = torotate;
  torotate->parent = keep;
}

void LeftRotation(node torotate,tree rbt){
  node keep;
  keep = torotate->rightchild;
  torotate->rightchild = keep->leftchild;
  if (torotate->rightchild !=NULL)
    torotate->rightchild->parent=torotate;
  keep->parent = torotate->parent;
  if (keep->parent == NULL)
    rbt->root = keep;
  else if (keep->parent->leftchild == torotate)
    keep->parent->leftchild = keep;
  else keep->parent->rightchild = keep;
  keep->leftchild = torotate;
  torotate->parent = keep;
}


node RBsearch(tree rbt,int keycode){
  node tofind;
  tofind = rbt ->root;
  while (tofind!=NULL){
    if (keycode  > tofind->data->hValue){
      if (tofind->rightchild != NULL)
        tofind = tofind->rightchild;
    else {//printf("The Keycode you search does not exist\n");
        return NULL;
      }
    }
    else if(keycode < tofind->data->hValue){
      if (tofind->leftchild !=NULL)
        tofind = tofind->leftchild;
      else {//printf("The keycode you search does not exist\n");
            return NULL;
      }
    }
    else{
    //printf("Found\n");
    return tofind;
    }
  }
  return NULL;
}

int RBdelete(tree rbt,int keycode){
  int ind = 0;
  node todel;
  node successor;
  node child =NULL;
  todel = RBsearch(rbt,keycode);
  if (todel == NULL){
      printf("Nothing to delete\n");
      return 0;
  }
  else {
    if ((todel->leftchild !=NULL) && (todel->rightchild !=NULL)){//If node has 2 childs we need to find successor
      successor = todel->rightchild;
      while (successor->leftchild != NULL)
        successor = successor->leftchild;
      free(todel->data);                     //free data we delete before copy
      todel->data = successor->data;
      todel = successor;
      ind = 1;
      }
    if (todel->leftchild != NULL)           //find child - then skip todel --- connect todel->parent and child
      child = todel->leftchild;
    else if (todel->rightchild != NULL)
      child = todel->rightchild;
    else {
      child = NULL;
    }
    if (child !=NULL)             //connecting todel -> parent and child
      child->parent = todel->parent;
    if (todel->parent == NULL)
      rbt->root = child;
    else if (todel->parent->leftchild == todel)
      todel->parent->leftchild = child;
    else todel->parent->rightchild = child;
    if (isblack(todel)){
        RBdelBalance(rbt,child,todel->parent);
    }
    if (!(ind))                   //if we found successor we have already free'd the data we should
      delete(todel->data);
    free(todel);
    rbt->NumElems--;
    return 1;
  }
}




void RBdelBalance(tree rbt,node raround,node mparent){        //sibling->parent == mparent apparently
  while ((raround != rbt->root) && (isblack(raround))) {        //condition
    node sibling;
    if (raround == mparent->leftchild){               //check which child raround is to pick up sibling
      sibling = mparent->rightchild;                  //if raround is the leftchild
      if (!(isblack(sibling))){                       //if sibling is red
        sibling->colour=0;
        mparent->colour = 1;
        LeftRotation(mparent,rbt);
        sibling = mparent->rightchild;
      }
      if (isblack(sibling->leftchild) && isblack(sibling->rightchild)){ //if both siblings children are black
        sibling->colour = 1;
        raround = mparent;
        mparent = raround->parent;
      }
      else{                                                               //else one of them is definetely red
        if (isblack(sibling->rightchild)){            //if leftchild is red
          sibling->leftchild->colour = 0;
          sibling->colour = 1;
          RightRotation(sibling,rbt);                   //rightrotate
          sibling = mparent->rightchild;                //new sibling after rotate
        }
        sibling->colour = sibling->parent->colour;        //recolour sibling and parent
        mparent->colour = 0;
        if (sibling->rightchild!=NULL)                    //in case rightchild isnt NULL,if it is it is black already
          sibling->rightchild->colour = 0;
        LeftRotation(mparent,rbt);            //rotate left
        return;                               //tree balanced
      }
  }                                                       //mirror case
    else if (raround == mparent->rightchild){
      sibling = mparent->leftchild;
      if (!(isblack(sibling))) {
        sibling->colour = 0;
        mparent->colour=1;
        RightRotation(mparent,rbt);
        sibling = mparent->leftchild;
      }
      if ((isblack(sibling->leftchild)) && (isblack(sibling->rightchild))){  //if both children are black//they might be null too
        sibling->colour = 1;
        raround = mparent;
        mparent = raround->parent;
      }
      else{
        if (isblack(sibling->leftchild)){           //that means the rightchild is red since we know both children are not black
          sibling->rightchild->colour = 0;
          sibling->colour = 1;
          LeftRotation(sibling,rbt);
          sibling = mparent->leftchild;
        }
        sibling->colour = sibling->parent->colour;
        mparent->colour = 0;
        if (sibling->rightchild != NULL)
          sibling->rightchild->colour = 0;
        RightRotation(mparent,rbt);
        return;
      }
    }
  }
  rbt->root->colour = 0;
  rbt->root->parent = NULL;
}

node getroot(tree rbt){
  return rbt->root;
}
void printinorder(node treeroot,int* counter) {
  if (treeroot!=NULL) {
    printinorder(treeroot->leftchild,counter);
    //printid(treeroot->data);
    if (treeroot->colour)
    printf(" RED\n");
    else printf(" BLACK\n");
    (*counter)++;
    printf("%d matches %d\n",returnData(treeroot)->hValue,returnData(treeroot)->fValue);
    printinorder(treeroot->rightchild,counter);
 }
}

void RBTdestroy(node troot,tree rbt){
  if (troot == NULL)
		return;
	RBTdestroy(troot->leftchild,rbt);
	RBTdestroy(troot->rightchild,rbt);
  //FreeRecord(troot->data);
	free(troot);
	troot=NULL;
}

RBdataPtr returnData(node rbtnode){
  if (rbtnode == NULL)
    printf("ERRORRRR\n");
  return rbtnode->data;
}


char isblack(node check){
  if (check == NULL)
    return 1;
  else if (check->colour==0)
    return 1;
  else return 0;
  }

node findsuccessor(node todel){
  node successor;
  if ((todel->leftchild != NULL) && (todel->rightchild != NULL)){//If node has 2 childs we need to find successor
      successor = todel->rightchild;
    while (successor->leftchild != NULL)
      successor = successor->leftchild;
    return successor;
  }
  else return NULL;
}

int get_tree_elems(tree MyTree){
  return MyTree->NumElems;
}


RBdataPtr SetupRBdata(int hval,int fval){
  RBdataPtr toReturn = new RBdata;
  toReturn->fValue = fval;
  toReturn->hValue = hval;
  return toReturn;
}

int Returnhval(RBdataPtr Retnode){
  return Retnode->hValue;
}

int Returnfval(RBdataPtr Retnode){
  return Retnode->fValue;
}
