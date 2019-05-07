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
    //Constructor that makes the object, calling all necessary functions to have the vector of chunks.
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
    //Replace the capital letters with lowercase
    void replaceCaps(string &currentWord);
    //remove all non-lowercase character ascii values after changing capitals to lowercase
    void rmNonAscii(string &currentWord);
    //This is the meat of the class. It makes the chunks and stores them in a vector, to be accessed and used by main program
    void makeChunks(int i, int n);




};


#endif //CHEATERS_FILECHUNKS_H
