#include <string>

/**
 * Node(url, frequency of url) will be used in TopK heap
*/
class Node{
public:
    std::string url;
    int num;
    Node(std::string s, int v): url(s), num(v) {}
    static bool cmp(const Node& a, const Node& b) {
        return a.num > b.num;
    }
};