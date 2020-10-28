#include "../headers/LSH.h"
#include "../headers/HashTable.h"

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

vector<vector<int>*> LSH(HashTablePtr L){
    
}