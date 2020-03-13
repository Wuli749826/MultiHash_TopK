#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

/**
 * Generate original url file, size = 1G
 * repeat url files from bilibili, acfun, iqiyi, netease, tencent, tudou and youku
 * 100 url files from bilibili will be repeated most
 * therefore, the Top100 url will all start with www.bilibili.com
 * @param gfname filename of 1G url file
 * @return -1 if any file errors occur, otherwise, 0.
*/
int GenerateURL(string gfname) {
    ofstream fout;
    fout.open(gfname);
    if (!fout) {
        return -1;
    }
	string origi_filename[] = {"original/sitemap_bilibili_100.txt", "original/sitemap_acfun_583.txt", 
    "original/sitemap_iqiyi_180.txt", "original/sitemap_netease_315.txt", "original/sitemap_tecent_296.txt",
    "original/sitemap_tudou_152.txt", "original/sitemap_youku_158.txt"};
    //1784 urls
    //top100 should from bilibili, repeat by (200-250)*100 times
    //other should repeat by (100-150)*100 times
    srand((int)time(0));
    int init = 200;
    for (int i = 0; i < 7; ++i) {
        ifstream fin;
        fin.open(origi_filename[i]);
        if (!fin) {
            return -1;
        }
        string cur_url;
        while (getline(fin, cur_url)) {
            int t = init + rand()%51;
            //modify here, if t*=100, each file 10M, total = 10M*100=1G
            //if t *= 1, each file 100K, total = 100K*100=10M
            t *= 100;
            while (t--) {
                fout <<  cur_url << endl;
            }
        }
        init = 100;
        fin.close();
    }
    fout.close();
    return 0;
}