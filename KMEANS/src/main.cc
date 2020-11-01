#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
#include <string.h>
#include <ctime>
#include <chrono>

// #include "../headers/LSH.h"
#include "../headers/kMeans.h"

using namespace std;

int main(int argc,char* argv[]) {

    std::string inputfile;

    for (int i = 1 ; i < argc ; i+=2){
        if (strcmp(argv[i],"-i") == 0){
            inputfile = argv[i+1];
        }
        else if (strcmp(argv[i],"-c") == 0){
            std::string configfile = argv[i+1];
        }
        else if (strcmp(argv[i],"-o") == 0){
            std::string outputfile = argv[i+1];
        }
        else if (strcmp(argv[i],"-complete") == 0){
            int complete = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i],"-m") == 0){
            std::string method = argv[i+1];
        }
        // else if (strcmp(argv[i],"-L") == 0){
        //     L = atoi(argv[i+1]);
        // }
    }

    auto start = std::chrono::high_resolution_clock::now();

    dataInput *s = new dataInput("t10k-images.idx3-ubyte");
    // dataInput *s = new dataInput(inputfile);
    
    s->readMnist();
    



    KMeans *kM = new KMeans(4);
    kM->Clusterify(s);
    // kM->ClusterifyWITHLsh(s);
    delete kM;
    
    
    
    
    delete s;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}