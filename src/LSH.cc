#include "../headers/LSH.h"

int manhattanDistance(vector<int>* x, vector<int>* y) {
    
    int sum = 0;

    // cout << "Size of vector x is " << x->size() << endl;
    // cout << "Size of vector y is " << y->size() << endl;

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

int concatInts(const int a, const int b) {

    string s1 = to_string(a); 
    string s2 = to_string(b);

    // int c = (a << sizeof(b)) | b;

    // cout << "Gave " << a << " and " << b << " and result is " << c << endl;
    cout << s1<<" "<<s2<<endl;
    return stoi( s1 + s2 );

}

vector<int>* getVectorS(const unsigned int size, const int w) {
    
    vector<int>* s = new vector<int> (size);

    for(unsigned int i=0; i<(*s).size(); i++) {
        (*s)[i] = rand() % w; // +1 ?
    }
    return s;
}

// int ai(const int pi, const int si, const int w) {
    
//     return floor( float(pi - si) / float(w) );

// }

int h(vector<int>* p, vector<int>* s, const int m, const int w, const int M) {
    
    // return h()
    int ret = 0;
    int ekth = 0;

    for(unsigned int i=0; i<p->size(); i++) {

        ret += int(pow(m, ekth++)) * ai( (*p)[i], (*s)[i], w );

    }

    return ret % M;
}


int h2(vector<int>* p, vector<int>* s, const int m, const int w, const int M) {
    
    int ret = 0;
    int ekth = 0;

    for(unsigned int i=0; i<p->size(); i++) {

        // probably save m values?
        ret += ( int(pow(m, ekth++)) * ai( (*p)[i], (*s)[i], w ) ) % M; // +1?

    }

    return ret % M;
}

int g(vector<int>* p, const int k, const int w, const int m, const int M) {
    
    // it returns g(p) wich is a concatenation of h

    int hashRet = 0;
    int hashRet2 = 0;

    for(int i=0; i<k; i++) {

        vector<int>* s = getVectorS((*p).size(), w);

        hashRet = concatInts( hashRet, h( p, s, m, w, M ) );
        hashRet2 = concatInts( hashRet2, h2( p, s, m, w, M ) );

        delete s;

    }

    cout << "hashRet2 is " << hashRet2 << endl;
    return hashRet;

}

void tryHash() {

    int m = 1;
    int M = 3;
    int k = 9;
    int w = 52;

    vector<int> p(35);

    srand((unsigned) time(0));

    for(unsigned int i=0; i<p.size(); i++) {
        p[i] = rand() % 255 + 1;
    }

    int ret = g(&p, k, w, m, M) % M;

    cout << "G with outside M is " << ret << endl;
}