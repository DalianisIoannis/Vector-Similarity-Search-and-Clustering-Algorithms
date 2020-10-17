#include <iostream>
#include <string>
#include <errno.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <math.h>

using namespace std;

int manhattanDistance(vector<int>* x, vector<int>* y);

int ai(const int pi, const int si, const int w);

int h(vector<int>* p, vector<int>* s, const int m, const int w, const int M);

int g(vector<int>* p, vector<int>* s, const int k, const int w, const int m, const int M);

void tryHash();