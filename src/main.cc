#include <iostream>
#include <fstream>
#include "../headers/HashTable.h"
#include "../headers/input.h"
#include "../headers/LSH.h"

using namespace std;

int main(void) {

    cout << "Only just started!" << endl;

    dataInput *s = new dataInput("train-images.idx3-ubyte");


    // s->readMnist();

    // s->tryVector();


    tryHash();

    delete s;

    cout << "DOKIMI" << endl;

    HashTablePtr table = new HashTable(5) ;
    std::vector <int> pict = {1,2,8};
    cout << table->Table_Insert(*funct,pict)<<endl;
    
    delete table;

    return 0;
}