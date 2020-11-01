#include <iostream>
#include <fstream>
#include "../headers/LSH.h"
#include <random>
#include <math.h>
using namespace std;

int main(void) {

    cout << "Only just started!" << endl;
    listinfo mylist,mynewlist;

  dataInput *q = new dataInput("t10k-images-idx3-ubyte");

  q->readMnist();

  dataInput *s = new  dataInput("train-images-idx3-ubyte");

  s->readMnist();



    //delete s;
       HashTablePtr table[2];
        table[0] = new HashTable(784,7,3000,1,600) ;
        // table[1] = new HashTable(784,6,1000,1,4) ;
      //  CubeTablePtr newtabl = new CubeTable(784,6,1000,1);

   for (int i = 0 ; i < s->getiMageVectorSize() ; i++){
        cout <<"................"<<endl;
        table[0]->Table_Insert(s->getinputFormByNum(i));
        // table[1]->Table_Insert(s->getinputFormByNum(i));
      //  newtabl->CubeTable_Insert(s->getinputFormByNum(i));
        cout <<"................"<<endl;
   }
    vector<int> p(784);

    srand((unsigned) time(0));

    for(unsigned int i=0; i<p.size(); i++)
         p[i] = rand() % 255 + 1;
    for (int i = 0 ; i < q->getiMageVectorSize() ; i++){
    mylist = kNearestNeighbors(table,1,15,&q->getinputFormByNum(i)->image);
    // mynewlist = knNearestNeighbors(&newtabl,5,2,10000,&s->getinputFormByNum(9)->image);
    PrintList(mylist);
    }
    //mylist = RangeSearch(table,2,27500,&s->getinputFormByNum(9)->image);
//     tree RedBlacktreenew = Rbtcreate();
//     RBdataPtr datanew = SetupRBdata(0,1);
//     RBdataPtr datanew2 = SetupRBdata(1,0);
//     RBdataPtr datanew3 = SetupRBdata(2,1);

//     insert(RedBlacktreenew,datanew);
//     insert(RedBlacktreenew,datanew2);
//     insert(RedBlacktreenew,datanew3);    
//     int counter = 0;
//     RBdelete(RedBlacktreenew,0);
//     printinorder(getroot(RedBlacktreenew),&counter);
//     random_device rd;
// 	mt19937 gen (rd ());
// 	uniform_int_distribution <> dis (0, 1);
//     int x = dis(gen);
//     cout <<x<<endl;
//     cout <<"Hamming distance is " << hammingDistance(0,3) <<endl;
//     string minestr = "001";
//     vector<int> ret = findNearVerticlesOne(&minestr);
//     vector<int> toreti = findNearVerticles((int)pow(2,3),&minestr,4);
  
//   for (int i = 0 ; i < toreti.size() ; i++){
//         cout <<toreti[i];
//     }
    return 0;
}
// k : poses hash functions 
// size: idios arithmos me ta stoixeia tou dianismatos ths eikonas
// w : modarei ta ai
// m : varoi
// M :panw akro tou m tou vragmenou
// g_funct::g_funct(int size, const int k, const int w, const int m, const int M){
