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

#include "getFileNames.h"
#include "FileChunks.h"

using namespace std;

int main() {

    //Change the below to use argv(s)
    string dir = string("sm_doc_set");
    int n = 6;

    vector<string> files = vector<string>();

    getdir(dir, files);

    for (vector<string>::const_iterator it = files.begin(); it != files.end(); it++) {
        if ((*it) == "." || *it == "..") {
            files.erase(it);
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
        int* next;
    };
    hashNode* hashTable[1000000];

    //for (vector<string>::const_iterator it = files.begin(); it != (files.end()); it++) {
    for(int i = 0; i < files.size(); i++){
        //allChunkedVec.push_back(FileChunks(dir, *it, i, n));
        allChunkedVec.push_back(FileChunks(dir, files[i], i, n));
    }

    //hashNode* temp = new hashNode{i, NULL};
    //hashTable[i] = temp;
    int tempIdx = 0;
    //int fileIdx = 0;
    for (vector<FileChunks>::iterator it = allChunkedVec.begin(); it != (allChunkedVec.end()); it++) {
        vector<string> chunks = (*it).getChunksRef();
        //fileIdx = (*it).getFileIdx();
        for(vector<string>::iterator it2 = chunks.begin(); it2 != (chunks.end()); it2++){
            hashNode* temp = new hashNode{(*it).getFileIdx(), NULL};
            //Replace the below with the hashing function (modify from notes, summing fct)
            hashTable[tempIdx] = temp;
            tempIdx++;
        }

        //cout << endl <<"-------------------------------------------------------------------------" <<endl<<endl;
    }

    for(int i = 0; i< 40000; i++){
        cout << hashTable[i]->fileIdx << endl;
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


