//
// Created by caleb on 4/28/19.
//

#ifndef CHEATERS_FILECHUNKS_H
#define CHEATERS_FILECHUNKS_H

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class FileChunks {

public:

    FileChunks();
    FileChunks(string direcName, string fileName, int i, int n);

    void outWordsVec();
    void outChunksVec();
    string getFileName();
    int getFileIdx();
    const vector<string> &getChunksRef();






private:

    vector <string> chunks;
    vector <string> words;
    string currentChunk;
    string fileName;
    int fileIdx;
    //string fileString;
    void replaceCaps(string &currentWord);
    void rmNonAscii(string &currentWord);
    //int openFile(string fileName);
    //int makeFileString(string &fileString);
    void makeChunks(int i, int n);




};


#endif //CHEATERS_FILECHUNKS_H
