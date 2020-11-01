#include <iostream>
#include <string>
#include <errno.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <ctime>
#include "cube.h"

using namespace std;

int manhattanDistance(vector<int>* x, vector<int>* y);

int ai(const int pi, const int si, const int w);

int h(vector<int>* p, vector<int>* s, const int m, const int w, const int M);
int h2(vector<int>* p, vector<int>* s, const int m, const int w, const int M);

int g(vector<int>* p, const int k, const int w, const int m, const int M);

int concatInts(unsigned int a, unsigned int b);

vector<int>* getVectorS(const unsigned int size, const int w);
listinfo kNearestNeighbors(HashTablePtr*,int,int,vector<int>*);
listinfo RangeSearch(HashTablePtr*,int,int,vector<int>*);
void tryHash();