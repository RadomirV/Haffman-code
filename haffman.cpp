#include <iostream>
#include <cmath>
#include <cstdio>
#include <chrono>
#include <time.h>
#include <cstring>
#include <fstream>
using namespace std;

class Node
{
public:
    char s;             ///symbol
    int key;            /// amount symbols
    Node *left, *right; ///pointers on left_ and right_

    Node();
    Node(char, int);
    Node(Node *, Node *);
    ~Node();
};

void tree_go(Node *);

bool comp(const Node *c1, const Node *c2)
{
    if (c1->key < c2->key)
        return 1;
    else
        return 0;
}

int main()
{

    return 0;
}

/*
int main()
{

    ifstream text;
    text.open("C:\\Users\\12\\Desktop\\c_labs\\haffman\\text.txt");
    int ix = 0;
    int werew = 0;
    int text_size = 0;
    while (!text.eof())
    {
        text_size++;
        text.get();
    }

    unsigned char str[text_size];
    for (int i = 0; i < text_size; i++)
        str[i] = 0;
    text >> str;

    for (int i = 0; i < text_size; i++)
        cout << str[i];

    /*while (!text.eof())
    {
        s = text.get();
        cout << s[ix];
        ix++;
    }
    //comcommit 1
    //while (s[ix] != ',')
    //git commit 20:02

    return 0;
}
*/
