//
// Created by caleb on 4/28/19.
//

#include "FileChunks.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


    FileChunks::FileChunks(){
        cout << "error: provide inputs " <<endl;
    }

    FileChunks::FileChunks(string direcName, string fileName, int n){

        string wd = "/" + direcName + "/" + fileName;
        string temp;
        ifstream currentFile;
        //currentFile.open(wd);
        currentFile.open("test.txt");
        while(currentFile) {
            currentFile >> temp;
            words.push_back(temp);
        }
        //currentFile >> temp;
        //currentFile >> temp;

        //cout << temp <<endl;
        //words.push_back(temp);


    }

    void FileChunks::outWordsVec() {
        for (vector<string>::const_iterator it = words.begin(); it != words.end(); it++) {
            cout << *it;
        }
    }
