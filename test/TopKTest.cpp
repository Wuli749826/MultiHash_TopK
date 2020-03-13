#include "gtest/gtest.h"
#include "TopK.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//Test Top100 from one file
TEST(TopKTest, SingleFileTest) {
    ofstream fout("temp_0.txt");
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= i; ++j)
            fout << to_string(i) << endl;
    fout.close();
    string inpath = "";
    string ofname = "Top100.txt";
    int res = TopK(inpath, ofname, 100, 1);
    EXPECT_EQ(res, 0);
    ifstream fin("Top100.txt");
    string cur_url;
    int max_v = 200;
    while (getline(fin, cur_url)) {
        EXPECT_EQ(to_string(max_v), cur_url);
        max_v--;
    }
    EXPECT_EQ(max_v, 100);
}


//Test Top100 from 4 files
TEST(TopKTest, MultiFileTest) {
    ofstream fout("temp_0.txt");
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= 10; ++j)
            fout << to_string(i) << endl;
    fout.close();
    fout.open("temp_1.txt");
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= 20; ++j)
            fout << to_string(i) << endl;
    fout.close();
    fout.open("temp_2.txt");
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= 30; ++j)
            fout << to_string(i) << endl;
    fout.close();
    fout.open("temp_3.txt");
    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= i; ++j)
            fout << to_string(i) << endl;
    fout.close();
    string inpath = "";
    string ofname = "Top100.txt";
    int res = TopK(inpath, ofname, 100, 4);
    EXPECT_EQ(res, 0);
    ifstream fin("Top100.txt");
    string cur_url;
    int max_v = 200;
    while (getline(fin, cur_url)) {
        EXPECT_EQ(to_string(max_v), cur_url);
        max_v--;
    }
    EXPECT_EQ(max_v, 100);
}