#include <iostream>
#include <fstream>
#include "../headers/HashTable.h"
#include "../headers/input.h"

using namespace std;

int main(void) {

    cout << "Only just started!" << endl;

    dataInput *s = new dataInput("train-images.idx3-ubyte");

    s->readMnist();

    // s->tryVector();

    delete s;

    cout << "DOKIMI" << endl;
    HashTablePtr table = new HashTable(5) ;
    std::vector <int> pict = {1,2,8};
    cout << table->Table_Insert(*funct,pict)<<endl;
    return 0;
}