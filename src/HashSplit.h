#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

/**
 * Use one effective string hash function BKDRHash to split files for 200 or more
 * There still exists files whose size > 10M
*/


/**
 * Generate multiple hash files
 * @param infname the original url file, size = 1G
 * @param outpath the path where temporary hash files locate
 * @return -1 if any file errors occur, otherwise, 0.
*/
int HashSplit(string infname, string outpath, int& H) {
    hash<string> hf;
    ifstream fin(infname);
    if (!fin)
        return -1;
    ofstream fout[H];
    for (int i = 0; i < H; ++i)
        fout[i].open(outpath + "temp_" + to_string(i) + ".txt"); 
    string cur_url;
    while (getline(fin, cur_url)) {
        int h1 = hf(cur_url) % H;
        fout[h1] << cur_url << endl;
    }
    fin.close();
    for (int i = 0; i < H; ++i)
        fout[i].close();
    return 0;

}