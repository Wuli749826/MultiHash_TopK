#include "gtest/gtest.h"
#include "MultiHashSplit.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


//cannot lose each url
TEST(MultiHashSplitTest, NotLostTest) {
    hash<string> hf;
    ofstream fout("cur_file.txt");
    for (int i = 0; i < 300; ++i)
        fout << to_string(i) << endl;
    fout.close();
    //////////new directory, cant be create!!!!!!!!!!
    string outpath = "";
    int H = 20;
    int res = MultiHashSplit("cur_file.txt", outpath, H);
    EXPECT_EQ(res, 0);
    vector<string> url_arr;
    for (int i = 0; i < H; ++i) {
        fstream fin(outpath+ "temp_" + to_string(i) + ".txt");
        string cur_url;
        while (getline(fin, cur_url)) {
            url_arr.push_back(cur_url);
        }
        fin.close();
    }
    EXPECT_EQ(url_arr.size(), 300);
    unordered_map<string, bool> url_count;
    for (auto i : url_arr) {
        EXPECT_EQ(url_count.find(i), url_count.end());
        url_count[i] = true;
    }
}

//the same url cannot be hashed into two or more files
TEST(MultiHashSplitTest, NotRepeatTest) {
    hash<string> hf;
    ofstream fout("cur_file.txt");
    for (int i = 0; i < 300; ++i)
        for (int j = 0; j < 20; ++j)
            fout << to_string(i) << endl;
    fout.close();
    //////////new directory, cant be create!!!!!!!!!!
    string outpath = "";
    int H = 20;
    int res = MultiHashSplit("cur_file.txt", outpath, H);
    EXPECT_EQ(res, 0);
    unordered_map<string, int> url_count;
    for (int i = 0; i < H; ++i) {
        vector<string> url_arr;
        fstream fin(outpath+ "temp_" + to_string(i) + ".txt");
        string cur_url;
        while (getline(fin, cur_url)) {
            url_arr.push_back(cur_url);
        }
        fin.close();
        //for each url in this turn, it shouldn't have appeared before
        for (auto s : url_arr) {
            if (url_count.find(s) != url_count.end()) {
                EXPECT_EQ(url_count[s], i);
            }
            url_count[s] = i;
        }
    }
}