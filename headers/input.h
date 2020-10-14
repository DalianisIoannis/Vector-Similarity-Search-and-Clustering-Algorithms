#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>

using namespace std;

class imageInput {
    private:
        int32_t magic_number;
        int32_t number_of_images;
        int32_t rows;
        int32_t cols;
        string inputFile;
    public:
        imageInput(string);
        ~imageInput();
        void readMnist();
};