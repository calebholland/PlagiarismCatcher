//
// Created by caleb on 4/28/19.
//

#include "plagiarismCatcher.h"



using namespace std;


int main(int argc, char *argv[]) {


// Take command line arguments to run program
    char dir[300] = {0};
    strcpy(dir,argv[1]);
    const int n = atoi(argv[2]);
    const int similarities = atoi(argv[3]);


    vector<string> files = vector<string>();

    getdir(dir, files);

    removeCurrParentDirecs(files);

    vector<FileChunks> allChunkedVec;

    struct hashNode{
        int fileIdx;
        hashNode* next;
    };

    const long hashArrSize = 1000000;
    hashNode* hashTable[hashArrSize] = {NULL};

    for(int i = 0; i < files.size(); i++){
        allChunkedVec.push_back(FileChunks(dir, files[i], i, n));
    }


    //allChunkedVec is a vector of FileChunks objects, each of which includes the index fileIdx
    //and the vector of chunks. The below fills in the hash table by hashing each chunk in each
    //object (each chunked file). After calling hash function, if that space in the table is empty
    //or not from the same file, it adds a node at the beginning of the list with that file index.
    //After completion of the outer loop, every chunk is hashed into the hash table.

    for (vector<FileChunks>::iterator it = allChunkedVec.begin(); it != (allChunkedVec.end()); it++) {
        vector<string> chunks = (*it).getChunksRef();
        for(vector<string>::iterator it2 = chunks.begin(); it2 != (chunks.end()); it2++){
            hashNode* tempNode = new hashNode{(*it).getFileIdx(), NULL};

            unsigned long hashed = hashing(*it2);
            if(hashTable[hashed] == NULL) {
                hashTable[hashed] = tempNode;
            }
            else{
                int checkSame1 = hashTable[hashed]->fileIdx;
                int checkSame2 = tempNode->fileIdx;
                if(checkSame1 != checkSame2) {
                    hashNode *hashTemp = hashTable[hashed];
                    hashTable[hashed] = tempNode;
                    tempNode->next = hashTemp;
                }
            }
        }
    }


    //The twoDArray below is actually just a dynamically allocated single dimensional array which calculates
    //the index with a helper function. This saves memory and time (and segfaults from 2D arrays that are too large as
    //would be the case on the large file sets). It only bothers adding the collisions from the hash table if there are
    //more than one entry, because a single entry is not a collision and therefore not useful.
    //After adding all the collisions to the array, it deletes each node to prevent mem leaks.

    int * twoDArray = new int[(files.size())*(files.size())]{0};

    for(int i = 0; i < hashArrSize-1; i++){
        if(hashTable[i] != NULL){
            if(hashTable[i]->next != NULL){
                hashNode* lTempPtr = hashTable[i];
                hashNode* rTempPtr = hashTable[i]->next;
                while(rTempPtr != NULL){
                    twoDArray[idx2D(lTempPtr->fileIdx, rTempPtr->fileIdx, files)] ++;
                    rTempPtr = rTempPtr->next;
                }
                while(lTempPtr->next->next != NULL){
                    lTempPtr = lTempPtr->next;
                    rTempPtr = lTempPtr->next;
                    while(rTempPtr != NULL){
                        twoDArray[idx2D(lTempPtr->fileIdx, rTempPtr->fileIdx, files)] ++;
                        rTempPtr = rTempPtr->next;
                    }
                }
            }
        }
        hashNode* lTempPtr = hashTable[i];
        hashNode* rTempPtr = hashTable[i];
        while(lTempPtr != NULL){
            rTempPtr = lTempPtr;
            lTempPtr = rTempPtr->next;
            delete rTempPtr;
        }
    }


    outPut(twoDArray, similarities, files);


    delete[] twoDArray;


    return 0;
}

void outPut(int * &twoDArray, int similarities, vector <string> &files){
    vector <Output> outVec;

    for(int i = 0; i < files.size() ; i++){
        for( int j = 0; j <files.size() ; j++){
            if(twoDArray[idx2D(i, j, files)]> similarities){
                outVec.push_back( Output( twoDArray[idx2D(i, j, files)], files[i], files[j]));
            }
        }
    }


    while(outVec.size() != 0) {
        Output largest = outVec[0];
        vector<Output>::iterator iter = outVec.begin();
        for (vector<Output>::iterator it = outVec.begin(); it != (outVec.end()); it++) {
            if ((*it) > largest) {
                largest = (*it);
                iter = it;
            }
        }
        cout << (*iter).getCollisions() << ": " << (*iter).getFile1() << ", " << (*iter).getFile2() << endl;
        outVec.erase(iter);
    }
}


void removeCurrParentDirecs( vector <string> &files){
    for (vector<string>::iterator it = files.begin(); it != files.end(); it++) {
        if ((*it) == "." || (*it) == ".." || (*it) == ".DS_Store") {
            files.erase(it);
            if ((*it) == "." || (*it) == ".." || (*it) == ".DS_Store") {
                files.erase(it);
                if ((*it) == "." || (*it) == ".." || (*it) == ".DS_Store") {
                    files.erase(it);
                }
            }
        }
    }
}

unsigned long idx2D(int file1, int file2, const vector<string> &files){
    unsigned long idx = ((files.size()) * file2) + file1;
    return idx;
}


unsigned long hashing(string hashChunk){
    //int keySize = hashChunk.size();
    const unsigned long  modSm = 29873; //prime near roughly 1M /40 (one of the longest string lengths)
    const unsigned long  mod = 954827; //prime close under 1M
    const unsigned long  powMod = 4294967291; // Close prime number under max unsigned int;
    unsigned long  hash = 0;
    unsigned long  power = 1;
    for (int i = 0; i< hashChunk.size(); i++){
        hash += ((hashChunk[hashChunk.size() - 1 - i] * power) % mod);
        power = ((power * 29)% powMod);
    }
    hash = hash%mod;
    return hash;

}






/*
    for (vector<Output>::iterator it = outVec.begin(); it != (outVec.end()); it++) {
        cout << (*it).getCollisions() << ": " << (*it).getFile1() << ", " << (*it).getFile2() << endl;
    }

    cout <<endl <<endl<<endl;
    */

/*
for(int i = 0; i < (files.size())*(files.size()); i++){
    cout << twoDArray[i] << endl;
}
int sizex= files.size();

*/




/*
    for(int i = 0; i < files.size() ; i++){
        for( int j = 0; j <files.size() ; j++){
            if(twoDArray[idx2D(i, j, files)]> similarities){
                cout << twoDArray[idx2D(i, j, files)] << ": " << files[i] << ", " << files[j] << endl;
            }
        }
    }

*/


//hashTable[tempIdx] = temp;
//tempIdx++;

//const int fileArrSize = files.size() -1;

//int twoDArray[25][25] = {0};

//int ** twoDArray = new int*[files.size() -1];
//for(int i = 0; i < files.size() -1; i++){
//    twoDArray[i] = new int[files.size() -1];
//}


//hashNode* temp = new hashNode{i, NULL};
//hashTable[i] = temp;
//int tempIdx = 0;
//int fileIdx = 0;



/*
    for (unsigned int i = 0; i < files.size(); i++) {
       // cout << i << " " << files[i] << endl;
    }
*/
//    cout<< files[0] <<endl;



/*

    outVec.push_back(Output(23, "ajslkfdj", "jkljaklj"));
    outVec.push_back(Output(3, "ajslkfdj", "jkljaklj"));
    outVec.push_back(Output(40, "ajslkfdj", "jkljaklj"));

    for(int i = 0; i< 3; i++){
        cout << outVec[i].getCollisions() << ": " << outVec[i].getFile1() << ", " << outVec[i].getFile2() << endl;
    }

    */


//sort(outVec, outVec.size()/*, greater<Output>()*/);









/*
for (vector<FileChunks>::iterator it = allChunkedVec.begin(); it != (allChunkedVec.end()); it++) {
    (*it).outChunksVec();
    cout << endl <<"-------------------------------------------------------------------------" <<endl<<endl;
}
*/
//    FileChunks chunk1 = FileChunks(dir, files[0], n);
//    chunk1.outWordsVec();
//    cout << endl <<endl;
//    chunk1.outChunksVec();

//    vector<string> chunk2 = chunk1.getChunksRef();
//    chunk2.push_back("4523789");

//for (vector<string>::const_iterator it = files.begin(); it != (files.end()); it++) {
//allChunkedVec.push_back(FileChunks(dir, *it, i, n));

//else /*if(hashTable[hashed]->fileIdx != tempNode->fileIdx)*/{

//twoDArray[lTempPtr->fileIdx][rTempPtr->fileIdx] ++;

//void makeHashTable(vector<FileChunks> &allChunkedVec, , )

//void make2DArray(int * &twoDArray, )


//Change the below to use argv(s)
/*
const int n = 6;
string dir = string("big_doc_set");
const int similarities = 200;
 */