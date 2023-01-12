#include "../headers/kMeans.h"

cluster::cluster()
{
    cout<<"I've just created cluster." <<endl;
}

void cluster::delcentroidVec() {
    delete this->centroidVec;
}

cluster::~cluster()
{
    cout <<"I'm destroying cluster"<<endl;
    // delete this->centroidVec;
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

    // for(int i=0; i<this->getClusNum(); i++) {
    //     (*this->clusterAr)[i]->deleteindexesOfAssVecs();
    // }

    // for(int i=0; i<this->numOfclusters; i++) {
    //     delete (*this->clusterAr)[i];
    // }

    delete this->clusterAr;

}

int KMeans::getClusNum() {
    return this->numOfclusters;
}

void cluster::print_assigned_vectors_ids() {
    for(long unsigned int i=0; i<this->indexesOfAssVecs->size(); i++) {
        // cout <<"        " << (*this->indexesOfAssVecs)[i] << endl;
        cout << " " << (*this->indexesOfAssVecs)[i];
    }
    cout << endl;
}

bool isIdInVector(const int ID, vector<inputForm*> *centrAr, const int enteredNums)
{
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
    
    // size_t n = v->size() / 2;
    // nth_element(v->begin(), v->begin()+n, v->end());
    // return (*v)[n];

    return (int)accumulate( v->begin(), v->end(), 0.0)/v->size();

}

void KMeans::ClusterifyWITHLsh(dataInput* data) {

    int L = 3;
    HashTablePtr Tables[L];
    int k=6;
    int w=10;
    int m = pow(2,31) - 5;

    dataInput *inputset = data;
    
    int M = inputset->getiMageVectorSize() / 8;

    for (int i = 0 ; i < L ; i++){
        Tables[i] = new HashTable(inputset->getImageSize(), k, w, m, M) ;
        for (int j = 0 ; j < inputset->getiMageVectorSize() ; j++){
            Tables[i]->Table_Insert(inputset->getinputFormByNum(j));
        }
        cout <<"Pushed "<<inputset->getiMageVectorSize()<<" elements on Hash Table "<<i<<endl;
    }

    vector<inputForm*> *centrAr = this->getKMeansCentroids(data);

    cout << "Initial Cntroids" << endl;
    for(int i=0; i<this->getClusNum(); i++) {
        cout << (*centrAr)[i]->Id << endl;
    }

    // for(int i=0; i<this->getClusNum(); i++) {

    //     vector<int>* tmp = (*centrAr)[i]->image;
        
    //     (*this->clusterAr)[i]->CopyCenVec( tmp );
        
    // }

    // for(int i=0; i<this->getClusNum(); i++) {
    //     cout << "CLUSTER " << i << " has d 0 " << (*(*this->clusterAr)[i]->returncentroidVec())[0] << " and 1 " << (*(*this->clusterAr)[i]->returncentroidVec())[1] << " and size " << (*this->clusterAr)[i]->returncentroidVec()->size() << endl;
    //     // for(unsigned int j=0; j< (*this->clusterAr)[i]->returncentroidVec()->size(); j++) { cout << "   stoixeio " << j << " einai " << (*(*this->clusterAr)[i]->returncentroidVec())[j] << endl; }
    // }

    for(int i=0; i<this->numOfclusters; i++) {
        delete (*this->clusterAr)[i];
    }

    delete centrAr;
}

void KMeans::Clusterify(dataInput* data, std::string output_file) {

    // ofstream myfile;
    // myfile.open (output_file);
    // myfile << "Eimai from Means.\n";

    vector<inputForm*> *centrAr = this->getKMeansCentroids(data);
    
    cout << "Initial Cntroids" << endl;
    for(int i=0; i<this->getClusNum(); i++) {

        cout << (*centrAr)[i]->Id << endl;

        vector<int>* tmp = (*centrAr)[i]->image;
        
        (*this->clusterAr)[i]->CopyCenVec( tmp );
        
    }

    // for(int i=0; i<this->getClusNum(); i++) {
    //     cout << "CLUSTER " << i << " has d 0 " << (*(*this->clusterAr)[i]->returncentroidVec())[0] << " and 1 " << (*(*this->clusterAr)[i]->returncentroidVec())[1] << " and size " << (*this->clusterAr)[i]->returncentroidVec()->size() << endl;
    //     // for(unsigned int j=0; j< (*this->clusterAr)[i]->returncentroidVec()->size(); j++) { cout << "   stoixeio " << j << " einai " << (*(*this->clusterAr)[i]->returncentroidVec())[j] << endl; }
    // }

    this->assignData(data);

    cout << "RETURN FROM CLUSTERING" << endl << endl;

    // print images of every cluster
    for(int i=0; i<this->getClusNum(); i++) {
        
        cout << "\n   Centroid vector of cluster " << i << endl;
        for(long unsigned int j=0; j<(*this->clusterAr)[i]->centroidVec->size(); j++) {   // centroid
            cout << (*(*this->clusterAr)[i]->centroidVec)[j] << " ";
        }
        
        cout << "\n   Assigned vectors of cluster " << i << endl;
        (*this->clusterAr)[i]->print_assigned_vectors_ids();
    }

    this->Silhouette(data);

    for(int i=0; i<this->getClusNum(); i++) {                       // gia kanoniko
        (*this->clusterAr)[i]->deleteindexesOfAssVecs();
    }

    for(int i=0; i<this->numOfclusters; i++) {

        delete (*this->clusterAr)[i]->centroidVec;

        // delete (*this->clusterAr)[i]->delcentroidVec();

        delete (*this->clusterAr)[i];
    }

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

    vector<int> *infoAr = new vector<int>(data->getiMageVectorSize());  // assignment for each vec

    for(int i=0; i<data->getiMageVectorSize(); i++) { (*infoAr)[i] = -1; } // none assigned

    int reps=0;
    int threshold = 7;
    bool StayedSame = false;
    while( reps<threshold && StayedSame==false) {

        cout << "\nREP " << reps << " for data->getiMageVectorSize() " << data->getiMageVectorSize() << endl;
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // centroids
        // for(int clus=0; clus<this->getClusNum(); clus++) {
        //     // cout << "   Cluster " << clus << " has size " << ((*this->clusterAr)[clus])->returncentroidVec()->size() << endl;
        //     int fjsnjcdf=0;
        //     cout << "   Cluster " << clus << endl;
        //     for(unsigned int j=0; j< ((*this->clusterAr)[clus])->returncentroidVec()->size() ; j++) {
        //         cout << (*((*this->clusterAr)[clus])->returncentroidVec())[j] << "  ";
        //         if(++fjsnjcdf==28) {
        //             fjsnjcdf=0;
        //             cout << endl;
        //         }
        //     }
        //     cout << endl;
        // }
        ////////////////////////////////////////////////////////////////////////////////////////////////

        StayedSame = true; // if even one changes then repeat
        
        for(int i=0; i<data->getiMageVectorSize(); i++) { // every input vector

            int ClusInd = this->returnClusterIndex( data->getinputFormByNum(i) ); // where should be inserted

            if((*infoAr)[i] != ClusInd) { // not in that cluster already
            
                (*infoAr)[i] = ClusInd;
                // if nothing changed
                StayedSame = false;

            }

        }

        // make array with centrs of each clus
        for(int i=0; i<this->getClusNum(); i++) {
            (*this->clusterAr)[i]->initindexesOfAssVecs();  // edo mesa exei ta indexes ton vectors gia kathe cluster
        }
        for(int i=0; i<data->getiMageVectorSize(); i++) {
            // cout << " i " << i << " (*infoAr)[i] " << (*infoAr)[i] << endl;
            (*this->clusterAr)[(*infoAr)[i]]->addVecToclus(i);
        }

        // for(int i=0; i<this->getClusNum(); i++) {
        //     cout << "   Cluster " << i << " has :" << (*this->clusterAr)[i]->ReturnNewindexesOfAssVecsSize() << " assigned " << endl;
        // }

        // change centroids
        if(StayedSame==false) {  // compute new centroids if didn t change

            // cout << "   FOR REAR " << endl;

            for(int clus=0; clus<this->getClusNum(); clus++) {   // for every cluster

                // cout << "       Cluster " << clus << endl;
                
                // int fjsnjcdf=0;
                int newCIndex = 0;
                // cout << "data->getinputFormByNum(0)->image.size() " << data->getinputFormByNum(0)->image->size() << endl;
                // cout << "data->getImagesNUM() " << data->getImagesNUM() << endl;
                
                for(unsigned int j=0; j<data->getinputFormByNum(0)->image->size(); j++) { // for every vector column
                    
                    vector<int> *myV = new vector<int>(data->getImagesNUM());

                    // median ton dikon tou
                    for(int k=0; k<(*this->clusterAr)[clus]->ReturnNewindexesOfAssVecsSize(); k++) {
                        (*myV)[k] = (*(data->getinputFormByNum( (*(*this->clusterAr)[clus]->returnindexesOfAssVecs())[k] )->image))[ j ] ;   // vector of all column nums
                    }

                    int newCoord;
                    if((*this->clusterAr)[clus]->ReturnNewindexesOfAssVecsSize()!=0) {
                        newCoord = getVecMedian(myV);
                    }
                    else {
                        // cout << "  KANENA MESA"; // SOS
                        // newCoord = (*(*this->clusterAr)[clus]->returncentroidVec())[j];
                        newCoord = 0;
                    }

                    // cout << newCoord << "  ";
                    // if(++fjsnjcdf==28) {
                    //     fjsnjcdf=0;
                    //     cout << endl;
                    // }

                    (*this->clusterAr)[clus]->InputNewCentrCoord(newCoord, newCIndex++);

                    delete myV;
                }
            }

            cout << endl;
        }

        reps++;
        
        if( reps<threshold && StayedSame==false) {
            for(int i=0; i<this->getClusNum(); i++) {
                (*this->clusterAr)[i]->deleteindexesOfAssVecs();
            }
        }
    }

    // cout << "Indexing " << endl;
    // for(unsigned int j=0; j<infoAr->size(); j++) { cout << "   Vec " << j << " in cluster " << (*infoAr)[j] << endl; }

    // for(int i=0; i<this->getClusNum(); i++) {
    //     cout << "CLUSTER " << i << endl;
    //     for(unsigned int j=0; j< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); j++) { cout << "   " << (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j] << endl; }
    // }
    
    delete infoAr;
}

vector<int>* cluster::returnindexesOfAssVecs() {
    return this->indexesOfAssVecs;
}

vector<int>* cluster::returncentroidVec() {
    return this->centroidVec;
}

void cluster::initindexesOfAssVecs() {
    this->indexesOfAssVecs = new vector<int>;
}

void cluster::addVecToclus(const int indexV) {
    this->indexesOfAssVecs->push_back(indexV);
}

void cluster::deleteindexesOfAssVecs() {
    delete this->indexesOfAssVecs;
}

int cluster::ReturnNewindexesOfAssVecsSize() {
    return (this->indexesOfAssVecs)->size();
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
    this->centroidVec = nW;
}

void cluster::InputNewCentrCoord(const int num, const int coord) {

    (*this->centroidVec)[coord] = num;
}

vector<inputForm*>* KMeans::getKMeansCentroids(dataInput* data) {
    vector<inputForm*> *centrAr = new vector<inputForm*>(this->getClusNum());   // initial centroids

    int t=0;    // num of centroids so far
    int dataSize = data->getiMageVectorSize(); // num of vectors

    int un = (int)uniformNUMBER( (float)data->getiMageVectorSize()-1 ); // uniformly choose first centroid
    
    (*centrAr)[t] = (data->getinputFormByNum(un)); // first centroid assign with pointer


    while(t < this->getClusNum() - 1) { // until all centroids are chosen

        cout << "For centroid " << t + 1 << endl;

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

        // compute probs
        // Dpointer--; Dpointer is pointer + 1 for zero
        int bound = dataSize - t + 1 + 1;
        vector<float> *P = new vector<float>(bound);

        // find max D
        int curMax = (*D)[0];
        for (int i = 1; i < dataSize - t - 1; i++) {
            if( curMax < (*D)[i] ) {
                curMax = (*D)[i];
            }
        }

        // divide all by max
        (*P)[0] = 0;
        for (int i = 1; i < bound; i++) {
            (*P)[i] = (*P)[i-1] + pow( ((float)((*D)[i-1]) / curMax), 2);
        }

        float x = uniformNUMBER( (float)(*P)[dataSize - t + 1 + 1 - 1] );

        float smallerThanX = (*P)[0];
        int IndSmall = 0;
        
        // (*P)[0] is 0 always        
        float LargerOrEqualX = (*P)[1];
        int IndLarge = 1;

        for (int i = 1; i < bound; i++) {
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

void KMeans::Silhouette(dataInput* data) {

    int dataSize = data->getiMageVectorSize(); // num of vectors
    vector<int> *A = new vector<int>(dataSize); // array of min dis from vec to centroids
    // cout << "A has size " << A->size() << endl;

    cout << endl << "IN Silhouette " << endl;
    for(int i=0; i<this->getClusNum(); i++) {
        // cout << "CLUSTER " << i << endl;
        cout << "Cluster " << i << " has :" << (*this->clusterAr)[i]->ReturnNewindexesOfAssVecsSize() << " assigned " << endl;
        // for(unsigned int j=0; j< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); j++) { cout << "   " << (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j] << endl; }
    }

    int Aindex=0;
    for(int i=0; i<this->getClusNum(); i++) { // apo kathe cluster

        for(unsigned int j=0; j< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); j++) { // gia kathe tou vector
            // cout << "   " << (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j] << endl;
            int curInd = (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j];
            (*A)[Aindex] = 0;

            for(unsigned int k=0; k< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); k++) {
                int secInd = (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[k];
                if(secInd!=curInd) {
                    // (*A)[Aindex] += 1;
                    (*A)[Aindex] += manhattanDistance( (data->getinputFormByNum(secInd)->image), (data->getinputFormByNum(curInd)->image) );
                    // manhattanDistance( (data->getinputFormByNum(i)->image), ((*centrAr)[0]->image) );
                }
                // else { (*A)[Aindex] = -1; //eaUto tou }
            }

            // average
            (*A)[Aindex] = (*A)[Aindex] / (*this->clusterAr)[i]->returnindexesOfAssVecs()->size();

            Aindex++;
        }

    }

    // siloueta kanoniki
    vector<int> *BTMP = new vector<int>(dataSize); // array of min dis from vec to other centrs
    for(int i=0; i<this->getClusNum(); i++) { // apo kathe cluster
        
        for(unsigned int j=0; j< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); j++) { // gia kathe tou vector
            int bigDis = 1000000000;
            int secCloserClus = -1;
            int curInd = (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j];
            for(int k=0; k<this->getClusNum(); k++) {
                
                if (i!=k){ // apo kathe allo cluster metrao apostasi apo kentro
                    int dis = manhattanDistance( (*this->clusterAr)[k]->centroidVec, (data->getinputFormByNum(curInd)->image) );
                    // cout << "distance from vec " << j << " of cluster " << i << " to centroid of cluster " << k << " is " << dis << endl;
                    if (dis<bigDis) {
                        bigDis = dis;
                        secCloserClus = k;
                    }
                }

            }
            // cout << "       vec " << j << " of cluster " << i << " closer to " << secCloserClus << " with dis " << bigDis << endl;
            //  have found second closest cluster to vec
            int BTMPindex=0;
            for(unsigned int jj=0; jj< (*this->clusterAr)[secCloserClus]->returnindexesOfAssVecs()->size(); jj++) { // gia kathe vector tou second closest cluster
                curInd = (*(*this->clusterAr)[secCloserClus]->returnindexesOfAssVecs())[jj];
                (*BTMP)[BTMPindex] = 0;

                for(unsigned int k=0; k< (*this->clusterAr)[secCloserClus]->returnindexesOfAssVecs()->size(); k++) {
                    int secInd = (*(*this->clusterAr)[secCloserClus]->returnindexesOfAssVecs())[k];
                    if(secInd!=curInd) {
                        (*BTMP)[BTMPindex] += manhattanDistance( (data->getinputFormByNum(secInd)->image), (data->getinputFormByNum(curInd)->image) );
                    }
                }
                // average
                (*BTMP)[BTMPindex] = (*BTMP)[BTMPindex] / (*this->clusterAr)[secCloserClus]->returnindexesOfAssVecs()->size();
                BTMPindex++;
            }
        }
        // cout << endl;
    }

    vector<double> *S = new vector<double>(dataSize); // array of siloueta

    // vector<int> *B = computeB(data);    // wrong B

    // for(unsigned int k=0; k< S->size(); k++) {
    //     // (*S)[k] = (float)(( (float)(*B)[k] - (*A)[k]) / (float)std::max((*A)[k], (*B)[k]));
    //     if( (*A)[k] <  (*B)[k] ) { (*S)[k] = (double)( (double)1 - (double)((double)((*A)[k]) / (double)((*B)[k])) ); }
    //     else if ( (*A)[k] > (*B)[k] ) { (*S)[k] = (double)( (double)((double)((*B)[k]) / (double)((*A)[k])) - (double)1 ); }
    //     else { (*S)[k] = (double)0; }
    // }

    for(unsigned int k=0; k< S->size(); k++) {
        // (*S)[k] = (float)(( (float)(*BTMP)[k] - (*A)[k]) / (float)std::max((*A)[k], (*BTMP)[k]));
        if( (*A)[k] <  (*BTMP)[k] ) { (*S)[k] = (double)( (double)1 - (double)((double)((*A)[k]) / (double)((*BTMP)[k])) ); }
        else if ( (*A)[k] > (*BTMP)[k] ) {
            (*S)[k] = (double)( (double)((double)((*BTMP)[k]) / (double)((*A)[k])) - (double)1 );
        }
        else { (*S)[k] = (double)0; }
    }

    // cout << "THE A is " << endl;
    // for(int i=0; i<dataSize; i++) { cout << "GIA TO i " << i << " TIMI " << (*A)[i] << endl; }
    // cout << "THE B is " << endl;
    // for(int i=0; i<dataSize; i++) { cout << "GIA TO i " << i << " TIMI " << (*B)[i] << endl; }
    // cout << "THE S is " << endl;
    // for(int i=0; i<dataSize; i++) { cout << "GIA TO i " << i << " TIMI " << (*S)[i] << endl; }

    double SilTotal = 0.0;
    
    for(int i=0; i<dataSize; i++) { SilTotal += (double)(*S)[i]; }
    
    cout << "SilTotal is " << SilTotal << endl;
    cout << "Silhouette Total is " << ((double)SilTotal) / (double)(this->getClusNum()) << endl;

    // delete B;
    delete S;
    delete A;
    delete BTMP;
}

// return 2nh best distance
int KMeans::returnClusterIndexFORB(inputForm* newInp) {
    
    int minMan = manhattanDistance(newInp->image, ((*this->clusterAr)[0]->returncentroidVec()) );
    int ind = 0;
    int indLess = 0;

    for(unsigned int i=1; i<this->clusterAr->size(); i++) {
        
        int newM = manhattanDistance(newInp->image, ((*this->clusterAr)[i]->returncentroidVec()) );
        
        if(newM<minMan) {

            // change small
            indLess = ind;

            minMan = newM;
            ind = i;
        }
    }

    return indLess;
}

vector<int> *KMeans::computeB(dataInput* data) {
    
    // cout << "TOTAL IMAGES ARE " << data->getiMageVectorSize() << endl;

    vector<inputForm*> *centrAr = this->getKMeansCentroids(data);
    
    // cout << "IN THE END" << endl;
    // for(int i=0; i<this->getClusNum(); i++) {
    //     cout << (*centrAr)[i]->Id << endl;
    // }

    vector<vector<int>*> *Cluster_Ar_OF_CENTERS = new vector<vector<int>*>(this->getClusNum());
    
    for(int i=0; i<this->getClusNum(); i++) {
        
        vector<int>* tmp = (*centrAr)[i]->image;

        (*Cluster_Ar_OF_CENTERS)[i] = new vector<int>(tmp->size());

        for (unsigned int j = 0; j < tmp->size(); j++){
            (*(*Cluster_Ar_OF_CENTERS)[i])[j] = (*tmp)[j];
        }

    }
    
    vector<int> *B = new vector<int>(data->getiMageVectorSize()); // array of min dis from vec to centroids
    vector<int> *infoAr = new vector<int>(data->getiMageVectorSize());  // assignment for each vec
    for(int i=0; i<data->getiMageVectorSize(); i++) { (*infoAr)[i] = -1; } // none assigned

    int reps=0;
    int threshold = 10;
    bool StayedSame = false;
    while( reps<threshold && StayedSame==false) {

        // cout << "\nREP " << reps << " for data->getiMageVectorSize() " << data->getiMageVectorSize() << endl;
        
        StayedSame = true; // if even one changes then repeat
        
        for(int i=0; i<data->getiMageVectorSize(); i++) { // every input vector

            int ClusInd = this->returnClusterIndexFORB( data->getinputFormByNum(i) ); // where should be inserted


            if((*infoAr)[i] != ClusInd) { // not in that cluster already
            
                (*infoAr)[i] = ClusInd;

                StayedSame = false;

            }

        }

        vector<vector<int>*> *Cluster_Ar_OF_ASS_VECTORS = new vector<vector<int>*>(this->getClusNum());
        for(int i=0; i<this->getClusNum(); i++) {
            (*Cluster_Ar_OF_ASS_VECTORS)[i] = new vector<int>;
        }
        for(int i=0; i<data->getiMageVectorSize(); i++) {
            (*Cluster_Ar_OF_ASS_VECTORS)[ (*infoAr)[i] ]->push_back(i);
        }
        

        // for(int i=0; i<this->getClusNum(); i++) { cout << "   Cluster " << i << " has :" << (*Cluster_Ar_OF_ASS_VECTORS)[i]->size() << " assigned " << endl; }

        // change centroids
        if(StayedSame==false) {  // compute new centroids if didn t change
            for(int clus=0; clus<this->getClusNum(); clus++) {   // for every cluster

                int newCIndex = 0;
                
                for(unsigned int j=0; j<data->getinputFormByNum(0)->image->size(); j++) { // for every vector column
                    vector<int> *myV = new vector<int>(data->getImagesNUM());

                    for(unsigned int k=0; k < (*Cluster_Ar_OF_ASS_VECTORS)[clus]->size() ; k++) {
                        (*myV)[k] = (*(data->getinputFormByNum( (*(*Cluster_Ar_OF_ASS_VECTORS)[clus])[k] )->image))[ j ] ;   // vector of all column nums
                    }

                    int newCoord;
                    if((*Cluster_Ar_OF_ASS_VECTORS)[clus]->size()!=0) {
                        newCoord = getVecMedian(myV);
                    }
                    else {
                        newCoord = 0;
                    }

                    (*(*Cluster_Ar_OF_CENTERS)[clus])[newCIndex] = newCoord;

                    newCIndex++;

                    delete myV;

                }
            }
        }

        reps++;

        if( reps>=threshold || StayedSame==false) { // last to return
            
            int Aindex=0;
            for(int i=0; i<this->getClusNum(); i++) { // apo kathe cluster

                for(unsigned int j=0; j< (*Cluster_Ar_OF_ASS_VECTORS)[i]->size(); j++) { // gia kathe tou vector
                    
                    
                    int curInd = (*(*Cluster_Ar_OF_ASS_VECTORS)[i])[j];

                    (*B)[Aindex] = 0;

                    for(unsigned int k=0; k< (*Cluster_Ar_OF_ASS_VECTORS)[i]->size(); k++) {

                        int secInd = (*(*Cluster_Ar_OF_ASS_VECTORS)[i])[k];

                        if(secInd!=curInd) {
                            (*B)[Aindex] += manhattanDistance( (data->getinputFormByNum(secInd)->image), (data->getinputFormByNum(curInd)->image) );
                        }
                        
                    }

                    (*B)[Aindex] = (*B)[Aindex] / (*Cluster_Ar_OF_ASS_VECTORS)[i]->size();

                    Aindex++;
                }
            }
        
        }

        for(int i=0; i<this->getClusNum(); i++) {
            delete (*Cluster_Ar_OF_ASS_VECTORS)[i];
        }
        
        delete Cluster_Ar_OF_ASS_VECTORS;
    }

    cout << "Indexing " << endl;
    // for(unsigned int j=0; j<infoAr->size(); j++) { cout << "   Vec " << j << " in cluster " << (*infoAr)[j] << endl; }

    // for(int i=0; i<this->getClusNum(); i++) {
    //     cout << "CLUSTER " << i << endl;
    //     for(unsigned int j=0; j< (*this->clusterAr)[i]->returnindexesOfAssVecs()->size(); j++) { cout << "   " << (*(*this->clusterAr)[i]->returnindexesOfAssVecs())[j] << endl; }
    // }

    
    for(int i=0; i<this->getClusNum(); i++) {
        delete (*Cluster_Ar_OF_CENTERS)[i];
    }

    delete Cluster_Ar_OF_CENTERS;
    delete infoAr;
    delete centrAr;
    
    return B;
}