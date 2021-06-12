#include <iostream>
#include <cmath>
#include <cstdio>
#include <chrono>
#include <time.h>
#include <cstring>
#include <fstream>
using namespace std;
/*
int main()
{
    return 0;
}
*/

int main()
{
    ifstream text;
    text.open("C:\\Users\\12\\Desktop\\c_labs\\haffman\\text.txt");
    int ix = 0;
    int werew = 0;
    int text_size = 0;
    while (!text.eof())
        text_size++;
    char str[text_size];
    text >> str;

    for (int i = 0; i < text_size; i++)
        cout << str[i];

    /*while (!text.eof())
    {
        s = text.get();
        cout << s[ix];
        ix++;
    }*/
    //comcommit 1
    //while (s[ix] != ',')
    //git commit 20:02

    return 0;
}
