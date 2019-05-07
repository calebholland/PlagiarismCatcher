//
// Created by caleb on 4/28/19.
//

#ifndef CHEATERS_PLAGIARISMCATCHER_H
#define CHEATERS_PLAGIARISMCATCHER_H



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

//The hashing function. Rolling Polynomial type, but with a large (>26 characters) power multiplier
// and to avoid overflow, an extra % modulo powMod
unsigned long hashing(string hashChunk);

//Uses arithmetic to treat the 1D array as a 2D array, which saves space and time
unsigned long idx2D(int file1, int file2, const vector<string> &files);

//deletes the . , .. , and DS_Store file names from files vector
void removeCurrParentDirecs( vector <string> &files);

//uses the output class with overloaded relational operators to create a vector those Output objects
//and print them in order
void outPut(int * &twoDArray, int similarities, vector <string> &files);





#endif //CHEATERS_PLAGIARISMCATCHER_H