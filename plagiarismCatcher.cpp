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

    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir, files);

    for (unsigned int i = 0; i < files.size(); i++) {
       // cout << i << files[i] << endl;
    }
    cout << endl << endl;


    for (vector<string>::const_iterator it = files.begin(); it != files.end(); it++) {
        if ((*it) == "." || *it == "..") {
            files.erase(it);
        }
    }

    for (unsigned int i = 0; i < files.size(); i++) {
       // cout << i << " " << files[i] << endl;
    }

    FileChunks chunk1 = FileChunks(dir, files[0], 6);
    chunk1.outWordsVec();


    return 0;
}


