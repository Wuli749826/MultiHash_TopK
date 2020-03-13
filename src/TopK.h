#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include "Node.h"
using namespace std;
/**
 * Keep a Min-root Heap of TopK frequency urls in memory
 * search all files splited by HashSplit or MultiHashSplit
 * compare and update TopK heap
 * @param inpath path of all hash files
 * @param ofname output filename of Topk urls
 * @param k Topk
 * @param cnt number of hash files
 * @return -1 if any file errors occur, otherwise, 0. 
*/

int TopK(string inpath, string ofname, int k, int cnt) {
    vector<Node> Top;
    for (int i = 0; i < k; ++i)
        Top.push_back(Node("", i));
    make_heap(Top.begin(), Top.end(), Node::cmp);

    //search all files splited by hash
    for (int i = 0; i < cnt; ++i) {
        ifstream fin(inpath + "temp_" + to_string(i) + ".txt");
        if (!fin) {
            continue;
        }
        string cur_url;
        unordered_map<string, int> h_map;
        while (getline(fin, cur_url)) {
            if (h_map.find(cur_url) == h_map.end()) 
                h_map[cur_url] = 1;
            else
                h_map[cur_url]++;
        }
        for (auto i = h_map.begin(); i != h_map.end(); ++i) {
            //if frequency > minimal of TopK
            if (i->second > Top.front().num) {
                pop_heap(Top.begin(), Top.end(), Node::cmp);
                Top.pop_back();
                Top.push_back(Node(i->first, i->second));
                push_heap(Top.begin(), Top.end(), Node::cmp);
            }
        }
    }
    vector<Node> temp;
    for (int i = 0; i < k; ++i) {
        temp.push_back(Top.front());
        pop_heap(Top.begin(), Top.end(), Node::cmp);
        Top.pop_back();
    }
    ofstream fout(ofname);
    for (int i = 0; i < k; ++i) {
        //fout << temp[k-1-i].url << " " << temp[k-1-i].num << endl;
        fout << temp[k-1-i].url << endl;
    }
    fout.close();
    return 0;
}