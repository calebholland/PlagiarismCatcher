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
    //std::cout << "Hello, World!" << std::endl;

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
    for (vector<string>::const_iterator it = files.begin(); it != (files.end()); it++) {
        allChunkedVec.push_back(FileChunks(dir, *it, n));
    }

    for (vector<FileChunks>::iterator it = allChunkedVec.begin(); it != (allChunkedVec.end()); it++) {
        (*it).outChunksVec();
        cout << endl <<"-------------------------------------------------------------------------" <<endl<<endl;
    }

//    FileChunks chunk1 = FileChunks(dir, files[0], n);
//    chunk1.outWordsVec();
//    cout << endl <<endl;
//    chunk1.outChunksVec();

//    vector<string> chunk2 = chunk1.getChunksRef();
//    chunk2.push_back("4523789");



    return 0;
}


