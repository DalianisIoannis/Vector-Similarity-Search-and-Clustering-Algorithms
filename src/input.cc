#include "../headers/LSH.h"

dataInput::dataInput(const string iFile):inputFile(iFile)
{
    cout<<"I've just created dataInput with file " << this->inputFile <<endl;
}

dataInput::~dataInput()
{
    cout <<"I'm destroying dataInput"<<endl;

    for (unsigned int i = 0; i < this->iMageVector.size(); i++) {

        delete this->iMageVector[i];

    }

}

void dataInput::readMnist()
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

        this->iMageVector.resize(this->number_of_images);
        // this->iMageVector.resize(100);

        int Id=0;

        // for(int i=0; i<100; i++) {
        for(int i=0; i<this->number_of_images; i++) {
            // cout <<i<<endl;
            
            inputForm* imVec = new inputForm;

            imVec->Id = Id++;
            
            for(int j=0; j<this->rows; j++) {
                for(int k=0; k<this->cols; k++) {

                    unsigned char temp=0;
                    file.read( (char*)&temp, sizeof(temp) );

                    (imVec->image).push_back((int)temp);


                    if(!file) {
                        cerr << "File IO error!\n";
                    }
                }
            }

            this->iMageVector[i] = imVec;

        }

        file.close();
    }
    else {
        cerr << "File could not be opened!\n";
    }

    cout << "Vector has size " << this->iMageVector.size() << endl;

    // for(int i=0; i<20; i++) {

        // cout << "Vector " << i << " has size " << this->iMageVector[i]->image.size() << " and ID " << this->iMageVector[i]->Id << endl;

    // }

}



inputForm* dataInput::getinputFormByNum(const int num) {
    return this->iMageVector[num];
}

int dataInput::getiMageVectorSize() {
    return this->iMageVector.size();
}

int dataInput::getImageSize(){
    return (this->rows * this->cols);
}