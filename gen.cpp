#include <fstream>
#include <iostream>
#include "config.h"

using namespace std;

int main(){
    ofstream file;
    file.open("starter");
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE-1; j++){
            file << "0,";
        }
        file << "0";
        file << "\n";
    }
    file.close();
    return 0;
}
