#include <iostream>
#include <fstream>

using namespace std;


int reverseInt (int i) 
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void read_mnist()
{
    ifstream file ("train-images.idx3-ubyte", ios::binary);
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;

        file.read((char*)&magic_number,sizeof(magic_number));     
        magic_number= reverseInt(magic_number);
        cout << magic_number << endl;
        
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);
        cout << number_of_images << endl;

        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverseInt(n_rows);
        cout << n_rows << endl;

        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverseInt(n_cols);
        cout << n_cols << endl;

        for(int i=0;i<number_of_images;++i)
        {
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read( (char*)&temp, sizeof(temp) );
                    // cout << (char*)&temp << endl;

                }
            }
        }
        file.close();
    }
}

int main(void) {

    cout << "Only just started!" << endl;


    read_mnist();



    cout << "DOKIMI" << endl;
    return 0;
}