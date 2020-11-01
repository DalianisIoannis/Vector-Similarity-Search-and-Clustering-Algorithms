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
  int L = 5;
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
  else if (strcmp(argv[i],"-L") == 0){
    L = atoi(argv[i+1]);
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
}
  dataInput *queryset = new dataInput(queryfile);
  queryset->readMnist();

  dataInput *inputset = new  dataInput(inputfile);
  inputset->readMnist();
  int m = 200;
  int w = 10;
  int M = inputset->getiMageVectorSize() / 8;

  HashTablePtr Tables[L];

  for (i = 0 ; i < L ; i++){
    Tables[i] = new HashTable(inputset->getImageSize(),k,w,m,M) ;
    for (j = 0 ; j < inputset->getiMageVectorSize() ; j++){
        Tables[i]->Table_Insert(inputset->getinputFormByNum(j));
    }
    cout <<"Pushed "<<inputset->getiMageVectorSize()<<" elements on Hash Table "<<i<<endl;
  }
    std::ofstream file;
    file.open(outputfile, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(strerror(errno));
    listinfo outputList = CreateList();
    listinfo outputListBrute = CreateList();
    listinfo Rnear = CreateList();
    for (int i = 0 ; i < queryset->getiMageVectorSize() ; i++){   

    auto start = std::chrono::high_resolution_clock::now();
    
    // outputList = kNearestNeighbors(Tables,L,N,&queryset->getinputFormByNum(i)->image);
    outputList = kNearestNeighbors(Tables,L,N,queryset->getinputFormByNum(i)->image);
    
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tLSH = finish - start;

    start = std::chrono::high_resolution_clock::now();
    
    // outputListBrute = BruteForceNearest(&queryset->getinputFormByNum(i)->image,inputset,N);
    outputListBrute = BruteForceNearest(queryset->getinputFormByNum(i)->image,inputset,N);
    
    finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>tTrue = finish - start;

    file <<"Query: "<<queryset->getinputFormByNum(i)->Id<<endl;
    PrintNearestList(outputList,outputListBrute,file,"LSH");
    file <<"tLSH: "<<tLSH.count()<<endl;
    file <<"tTrue: "<<tTrue.count()<<endl;
    file <<"R-near neighbors"<<endl;

    // Rnear = RangeSearch(Tables,L,R,&queryset->getinputFormByNum(i)->image);
    Rnear = RangeSearch(Tables,L,R,queryset->getinputFormByNum(i)->image);
    
    PrintList(Rnear,file);
    file <<endl;
    }

    return 0;
}
