#include <iostream>
#include <fstream>
#include "../headers/LSH.h"
#include <random>
#include <math.h>
#include <string.h>
#include <ctime>
#include <chrono>

using namespace std;

int main(int argc,char* argv[]) {
  int k = 14;
  int M = 10;
  int probes = 2;
  int N = 1;
  int R = 10000;
  int i,j;
  std::string queryfile;
  std::string inputfile;
  std::string outputfile;

for (i = 1 ; i < argc ; i+=2){
  if (strcmp(argv[i],"-d") == 0){
    inputfile = argv[i+1];
  }
  else if (strcmp(argv[i],"-q") == 0){
    queryfile = argv[i+1];
  }
  else if (strcmp(argv[i],"-k") == 0){
    k = atoi(argv[i+1]);
  }
  else if (strcmp(argv[i],"-M") == 0){
    M = atoi(argv[i+1]);
  }
  else if (strcmp(argv[i],"-o") == 0){
    outputfile = argv[i+1];
  }
  else if (strcmp(argv[i],"-N") == 0){
    N = atoi(argv[i+1]);
  }
  else if (strcmp(argv[i],"-R") == 0){
    R = atoi(argv[i+1]);
  }
  else if (strcmp(argv[i],"-probes") == 0){
    probes = atoi(argv[i+1]);
  }
}

  dataInput *queryset = new dataInput(queryfile);
  queryset->readMnist();
  dataInput *inputset = new  dataInput(inputfile);
  inputset->readMnist();
  CubeTablePtr Table;
  int m = 1;
  int w = 10;
  Table = new CubeTable(inputset->getImageSize(),k,w,m) ;

    for (j = 0 ; j < inputset->getiMageVectorSize() ; j++){
        Table->CubeTable_Insert(inputset->getinputFormByNum(j));
    }
    cout <<"Pushed "<<inputset->getiMageVectorSize()<<" elements on Cube Table "<<i<<endl;

    std::ofstream file;
    file.open(outputfile, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(strerror(errno));
    listinfo outputList = CreateList();
    listinfo outputListBrute = CreateList();
    listinfo Rnear = CreateList();

    for (int i = 0 ; i < queryset->getiMageVectorSize() ; i++){   

      auto start = std::chrono::high_resolution_clock::now();
      outputList = knNearestNeighbors(&Table,N,probes,M,queryset->getinputFormByNum(i)->image);
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> tHypercube = finish - start;
      start = std::chrono::high_resolution_clock::now();
      outputListBrute = BruteForceNearest(queryset->getinputFormByNum(i)->image,inputset,N);
      finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double>tTrue = finish - start;
      
      file <<"Query: "<<queryset->getinputFormByNum(i)->Id<<endl;
      PrintNearestList(outputList,outputListBrute,file,"Hypercube");
      file <<"tHypercube: "<< tHypercube.count()<<endl;
      file <<"tTrue: "<<tTrue.count()<<endl;
      file <<"R-near neighbors"<<endl;
      Rnear = cubeRangeSearch(&Table,probes,R,queryset->getinputFormByNum(i)->image,R);
      PrintList(Rnear,file);
      file <<endl;

      // DeleteList(outputList);
      // DeleteList(outputListBrute);
      // DeleteList(Rnear);
    }

    delete inputset;
    delete queryset;

    return 0;
}