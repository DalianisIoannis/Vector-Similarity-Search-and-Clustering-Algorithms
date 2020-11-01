#include "../headers/kMeans.h"

cluster::cluster()
{
    cout<<"I've just created cluster." <<endl;
    // this->centroidVec = new vector<int>;
}

cluster::~cluster()
{
    cout <<"I'm destroying cluster"<<endl;

    // this->centroidVec = NULL;
    delete this->centroidVec;
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
    // cout << "   IN isIdInVector centrAr->size() " << centrAr->size() << " AND enteredNums " << enteredNums << endl;
    for (int i = 0; i < enteredNums; i++) {
        if(ID == (*centrAr)[i]->Id) { return true; }
    }
    return false;
}

float uniformNUMBER(const float maxSize) {
    std::random_device rd;      //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());     //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(0.0, maxSize);
    return distrib(gen);
}

int getVecMedian(vector<int>* v) {
    size_t n = v->size() / 2;
    
    nth_element(v->begin(), v->begin()+n, v->end());
    
    return (*v)[n];
}

void KMeans::Clusterify(dataInput* data) {

    // initial centroids FIX
    vector<inputForm*> *centrAr = this->getKMeansCentroids(data);
    
    cout << "IN THE END" << endl;
    for(int i=0; i<this->getClusNum(); i++) {
        cout << (*centrAr)[i]->Id << endl;
    }

    for(int i=0; i<this->getClusNum(); i++) {

        vector<int>* tmp = (*centrAr)[i]->image;
        
        // (*this->clusterAr)[i]->NewCentroidVec( tmp );
        (*this->clusterAr)[i]->CopyCenVec( tmp );
        
        // (*this->clusterAr)[i]->DELCentroidVec();
        // (*this->clusterAr)[i]->centroidVec = new vector<int>;
        // (*centrAr)[i]->image = NULL;
    }

    // for (unsigned int i = 0; i < 2; i++) {
    //     cout << "TOTAL IMS " << data->getImagesNUM() << endl;
    //     cout << "IND is " << (*data->RetTheImage(0))[0] << endl;
    //     cout << "IMAGE SIZE is " << (&(*data->RetTheImage(0)))->size() << endl;
    //     for (unsigned int j = 0; j <   (&(*data->RetTheImage(i)))->size(); j++){
    //         cout << "   BIT " << j << " " << (*data->RetTheImage(0))[j] << endl;
    //     }
    // }

    for(int i=0; i<this->getClusNum(); i++) {
        cout << "CLUSTER " << i << " has d 0 " << (*(*this->clusterAr)[i]->returncentroidVec())[0] << " and 1 " << (*(*this->clusterAr)[i]->returncentroidVec())[1] << " and size " << (*this->clusterAr)[i]->returncentroidVec()->size() << endl;
        // for(unsigned int j=0; j< (*this->clusterAr)[i]->returncentroidVec()->size(); j++) {
        //     cout << "   stoixeio " << j << " einai " << (*(*this->clusterAr)[i]->returncentroidVec())[j] << endl;
        // }
    }

    // for(int i=0; i<data->getiMageVectorSize(); i++) { cout << "   in Clusterify Vector before assign " << i << " has size " << data->RetTheImage(i)->size() << endl; }

    this->assignData(data);
 
    delete centrAr;
}

int KMeans::returnClusterIndex(inputForm* newInp) {

    // for(unsigned int j=0; j< (*this->clusterAr)[0]->returncentroidVec()->size(); j++) { cout << "   stoixeio " << j << " einai " << (*(*this->clusterAr)[0]->returncentroidVec())[j] << endl; }
    // for(unsigned int j=0; j< newInp->image->size(); j++) { cout << "   stoixeio " << j << " einai " << (*newInp->image)[j] << endl; }
    
    int minMan = manhattanDistance(newInp->image, ((*this->clusterAr)[0]->returncentroidVec()) );
    int ind = 0;

    for(unsigned int i=1; i<this->clusterAr->size(); i++) {
        int newM = manhattanDistance(newInp->image, ((*this->clusterAr)[i]->returncentroidVec()) );
        if(newM<minMan) {
            minMan = newM;
            ind = i;
        }
    }

    return ind;
}

void KMeans::assignData(dataInput* data) {

    for(int i=0; i<this->getClusNum(); i++) {
        // vector<int>* lastIn = (*this->clusterAr)[i]->returnindexesOfAssVecs();
        (*this->clusterAr)[i]->initindexesOfAssVecs(1000);  // edo mesa exei ta indexes ton vectors gia kathe cluster
    }

    vector<int> *infoAr = new vector<int>(data->getiMageVectorSize());  // assignment for each vec

    // cout << "TOTAL IMAGES ARE " << data->getiMageVectorSize() << endl;;

    for(int i=0; i<data->getiMageVectorSize(); i++) { (*infoAr)[i] = -1; } // none assigned

    // for(int i=0; i<data->getiMageVectorSize(); i++) { cout << "   in assignData Vector " << i << " has size " << data->RetTheImage(i)->size() << endl; }

    int reps=0;
    bool StayedSame = false;
    while( reps<10 && StayedSame==false) {

        StayedSame = true; // if even one changes then repeat
        
        cout << "REP " << reps << " for data->getiMageVectorSize() " << data->getiMageVectorSize() << endl;

        for(int i=0; i<data->getiMageVectorSize(); i++) { // every input vector

            // cout << "   GIVE " << i << " with size " << data->getinputFormByNum(i)->image->size() <<endl;
            int ClusInd = this->returnClusterIndex( data->getinputFormByNum(i) ); // where should be inserted

            if((*infoAr)[i] != ClusInd) { // not in that cluster already
            
                (*infoAr)[i] = ClusInd;

                // assign vec

                // // if nothing changed
                StayedSame = false;

            }

        }
        // change centroids
        if(StayedSame==true) {  // compute new centroids if didn t change
            for(int clus=0; clus<this->getClusNum(); clus++) {   // for every cluster
            
                // vector<int>* newC = new vector<int>(data->getinputFormByNum(0)->image->size());
                int newCIndex = 0;
                // cout << "data->getinputFormByNum(0)->image.size() " << data->getinputFormByNum(0)->image->size() << endl;
                // cout << "data->getImagesNUM() " << data->getImagesNUM() << endl;
                
                for(unsigned int j=0; j<data->getinputFormByNum(0)->image->size(); j++) { // for every vector dimension -- column
                    
                    vector<int> *myV = new vector<int>(data->getImagesNUM());
                    
                    for(int k=0; k<data->getImagesNUM(); k++) { // every line
                        (*myV)[k] = (*(data->getinputFormByNum(k)->image))[j] ;   // vector of all column nums
                    }

                    // (*newC)[newCIndex++] = getVecMedian(myV);
                    // (*this->clusterAr)[clus]->InputNewCentrCoord(getVecMedian(myV), newCIndex-1);

                    (*this->clusterAr)[clus]->InputNewCentrCoord(getVecMedian(myV), newCIndex);


                    delete myV;
                }

                // new centroid
                // (*this->clusterAr)[clus]->NewCentroidVec( newC );
                // (*this->clusterAr)[clus]->DeleteAndNewCentroidVec( newC );

                // for(unsigned int k=0; k<newC->size(); k++) {}
                // delete newC;

            }
        }

        reps++;
    }

    cout << "Indexing " << endl;
    // for(unsigned int j=0; j<infoAr->size(); j++) {
    //     cout << "   Vec " << j << " in cluster " << (*infoAr)[j] << endl;
    // }

    for(int i=0; i<this->getClusNum(); i++) {
        // cout << "CLUSTER " << i << endl;
        // for(unsigned int j=0; j< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); j++) {
        //     cout << "   " << (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j] << endl;
        // }
        (*this->clusterAr)[i]->deleteindexesOfAssVecs();
    }
    
    delete infoAr;
}

vector<int>* cluster::returnindexesOfAssVecs() {
    return this->indexesOfAssVecs;
}

vector<int>* cluster::returncentroidVec() {
    return this->centroidVec;
}

void cluster::initindexesOfAssVecs(const int sssize) {
    this->indexesOfAssVecs = new vector<int>;
    // this->indexesOfAssVecs = new vector<int>(sssize);
    // for(unsigned int i=0; i<this->indexesOfAssVecs->size(); i++) {
    //     (*this->indexesOfAssVecs)[i] = -1;
    // }
}

void cluster::addVecToclus(const int indexV) {
    this->indexesOfAssVecs->push_back(indexV);
}

void cluster::deleteindexesOfAssVecs() {
    delete this->indexesOfAssVecs;
}

void cluster::DELCentroidVec() {
    delete this->centroidVec;
}

void cluster::NewCentroidVec(vector<int>* nW) {

    // this->centroidVec = new vector<int>;
    this->centroidVec = nW;
}

void cluster::CopyCenVec(vector<int>* nW) {
    this->centroidVec = new vector<int>(nW->size());
    for (unsigned int i = 0; i < nW->size(); i++){
        (*this->centroidVec)[i] = (*nW)[i];
    }
    
}

void cluster::DeleteAndNewCentroidVec(vector<int>* nW) {

    delete this->centroidVec;
    // this->centroidVec = new vector<int>;
    this->centroidVec = nW;
}

void cluster::InputNewCentrCoord(const int num, const int coord) {

    // delete this->centroidVec;
    // this->centroidVec = new vector<int>;
    (*this->centroidVec)[coord] = num;
}

vector<inputForm*>* KMeans::getKMeansCentroids(dataInput* data) {
    vector<inputForm*> *centrAr = new vector<inputForm*>(this->getClusNum());   // initial centroids

    int t=0;    // num of centroids so far
    int dataSize = data->getiMageVectorSize(); // num of vectors

    int un = (int)uniformNUMBER( (float)data->getiMageVectorSize()-1 ); // uniformly choose first centroid
    
    (*centrAr)[t] = (data->getinputFormByNum(un)); // first centroid assign with pointer


    while(t < this->getClusNum() - 1) { // until all centroids are chosen
    // while(t < this->getClusNum()) { // until all centroids are chosen

        cout << "For centroid " << t + 1 << endl;

        // vector<int> *D = new vector<int>(dataSize - t - 1); // array of min dis from vec to centroids
        vector<int> *D = new vector<int>(dataSize - t - 1 + 2); // array of min dis from vec to centroids

        int Dpointer = 0;
        for (int i = 0; i < dataSize; i++) {
            
            // vector i is not already centroid
            // if(isIdInVector(data->getinputFormByNum(i)->Id, centrAr, t+1) == false) {
            if(isIdInVector(data->getinputFormByNum(i)->Id, centrAr, t+1) == false && Dpointer < dataSize - t - 1) {

                (*D)[Dpointer] = manhattanDistance( (data->getinputFormByNum(i)->image), ((*centrAr)[0]->image) );

                for (int j = 1; j < t+1; j++) {
                    int manhat = manhattanDistance( (data->getinputFormByNum(i)->image), ((*centrAr)[j]->image) );

                    if( manhat < (*D)[Dpointer] ) {
                        (*D)[Dpointer] = manhat;
                    }
                }

                Dpointer++;

            }
        }

        //  APO EDO KAI KATO PALI

        // compute probs
        // Dpointer--; Dpointer is pointer + 1 for zero
        // int bound = ;
        vector<float> *P = new vector<float>(dataSize - t + 1 + 1);

        // find max D
        int curMax = (*D)[0];
        for (int i = 1; i < dataSize - t - 1; i++) {
            if( curMax < (*D)[i] ) {
                curMax = (*D)[i];
            }
        }

        // divide all by max
        (*P)[0] = 0;
        for (int i = 1; i < dataSize - t + 1 + 1; i++) {
            (*P)[i] = (*P)[i-1] + pow( ((float)((*D)[i-1]) / curMax), 2);
        }

        float x = uniformNUMBER( (float)(*P)[dataSize - t + 1 + 1 - 1] );

        float smallerThanX = (*P)[0];
        int IndSmall = 0;
        
        // (*P)[0] is 0 always        
        float LargerOrEqualX = (*P)[1];
        int IndLarge = 1;

        for (int i = 1; i < dataSize - t + 1 + 1; i++) {
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
        for (int i = 0; i < t+1; i++) {
            if((*centrAr)[i]->Id < IndLarge) {
                IndLarge++;
            }
        }

        if( t+1<this->getClusNum() )
            (*centrAr)[t+1] = (data->getinputFormByNum(IndLarge));

        t++;
        
        delete P;
        delete D;

    }


    return centrAr;
}