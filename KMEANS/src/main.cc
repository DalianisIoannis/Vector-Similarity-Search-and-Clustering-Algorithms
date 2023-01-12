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

    std::string input_file_original_space;
    std::string input_file_newspace;
    std::string output_file;
    for (int i = 1 ; i < argc ; i+=2){
        if (strcmp(argv[i],"-d") == 0){
            input_file_original_space = argv[i+1];
        }
        else if (strcmp(argv[i],"-i") == 0){
            input_file_newspace = argv[i+1];
        }
        else if (strcmp(argv[i],"-n") == 0){
            std::string classes_from_NN_as_clusters_file = argv[i+1];
        }
        else if (strcmp(argv[i],"-c") == 0){
            std::string configuration_file = argv[i+1];
        }
        else if (strcmp(argv[i],"-o") == 0){
            output_file = argv[i+1];
        }
    }
    ofstream myfile;
    myfile.open (output_file);
    myfile << "Writing this to a file.\n";

    KMeans *kM;
    auto start = std::chrono::high_resolution_clock::now();

    dataInput *s = new dataInput(input_file_original_space); // t10k-images.idx3-ubyte
    s->readMnist<unsigned char>();  // s->readMnist();

    kM = new KMeans(10); // we want the 10
    kM->Clusterify(s, output_file);
    // kM->ClusterifyWITHLsh(s);
    delete kM;
    
    delete s;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n\n\n";

    cout << endl << endl;

    start = std::chrono::high_resolution_clock::now();
    
    dataInput *newspace = new dataInput(input_file_newspace);
    newspace->readMnist<uint16_t>();

    kM = new KMeans(10);
    kM->Clusterify(newspace, output_file);
    // // kM->ClusterifyWITHLsh(s);
    delete kM;

    delete newspace;

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n\n\n";

    myfile.close();

    return 0;
}