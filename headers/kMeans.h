#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
#include <list>

#include "input.h"
#include "LSH.h"

using namespace std;

class cluster {
    private:
        
        // inputForm* centroid;

        vector<int>* indexesOfAssVecs;

        vector<int>* centroidVec; // centroid vector

    public:

        cluster();
        ~cluster();
        // void informCentroid(inputForm*);
        // inputForm* getCentr();

        void NewCentroidVec(vector<int>*);
        void CopyCenVec(vector<int>*);
        void DeleteAndNewCentroidVec(vector<int>* nW);
        void InputNewCentrCoord(const int, const int);
        void DELCentroidVec();
        vector<int>* returncentroidVec();

        void initindexesOfAssVecs(const int);
        vector<int>* returnindexesOfAssVecs();

        void addVecToclus(const int);
        void deleteindexesOfAssVecs();
};

class KMeans {
    private:
        
        vector<cluster*> *clusterAr;
        int numOfclusters;

    public:
        KMeans(const int);
        ~KMeans();
        int getClusNum();
        vector<inputForm*> *getKMeansCentroids(dataInput*);
        void Clusterify(dataInput*);
        
        int returnClusterIndex(inputForm*);
        void assignData(dataInput*);
};

// bool isIdInVector(const int, vector<inputForm*>*, const int);
float uniformNUMBER(const float);
int getVecMedian(vector<int>*);