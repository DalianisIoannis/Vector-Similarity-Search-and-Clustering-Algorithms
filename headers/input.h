#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>
#include <vector>

using namespace std;

typedef struct inputForm{

    vector<int> image;
    int Id;

} inputForm;

class dataInput {
    private:
        int32_t magic_number;
        int32_t number_of_images;
        int32_t rows;
        int32_t cols;
        string inputFile;

        vector<inputForm*> iMageVector;

    public:
        dataInput(const string);
        ~dataInput();
        void readMnist();
        void tryVector();
        inputForm* getinputFormByNum(const int);
        int getiMageVectorSize();
};