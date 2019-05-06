//
// Created by caleb on 5/6/19.
//

#include "Output.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

    Output::Output() {
        collisions = 0;
        file1 = "";
        file2 = "";
    }

    Output::Output(int _collisions, string _file1, string _file2) {
        collisions = _collisions;
        file1 = _file1;
        file2 = _file2;
    }


    bool Output::operator >(Output const &rhs){
        if(collisions > rhs.collisions) {
            return true;
        }
        else{
            return false;
        }
    }
    bool Output::operator <(Output const &rhs){
        if(collisions < rhs.collisions) {
            return true;
        }
        else{
            return false;
        }
    }
    bool Output::operator ==(Output const &rhs){
        if(collisions == rhs.collisions) {
            return true;
        }
        else{
            return false;
        }
    }

    int Output::getCollisions(){
        return collisions;
    }
    string Output::getFile1(){
        return file1;
    }
    string Output::getFile2(){
        return file2;
    }