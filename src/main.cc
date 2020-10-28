#include <iostream>
#include <fstream>
#include "../headers/HashTable.h"
#include "../headers/input.h"
#include "../headers/LSH.h"
#include "../headers/HashFunctions.h"
#include "../headers/kMeans.h"

using namespace std;

int main(void) {

    cout << "Only just started!" << endl;

    dataInput *s = new dataInput("train-images.idx3-ubyte");


    s->readMnist();

    s->tryVector();

    tryHash();



    KMeans *means = new KMeans(5);

    means->Clusterify(s);


    delete means;
    delete s;
    
    cout << "DOKIMI" << endl;

    // std::vector<double> x(789);
    // std::default_random_engine gen{std::random_device{}()};
    // std::uniform_real_distribution<double> dist(0.0, 4000.0);
    // std::generate(std::begin(x), std::end(x), [&]{ return dist(gen); });
    // for(int i=0; i<789; i++){
    //     std::cout << x[i] << std::endl;
    // }
    
    return 0;
}