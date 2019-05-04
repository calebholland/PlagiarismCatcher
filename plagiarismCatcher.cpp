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

#include "getFileNames.h"
#include "FileChunks.h"

using namespace std;

unsigned long hashing(string hashChunk);

unsigned long idx2D(int file1, int file2, const vector<string> &files);

int main() {

    //Change the below to use argv(s)
    int n = 6;
    string dir = string("user_doc_set");


    vector<string> files = vector<string>();

    getdir(dir, files);

    for (vector<string>::const_iterator it = files.begin(); it != files.end(); it++) {
        if ((*it) == "." || *it == "..") {
            files.erase(it);
            if ((*it) == "." || *it == "..") {
                files.erase(it);
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




    for(int i = 0; i < files.size() -1; i++){
        for( int j = 0; j <files.size() -1; j++){
            if(twoDArray[idx2D(i, j, files)]>4){
                cout << twoDArray[idx2D(i, j, files)] << ": " << files[i] << ", " << files[j] << endl;
            }
        }
    }













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