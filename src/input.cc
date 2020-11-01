#include "../headers/input.h"
#include "../headers/LSH.h"

dataInput::dataInput(const string iFile):inputFile(iFile)
{
    cout<<"I've just created dataInput with file " << this->inputFile <<endl;
}

dataInput::~dataInput()
{
    cout <<"I'm destroying dataInput"<<endl;

    for (unsigned int i = 0; i < this->iMageVector->size(); i++) {

        delete (*this->iMageVector)[i]->image;
        delete (*this->iMageVector)[i];

    }

    delete this->iMageVector;

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
        // this->number_of_images = 200; /////////////////////////////////////////////////////////////////////////////////////
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

        // for(int i=0; i<200; i++) {
        for(int i=0; i<this->number_of_images; i++) {
            
            inputForm* imVec = new inputForm;
            imVec->image = new vector<int>(this->rows * this->cols);
            // imVec->image = new vector<int>();

            imVec->Id = Id++;
            
            int counterPix = 0;
            for(int j=0; j<this->rows; j++) {
                for(int k=0; k<this->cols; k++) {

                    unsigned char temp=0;
                    file.read( (char*)&temp, sizeof(temp) );

                    // (imVec->image).push_back((int)temp);
                    // (*imVec->image).push_back((int)temp);
                    (*imVec->image)[counterPix++] = ((int)temp);

                    if(!file) {
                        cerr << "File IO error!\n";
                    }
                }
            }

            // this->iMageVector[i] = imVec;
            (*this->iMageVector)[i] = imVec;

        }

        file.close();
    }
    else {
        cerr << "File could not be opened!\n";
    }

    // cout << "iMageVector has sizeeeeeeee " << this->iMageVector->size() << endl;
    // for(int i=0; i<this->iMageVector->size(); i++) {
    //     cout << "   Vector " << i << " has size " << (*this->iMageVector)[i]->image->size() << " and ID " << (*this->iMageVector)[i]->Id << endl;
    // }

}

void dataInput::tryVector() {


    // for (unsigned int i = 0; i < 2; i++) {
    //     cout << "THIS IS IMAGE " << i << endl;
    //     for (unsigned int j = 0; j < this->iMageVector[i]->image.size(); j++){
    //         cout << "BIT " << j << " " << this->iMageVector[i]->image[j] << endl;
    //     }
    // }

    int manh = manhattanDistance( (*this->iMageVector)[0]->image, (*this->iMageVector)[1]->image );
    cout << "distance is " << manh << endl;
    // cout << "IMAGE 0 has size " << (*this->iMageVector)[0]->image->size() << endl;

}

inputForm* dataInput::getinputFormByNum(const int num) {
    return (*this->iMageVector)[num];
}

int dataInput::getiMageVectorSize() {
    return (*this->iMageVector).size();
}

int dataInput::getImagesNUM() {
    return this->number_of_images;
}
vector<int> *dataInput::RetTheImage(const int num) {

    return (*this->iMageVector)[num]->image;
}