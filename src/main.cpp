#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include "HashSplit.h"
#include "MultiHashSplit.h"
#include "GenerateURL.h"
#include "TopK.h"

using namespace std;

int main() {
    string gfname = "original/URL.txt";
    GenerateURL(gfname);
    cout << "original url file has been generated" << endl;
    
    int num_files = 200;
    string outpath = "HashSplitTemp/";
    HashSplit(gfname, outpath, num_files);
    cout << "HashSplit has finished" << endl;

    num_files = 100;
    outpath = "MultiHashSplitTemp/";
    MultiHashSplit(gfname, outpath, num_files);
    cout << "MultiHashSplit has finished" << endl;

    string ofname = "Top100.txt";
    TopK(outpath, ofname, 100, num_files);
    cout << "TopK has been generated" << endl;
}