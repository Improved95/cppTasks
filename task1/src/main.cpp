#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
//    ifstream fileIn(argv[1]);
    ifstream fileIn("in.txt");
    if (!fileIn) return -1;



    fileIn.close();
    return 0;
}