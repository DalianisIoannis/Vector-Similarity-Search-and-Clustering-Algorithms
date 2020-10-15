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