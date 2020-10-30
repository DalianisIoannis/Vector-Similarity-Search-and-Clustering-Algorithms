#include "../headers/kMeans.h"

cluster::cluster()
{
    cout<<"I've just created cluster." <<endl;

    this->centroid = new inputForm;
}

cluster::~cluster()
{
    cout <<"I'm destroying cluster"<<endl;

    delete this->centroid;
}

// copy centroid
void cluster::informCentroid(inputForm* newC) {

    // this->centroid = newC; // will delete twice, this is the datainput assigned to and centr
    this->centroid->Id = newC->Id;

    for (unsigned int i=0; i<newC->image.size(); i++) {
        this->centroid->image.push_back( newC->image[i] );
    }
}

inputForm* cluster::getCentr() {
    return this->centroid;
}

KMeans::KMeans(const int num):numOfclusters(num)
{
    cout<<"I've just created KMeans." <<endl;

    this->clusterAr = new vector<cluster*> (this->numOfclusters);

    for(int i=0; i<this->numOfclusters; i++) {
        (*this->clusterAr)[i] = new cluster();
    }
}

KMeans::~KMeans()
{
    cout <<"I'm destroying KMeans"<<endl;

    for(int i=0; i<this->numOfclusters; i++) {
        delete (*this->clusterAr)[i];
    }

    delete this->clusterAr;
}

int KMeans::getClusNum() {
    return this->numOfclusters;
}

bool isIdInVector(const int ID, vector<inputForm*> *centrAr, const int enteredNums) {
    for (int i = 0; i < enteredNums; i++) {
        if(ID == (*centrAr)[i]->Id) {
            return true;
        }
    }
    return false;
}

float uniformNUMBER(const float maxSize) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(0.0, maxSize);
    return distrib(gen);
}

// initial centroids
vector<inputForm*>* KMeans::getKMeansCentroids(dataInput* data) {
    vector<inputForm*> *centrAr = new vector<inputForm*>(this->getClusNum());

    int t=1;    // num of centroids so far
    int dataSize = data->getiMageVectorSize(); // num of vectors
    
    cout << "Size einai " << dataSize << endl;
    
    // uniformly choose first centroid
    int un = (int)uniformNUMBER( (float)data->getiMageVectorSize()-1 );
    cout << "FIRST rand is " << un << endl;
    cout << "For index " << un << " got id " << data->getinputFormByNum(un)->Id << endl;

    (*centrAr)[t-1] = (data->getinputFormByNum(un)); // first centroid

    while(t < this->getClusNum()) { // until all centroids are chosen

        cout << "For t " << t << endl;

        vector<int> *D = new vector<int>(dataSize - t); // array of min dis from vec to centroids
        
        int Dpointer = 0;
        for (int i = 0; i < dataSize; i++) {
            
            // vector i is not already centroid
            if(isIdInVector(data->getinputFormByNum(i)->Id, centrAr, t) == false) {
                // cout << i << " no found" << endl;
                (*D)[Dpointer] = manhattanDistance( &(data->getinputFormByNum(i)->image), &((*centrAr)[0]->image) );
                for (int j = 1; j < t; j++) {
                    int manhat = manhattanDistance( &(data->getinputFormByNum(i)->image), &((*centrAr)[j]->image) );
                    if(manhat<(*D)[Dpointer]) {
                        (*D)[Dpointer] = manhat;
                    }
                }
                // cout << "manh for " << i << " is " << (*D)[Dpointer] << endl;
                Dpointer++;
            }
        }

        // compute probs
        // Dpointer--; Dpointer is pointer + 1 for zero
        vector<float> *P = new vector<float>(Dpointer);

        // find max D
        int curMax = (*D)[0];
        for (int i = 1; i < Dpointer-1; i++) {
            if( curMax < (*D)[i] ) {
                curMax = (*D)[i];
            }
        }

        // divide all by max
        (*P)[0] = 0;
        for (int i = 1; i < Dpointer; i++) {
            (*P)[i] = (*P)[i-1] + pow( ((float)((*D)[i-1]) / curMax), 2);
        }

        // for (int i = 0; i < Dpointer; i++) { cout << (*P)[i] << endl; }
        float x = uniformNUMBER( (float)(*P)[Dpointer-1] );
        cout << "Float rand is " << x << endl;

        // find r
        float smallerThanX = (*P)[0];
        int IndSmall = 0;
        // (*P)[0] is 0 always
        float LargerOrEqualX = (*P)[1];
        int IndLarge = 1;
        // cout << "x is " << x << " and P is " << (*P)[1] << " and dif " << (*P)[1] - x << endl;

        for (int i = 1; i < Dpointer; i++) {
            // cout << "x is " << x << " and P is " << (*P)[i] << " and dif " << (*P)[i] - x << endl;
            if((*P)[i] >= x) {
                if( (*P)[i]-x < LargerOrEqualX-x || LargerOrEqualX-x<0) {
                    LargerOrEqualX = (*P)[i];
                    IndLarge = i;
                }
            }
            else {
                if( x-(*P)[i] < x-smallerThanX ) {
                    smallerThanX = (*P)[i];
                    IndLarge = i;
                }
            }
        }

        if(LargerOrEqualX - x <= 0) {
            LargerOrEqualX = smallerThanX;
            IndLarge = IndSmall;
        }

        cout << "small = " << smallerThanX << " < x = " << x << " < large = " << LargerOrEqualX << endl;

        // have found r but have to calc real index of input table
        for (int i = 0; i < t-1; i++) {
            if((*centrAr)[i]->Id < IndLarge) {
                IndLarge++;
            }
        }

        cout << "Include IndLarge " << IndLarge << " with ID " << data->getinputFormByNum(IndLarge)->Id << endl;

        (*centrAr)[t] = (data->getinputFormByNum(IndLarge));

        t++;
        
        delete P;
        delete D;
    }

    return centrAr;
}

void KMeans::Clusterify(dataInput* data) {

    // initial centroids
    vector<inputForm*> *centrAr = this->getKMeansCentroids(data);
    
    cout << "IN THE END" << endl;
    for(int i=0; i<this->getClusNum(); i++) {
        cout << (*centrAr)[i]->Id << endl;
    }

    // for (unsigned int i = 0; i < 2; i++) {
    //     cout << "THIS IS IMAGE " << i << endl;
    //     for (unsigned int j = 20; j < 90; j++){ cout << "BIT " << j << " " << data->getinputFormByNum(i)->image[j] << endl; }
    // }

    // init centroids in clusters
    for(int i=0; i<this->getClusNum(); i++) {
        
        (*this->clusterAr)[i]->informCentroid( (*centrAr)[i] );

        (*centrAr)[i] = NULL;   // doesnt still need to point it
    }

    this->assignData(data);
 
    delete centrAr;
}

int KMeans::returnClusterIndex(inputForm* newInp) {

    int minMan = manhattanDistance(&newInp->image, &((*this->clusterAr)[0]->getCentr()->image) );
    int ind = 0;

    for(unsigned int i=1; i<this->clusterAr->size(); i++) {
        int newM = manhattanDistance(&newInp->image, &((*this->clusterAr)[i]->getCentr()->image) );
        if(newM<minMan) {
            minMan = newM;
            ind = i;
        }
    }

    return ind;
}

void KMeans::assignData(dataInput* data) {

    vector<int> *infoAr = new vector<int>(data->getiMageVectorSize());
    vector<list <inputForm*>*> *clusterPoints = new vector<list <inputForm*>*>(this->getClusNum());

    for(int i=0; i<this->getClusNum(); i++) {
        (*clusterPoints)[i] = new list <inputForm*>;
    }

    for(int i=0; i<data->getiMageVectorSize(); i++) { (*infoAr)[i] = -1; } // none assigned

    int reps=0;
    bool StayedSame = true;
    while( reps<10 && StayedSame==true) {  //and few changes


        for(int i=0; i<data->getiMageVectorSize(); i++) { // every input vector

            int ClusInd = this->returnClusterIndex( data->getinputFormByNum(i) ); // where should be inserted
                        
            if((*infoAr)[i] != ClusInd) { // not in that cluster already
                if( (*infoAr)[i] != -1 ) { // it was elsewhere
                    // remove from last cluster
                    
                    list <inputForm*> :: iterator it; 
                    it = (*clusterPoints)[(*infoAr)[i]]->begin(); // remove from other cluster
                    while(it != (*clusterPoints)[i]->end()) {

                        if( (*it)->Id == i ) {
                            // put in correct
                            (*clusterPoints)[ClusInd]->push_back((*it));
                            (*it) = NULL;
                            it = (*clusterPoints)[i]->end();
                        }

                        ++it;
                    }

                }
                else { // first input
                    // need to store a copy
                    inputForm *copied = new inputForm;
                    copied->image.resize(data->getinputFormByNum(i)->image.size());
                    copied->Id = data->getinputFormByNum(i)->Id;
                    
                    (*clusterPoints)[ClusInd]->push_back(copied);
                    
                }
                (*infoAr)[i] = ClusInd;
                StayedSame = false;
            }

        }

        // change centroids
        // new centroids
        for(int i=0; i<this->getClusNum(); i++) {   // for every cluster
            for(unsigned int j=0; j<data->getinputFormByNum(0)->image.size(); j++) { // for every vector dimension -- column

            }
        }

        reps++;

    }

    for(int i=0; i<this->getClusNum(); i++) {
        cout << "For cluster " << i << endl;
        
        list <inputForm*> :: iterator it;
        for(it = (*clusterPoints)[i]->begin(); it!=(*clusterPoints)[i]->end(); it++) {
            cout << "  " << (*it)->Id;
        }
        cout << endl;
    }

    for(int i=0; i<this->getClusNum(); i++) {
        
        list <inputForm*> :: iterator it;
        for(it = (*clusterPoints)[i]->begin(); it!=(*clusterPoints)[i]->end(); it++) {
            delete (*it);
        }
        
        delete ((*clusterPoints)[i]);
    }

    delete clusterPoints;
    delete infoAr;
}