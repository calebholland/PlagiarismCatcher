//
// Created by caleb on 5/6/19.
//

#ifndef CHEATERS_OUTPUT_H
#define CHEATERS_OUTPUT_H
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class Output {

public:

    Output();
    Output(int _collisions, string _file1, string _file2);
    bool operator >(Output const &rhs);
    bool operator <(Output const &rhs);
    bool operator ==(Output const &rhs);
    int getCollisions();
    string getFile1();
    string getFile2();





private:

    int collisions;
    string file1;
    string file2;

};


#endif //CHEATERS_OUTPUT_H
