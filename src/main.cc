#include <iostream>
#include <fstream>

#include "../headers/input.h"

using namespace std;

int main(void) {

    cout << "Only just started!" << endl;

    imageInput *s = new imageInput("train-images.idx3-ubyte");

    s->readMnist();

    delete s;

    cout << "DOKIMI" << endl;
    return 0;
}