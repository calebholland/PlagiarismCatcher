//
// Created by caleb on 4/28/19.
//

#ifndef CHEATERS_GETFILENAMES_H
#define CHEATERS_GETFILENAMES_H

#endif //CHEATERS_GETFILENAMES_H

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//creates the files vector which will be used to make the chunks of each file and then print out the
// file name from the index at the end of the program
int getdir (string dir, vector<string> &files);
