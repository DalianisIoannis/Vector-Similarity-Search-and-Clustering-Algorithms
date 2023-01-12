#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <errno.h>
#include <vector>

using namespace std;

typedef struct inputForm{

    vector<int> *image;
    // vector<int> image;
    int Id;

} inputForm;

class dataInput {
    private:
        int32_t magic_number;
        int32_t number_of_images;
        int32_t rows;
        int32_t cols;
        string inputFile;

        // vector<inputForm*> *iMageVector;
        vector<inputForm*> *iMageVector;

    public:

        dataInput(const string);
        ~dataInput();
        template <class T>
        void readMnist(){
        {
            ifstream file (this->inputFile, ios::binary);

            if(file.is_open()) {


                file.read( (char*)&(this->magic_number), sizeof(this->magic_number) );
                if(!file) {
                    cerr << "File IO error!\n";
                }
                this->magic_number = __builtin_bswap32(this->magic_number);
                cout << "Magic number " << this->magic_number << endl;


                file.read( (char*)&(this->number_of_images), sizeof(this->number_of_images) );
                if(!file) {
                    cerr << "File IO error!\n";
                }
                this->number_of_images = __builtin_bswap32(this->number_of_images);
                this->number_of_images = 200; /////////////////////////////////////////////////////////////////////////////////////
                cout << "Images " << this->number_of_images << endl;


                file.read( (char*)&(this->rows), sizeof(this->rows) );
                if(!file) {
                    cerr << "File IO error!\n";
                }
                this->rows = __builtin_bswap32(this->rows);
                cout << "Rows " << this->rows << endl;


                file.read( (char*)&(this->cols), sizeof(this->cols) );
                if(!file) {
                    cerr << "File IO error!\n";
                }
                this->cols = __builtin_bswap32(this->cols);
                cout << "Columns " << this->cols << endl;

                this->iMageVector = new vector<inputForm*>(this->number_of_images);

                int Id=0;

                for(int i=0; i<this->number_of_images; i++) {
                
                    inputForm* imVec = new inputForm;
                    imVec->image = new vector<int>(this->rows * this->cols);

                    imVec->Id = Id++;
                    
                    int counterPix = 0;
                    for(int j=0; j<this->rows; j++) {
                        for(int k=0; k<this->cols; k++) {

                            T temp=0;
                            file.read( (char*)&temp, sizeof(temp) );

                            // (*imVec->image).push_back((int)temp);
                            (*imVec->image)[counterPix++] = ((int)temp);

                            if(!file) {
                                cerr << "File IO error!\n";
                            }
                        }
                    }

                    (*this->iMageVector)[i] = imVec;

                }

                file.close();
            }
            else {
                cerr << "File could not be opened!\n";
            }

            }
        }

        int getImageSize();
        inputForm* getinputFormByNum(const int);
        
        int getiMageVectorSize();
        int getImagesNUM();

        vector<int> *RetTheImage(const int);
};