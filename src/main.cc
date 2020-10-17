#include <iostream>
#include <fstream>

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
    return 0;
}