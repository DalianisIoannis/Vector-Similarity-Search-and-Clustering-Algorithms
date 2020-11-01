typedef struct RedBlackNode *node;
typedef struct RedBlackTree *tree;
typedef struct RBdata* RBdataPtr;

struct RBdata{              //struct that matches hValue with fValue for cube
    int hValue;
    int fValue;
};


tree Rbtcreate();
node insert(tree,RBdataPtr);
void balance(node,tree);
void RightRotation(node,tree);
void LeftRotation(node,tree);
node RBsearch(tree,int);
int RBdelete(tree,int);
void RBdelBalance(tree,node,node);
char isblack(node);
void printinorder(node,int*);
node getroot(tree);
void RBTdestroy(node,tree);
RBdataPtr returnData(node);
node findsuccessor(node);
int get_tree_elems(tree);
RBdataPtr SetupRBdata(int,int);
int Returnhval(RBdataPtr);
int Returnfval(RBdataPtr);



