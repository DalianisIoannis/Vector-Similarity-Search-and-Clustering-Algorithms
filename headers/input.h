#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>
#include <vector>

using namespace std;

class dataInput {
    private:
        int32_t magic_number;
        int32_t number_of_images;
        int32_t rows;
        int32_t cols;
        string inputFile;

        vector < vector<int> > imVector;

    public:
        dataInput(const string);
        ~dataInput();
        void readMnist();
        void tryVector();
};