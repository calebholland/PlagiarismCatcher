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


int getdir (string dir, vector<string> &files);
