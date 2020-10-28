#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>
#include <vector>
#include <random>
#include <algorithm>

#include "input.h"

using namespace std;

class cluster {
    private:
        
        inputForm* centroids;

    public:
        cluster();
        ~cluster();
};

class KMeans {
    private:
        
        vector<cluster*> *clusterAr;

        int numOfclusters;

    public:
        KMeans(const int);
        ~KMeans();
        void Clusterify(dataInput*);
        void addCentroid(inputForm*);
        int getClusNum();
};