#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>

#include "../headers/input.h"

// int reverseInt (int i) 
// {
//     unsigned char c1, c2, c3, c4;

//     c1 = i & 255;
//     c2 = (i >> 8) & 255;
//     c3 = (i >> 16) & 255;
//     c4 = (i >> 24) & 255;

//     return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
// }

imageInput::imageInput(string iFile):inputFile(iFile)
{
    cout<<"I've just created imageInput with file " << this->inputFile <<endl;
}

imageInput::~imageInput()
{
    cout <<"I'm destroying imageInput"<<endl;
}

void imageInput::readMnist()
{

    ifstream file (this->inputFile, ios::binary);

    if(file.is_open()) {


        file.read( (char*)&(this->magic_number), sizeof(this->magic_number) );
        if(!file) {
            cerr << "File IO error!\n";
        }
        this->magic_number = __builtin_bswap32(this->magic_number);
        // magic_number= reverseInt(magic_number);
        cout << this->magic_number << endl;


        file.read( (char*)&(this->number_of_images), sizeof(this->number_of_images) );
        if(!file) {
            cerr << "File IO error!\n";
        }
        this->number_of_images = __builtin_bswap32(this->number_of_images);
        cout << this->number_of_images << endl;


        file.read( (char*)&(this->rows), sizeof(this->rows) );
        if(!file) {
            cerr << "File IO error!\n";
        }
        this->rows = __builtin_bswap32(this->rows);
        cout << this->rows << endl;


        file.read( (char*)&(this->cols), sizeof(this->cols) );
        if(!file) {
            cerr << "File IO error!\n";
        }
        this->cols = __builtin_bswap32(this->cols);
        cout << this->cols << endl;


        for(int i=0; i<this->number_of_images; i++) {
            for(int j=0; j<this->rows; j++) {
                for(int k=0; k<this->cols; k++) {

                    unsigned char temp=0;
                    file.read( (char*)&temp, sizeof(temp) );
                    if(!file) {
                        cerr << "File IO error!\n";
                    }
                }
            }
        }

        file.close();
    }
    else {
        cerr << "File could not be opened!\n";
    }

}