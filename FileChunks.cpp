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

    FileChunks::FileChunks(string direcName, string _fileName, int i, int n){

        string wd = direcName + "/" + _fileName;
        string temp;
        ifstream currentFile;
        currentFile.open(wd);

        while(currentFile) {
            currentFile >> temp;
            replaceCaps(temp);
            rmNonAscii(temp);
            if(!temp.empty()){
                words.push_back(temp);
            }
        }
        makeChunks(i,n);
        fileName = _fileName;
        fileIdx = i;

    }

    string FileChunks::getFileName() {
        return fileName;
    }

    int FileChunks::getFileIdx() {
        return fileIdx;
    }

    const vector<string>& FileChunks::getChunksRef() {
        return chunks;
    }

    void FileChunks::makeChunks(int i, int n) {
        for (vector<string>::const_iterator it = words.begin(); it != (words.end() -n); it++) {
            for(int j = 0; j<n; j++){
                currentChunk += (*(it + j));
            }
            chunks.push_back(currentChunk);
            currentChunk = "";
        }
    }

    void FileChunks::rmNonAscii(string &currentWord) {
        string::size_type it = 0;
        while(it < currentWord.length()){
            if( (currentWord[it] < 97) || (currentWord[it] > 122) ){
                currentWord.erase(it, 1);
            }
            else {
                it++;
            }
        }
    }

    void FileChunks::replaceCaps(string &currentWord) {
        locale local;
        for(string::size_type it = 0; it < currentWord.length(); it++){
            currentWord[it] = tolower(currentWord[it], local);
        }
    }


    void FileChunks::outWordsVec() {
        for (vector<string>::const_iterator it = words.begin(); it != words.end()-1; it++) {
            cout << *it << endl;
        }
    }

    void FileChunks::outChunksVec() {
        for (vector<string>::const_iterator it = chunks.begin(); it != chunks.end(); it++) {
           cout << fileIdx << " : " << *it << endl;
        }
    }


