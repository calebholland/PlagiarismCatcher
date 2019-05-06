//
// Created by caleb on 4/28/19.
//

#include "plagiarismCatcher.h"

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <math.h>
#include <cstring>
#include <algorithm>
#include <cstdlib>


#include "getFileNames.h"
#include "FileChunks.h"
#include "Output.h"

using namespace std;

unsigned long hashing(string hashChunk);

unsigned long idx2D(int file1, int file2, const vector<string> &files);

int main(int argc, char *argv[]) {
//int main() {
    //Change the below to use argv(s)

    /*
    const int n = 6;
    string dir = string("big_doc_set");
    const int similarities = 100;
*/



    char dir[300] = {0};
    strcpy(dir,argv[1]);
    const int n = atoi(argv[2]);
    const int similarities = atoi(argv[3]);



    vector<string> files = vector<string>();

    getdir(dir, files);

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
/*
    for (unsigned int i = 0; i < files.size(); i++) {
       // cout << i << " " << files[i] << endl;
    }
*/
//    cout<< files[0] <<endl;

    vector<FileChunks> allChunkedVec;

    struct hashNode{
        int fileIdx;
        hashNode* next;
    };

    const long hashArrSize = 1000000;
    hashNode* hashTable[hashArrSize] = {NULL};

    //for (vector<string>::const_iterator it = files.begin(); it != (files.end()); it++) {
    for(int i = 0; i < files.size(); i++){
        //allChunkedVec.push_back(FileChunks(dir, *it, i, n));
        allChunkedVec.push_back(FileChunks(dir, files[i], i, n));
    }

    //hashNode* temp = new hashNode{i, NULL};
    //hashTable[i] = temp;
    //int tempIdx = 0;
    //int fileIdx = 0;

    //allChunkedVec is a vector of FileChunks objects, each of which includes the index fileIdx
    //and the vector of chunks.

    for (vector<FileChunks>::iterator it = allChunkedVec.begin(); it != (allChunkedVec.end()); it++) {
        vector<string> chunks = (*it).getChunksRef();
        //fileIdx = (*it).getFileIdx();
        for(vector<string>::iterator it2 = chunks.begin(); it2 != (chunks.end()); it2++){
            hashNode* tempNode = new hashNode{(*it).getFileIdx(), NULL};
            //Replace the below with the hashing function (modify from notes, summing fct)
            //hashTable[tempIdx] = temp;
            //tempIdx++;
            unsigned long hashed = hashing(*it2);
            if(hashTable[hashed] == NULL) {
                hashTable[hashed] = tempNode;
            }
            else /*if(hashTable[hashed]->fileIdx != tempNode->fileIdx)*/{
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

    //const int fileArrSize = files.size() -1;

    //int twoDArray[25][25] = {0};

    //int ** twoDArray = new int*[files.size() -1];
    //for(int i = 0; i < files.size() -1; i++){
    //    twoDArray[i] = new int[files.size() -1];
    //}

    int * twoDArray = new int[(files.size())*(files.size())]{0};



    for(int i = 0; i < hashArrSize-1; i++){
        if(hashTable[i] != NULL){
            if(hashTable[i]->next != NULL){
                hashNode* lTempPtr = hashTable[i];
                hashNode* rTempPtr = hashTable[i]->next;
                while(rTempPtr != NULL){
                    //twoDArray[lTempPtr->fileIdx][rTempPtr->fileIdx] ++;
                    twoDArray[idx2D(lTempPtr->fileIdx, rTempPtr->fileIdx, files)] ++;
                    rTempPtr = rTempPtr->next;
                }
                while(lTempPtr->next->next != NULL){
                    lTempPtr = lTempPtr->next;
                    rTempPtr = lTempPtr->next;
                    while(rTempPtr != NULL){
                        //twoDArray[lTempPtr->fileIdx][rTempPtr->fileIdx] ++;
                        twoDArray[idx2D(lTempPtr->fileIdx, rTempPtr->fileIdx, files)] ++;
                        rTempPtr = rTempPtr->next;
                    }
                }
            }
        }
    }
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

    vector <Output> outVec;

    for(int i = 0; i < files.size() ; i++){
        for( int j = 0; j <files.size() ; j++){
            if(twoDArray[idx2D(i, j, files)]> similarities){
                outVec.push_back( Output( twoDArray[idx2D(i, j, files)], files[i], files[j]));
            }
        }
    }

    for (vector<Output>::iterator it = outVec.begin(); it != (outVec.end()); it++) {
        cout << (*it).getCollisions() << ": " << (*it).getFile1() << ", " << (*it).getFile2() << endl;
    }

    cout <<endl <<endl<<endl;

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



    return 0;
}




unsigned long idx2D(int file1, int file2, const vector<string> &files){
    unsigned long idx = ((files.size()) * file2) + file1;
    return idx;
}


unsigned long hashing(string hashChunk){
    //int keySize = hashChunk.size();
    unsigned long  modSm = 29873; //prime near roughly 1M /40 (one of the longest string lengths)
    unsigned long  mod = 954827; //prime close under 1M
    unsigned long  powMod = 4294967291; // Close prime number under max unsigned int;
    unsigned long  hash = 0;
    unsigned long  power = 1;
    for (int i = 0; i< hashChunk.size(); i++){
        hash += ((hashChunk[hashChunk.size() - 1 - i] * power) % mod);
        power = ((power * 29)% powMod);
    }
    hash = hash%mod;
    return hash;

}