#include "../headers/LSH.h"

int manhattanDistance(vector<int>* x, vector<int>* y) {
    
    int sum = 0;

    cout << "Size of vector x is " << x->size() << endl;
    cout << "Size of vector y is " << y->size() << endl;

    if(x->size() != y->size()) {
        cerr << "Vectors should be of the same size!\n";
        return -1;
    }

    for (unsigned int i = 0; i < x->size(); i++) {
        
        cout << (*x)[i] << " and " << (*y)[i] << " and abs " << abs( (*x)[i] - (*y)[i] ) << endl;

        sum += abs( (*x)[i] - (*y)[i] );

    }
    
    return sum;
}

int ai(const int pi, const int si, const int w) {
    
    return floor( float(pi - si) / float(w) );

}

int h(vector<int>* p, vector<int>* s, const int m, const int w, const int M) {
    
    // return h()
    int ret = 0;
    int ekth = 0;

    for(unsigned int i=0; i<p->size(); i++) {

        ret += int(pow(m, ekth++)) * ai( (*p)[i], (*s)[i], w );

    }

    cout << "ret is " << ret << " and M is " << M << endl;

    return ret % M;
}

int g(vector<int>* p, vector<int>* s, const int k, const int w, const int m, const int M) {
    
    // it returns g(p)

    return h( p, s, m, w, M );

}

void tryHash() {

    vector<int> p(35);
    vector<int> s(35);

    int ccc = 0;

    cout << p.size() << endl;
    cout << s.size() << endl;

    for(unsigned int i=0; i<p.size(); i++) {
        p[i] = ccc++;
    }
    for(unsigned int i=0; i<s.size(); i++) {
        s[i] = ccc++;
    }

    for(unsigned int i=0; i<p.size(); i++) {
        cout << p[i] <<endl;
    }
    for(unsigned int i=0; i<s.size(); i++) {
        cout << s[i] <<endl;
    }

    // return g
    int m = 1;
    int M = 3;
    int k = 10;
    int w = 10;

    int ret = g(&p, &s, k, w, m, M);

    cout << "G is " << ret << endl;

}