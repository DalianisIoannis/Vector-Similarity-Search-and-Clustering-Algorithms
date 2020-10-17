#include "../headers/input.h"
#include "../headers/LSH.h"

// int reverseInt (int i) {
//     unsigned char c1, c2, c3, c4;

//     c1 = i & 255;
//     c2 = (i >> 8) & 255;
//     c3 = (i >> 16) & 255;
//     c4 = (i >> 24) & 255;

//     return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
// }

dataInput::dataInput(const string iFile):inputFile(iFile)
{
    cout<<"I've just created dataInput with file " << this->inputFile <<endl;
}

dataInput::~dataInput()
{
    cout <<"I'm destroying dataInput"<<endl;
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

        this->imVector.resize(this->number_of_images);

        for(int i=0; i<this->number_of_images; i++) {

            // vector<int> v1;
            
            for(int j=0; j<this->rows; j++) {
                for(int k=0; k<this->cols; k++) {

                    unsigned char temp=0;
                    file.read( (char*)&temp, sizeof(temp) );

                    // v1.push_back((int)temp);
                    this->imVector[i].push_back((int)temp);

                    if(!file) {
                        cerr << "File IO error!\n";
                    }
                }
            }

            // this->imVector.push_back(v1);

        }

        file.close();
    }
    else {
        cerr << "File could not be opened!\n";
    }

    cout << "Size of vector is " << this->imVector.size() << endl;

    for(int i=0; i<this->number_of_images; i++) {

        cout << "Vector " << i << " has size " << this->imVector[i].size() << endl;

    }

}

void dataInput::tryVector() {

    int kkk = 0;
    
    this->imVector.resize(50);

    for(int i=0; i<50; i++) {

        // vector<int> v1;

        for(int j=0; j<50; j++) {
            

            this->imVector[i].push_back(kkk);
            // v1.push_back(kkk);
            
            kkk++;

        }

        // this->imVector.push_back(v1);

    }

    // for (unsigned int i = 0; i < this->imVector.size(); i++) {
    //     for (unsigned int j = 0; j < this->imVector[i].size(); j++){
    //         cout << this->imVector[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // int manh = manhattanDistance( &(this->imVector)[0], &(this->imVector)[1] );
    // cout << "distance is " << manh << endl;

}