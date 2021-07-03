#include <iostream>
#include <cmath>
#include <cstdio>
#include <chrono>
#include <time.h>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <list>
using namespace std;
vector<bool> newcode;
map<char, vector<bool>> code;

class Node
{
public:
    char s;
    int key;
    Node *left, *right;
    Node();
    Node(char, int);
    Node(Node *, Node *);
    ~Node();
};
Node::Node()
{
    key = 0;
    s = 0; //' ';
    left = NULL;
    right = NULL;
}

Node::Node(char ss, int kkey)
{
    s = ss;
    key = kkey;
    left = NULL;
    right = NULL;
}
Node::~Node()
{
    delete[] left;
    delete[] right;
}
Node::Node(Node *lleft, Node *rright)
{
    key = lleft->key + rright->key;
    left = lleft;
    right = rright;
}
void tree_go(Node *head)
{

    if (head->left != NULL)
    {
        newcode.push_back(0);
        //cout << "heree" << endl;
        tree_go(head->left);
    }
    if (head->right != NULL)
    {
        newcode.push_back(1);
        tree_go(head->right);
    }
    if (head->left == NULL && head->right == NULL)
    {
        code[head->s] = newcode;
    }
    if (!newcode.empty())
    {
        newcode.pop_back();
    }
}

bool comp(const Node *n1, const Node *n2)
{
    if (n1->key < n2->key)
        return 1;
    else
        return 0;
}

bool Code_haffman(char *textway, char *codedway)
{

    ofstream codedtext(codedway, ios::in | ios::binary);
    if (codedtext.is_open() == 0)
    {
        cout << "can't open codedway" << endl;
        return 0;
    }
    ifstream text(textway, ios::out | ios::binary);
    if (text.is_open() == 0)
    {
        cout << "can't open textway" << endl;
        return 0;
    }

    map<char, int> table;
    map<char, int>::iterator it;
    char s;
    while (!text.eof())
    {
        s = text.get();
        table[s]++;
    }
    /*
    map<char, int>::iterator iter;
    for (iter = table.begin(); iter != table.end(); iter++)
    {
        cout << "char= " << iter->first << " int= " << iter->second << endl;
    }
    */

    list<Node *> llist;
    for (it = table.begin(); it != table.end(); it++)
    {
        Node *p = new Node(it->first, it->second);
        llist.push_back(p);
    }
    while (llist.size() != 1)
    {
        llist.sort(comp);
        Node *left_node = llist.front();
        llist.pop_front();
        Node *right_node = llist.front();
        llist.pop_front();
        Node *new_node = new Node(left_node, right_node);
        llist.push_back(new_node);
    }
    Node *root = llist.front();

    tree_go(root);

    int size = 0;
    for (it = table.begin(); it != table.end(); it++)
    {
        if (it->second != 0)
        {
            size++;
        }
    }

    codedtext.write((char *)(&size), sizeof(size));
    for (it = table.begin(); it != table.end(); it++)
    {
        codedtext.write((char *)(&it->first), sizeof(it->first));
        codedtext.write((char *)(&table[it->first]), sizeof(table[it->first]));
    }

    char curr;
    vector<bool> x;
    int count = 0;

    text.close();
    text = ifstream(textway, ios::out | ios::binary);

    while (!text.eof())
    {
        s = text.get();
        x = code[s];
        for (int i = 0; i < x.size(); i++)
        {
            curr = curr | x[i] << (7 - count);
            count++;
            if (count == 8)
            {
                count = 0;
                codedtext << curr;
                curr = 0;
            }
        }
    }

    text.close();
    codedtext.close();

    return 1;
}

bool Decode_haffman(char *codedway, char *decodedway)
{
    ifstream coded(codedway, ios::out | ios::binary);
    if (coded.is_open() == 0)
    {
        cout << "can't open codedway" << endl;
        return 0;
    }
    ofstream decoded(decodedway, ios::in | ios::binary);
    if (decoded.is_open() == 0)
    {
        cout << "can't open decodedway" << endl;
        return 0;
    }

    int n, sym_freq;
    char s;
    map<char, int> table;
    map<char, int>::iterator it;
    coded.read((char *)&n, sizeof(n));
    while (n > 0)
    {
        coded.read((char *)&s, sizeof(s));
        coded.read((char *)&sym_freq, sizeof(sym_freq));
        table[s] = sym_freq;
        n--;
    }

    list<Node *> llist;
    for (it = table.begin(); it != table.end(); it++)
    {
        Node *p = new Node(it->first, it->second);
        llist.push_back(p);
    }
    while (llist.size() != 1)
    {
        llist.sort(comp);
        Node *left_node = llist.front();
        llist.pop_front();
        Node *right_node = llist.front();
        llist.pop_front();
        Node *new_node = new Node(left_node, right_node);
        llist.push_back(new_node);
    }

    Node *root = llist.front();
    tree_go(root);

    char byte;
    int count = 0;
    Node *p = root;
    byte = coded.get();

    while (!coded.eof())
    {
        char bit = byte & (1 << (7 - count)); // проверяем что лежит в каждом бите если 1 то идем вправо если 0 то влево
        if (bit)
        {
            p = p->right;
        }
        else
        {
            p = p->left;
        }
        if (p->left == NULL && p->right == NULL)
        {
            decoded << p->s;
            p = root;
        }
        count++;
        if (count == 8)
        {
            count = 0;
            byte = coded.get();
        }
    }

    coded.close();
    decoded.close();

    return 1;
}
bool File_compare(char *textway, char *decoded_textway)
{
    ifstream text(textway, ios::out | ios::binary);
    if (text.is_open() == 0)
    {
        cout << "can't open textway" << endl;
        return 0;
    }
    ifstream decoded_text(decoded_textway, ios::out | ios::binary);
    if (decoded_text.is_open() == 0)
    {
        cout << "can't open decoded_textway" << endl;
        return 0;
    }
    char s, sym;
    while ((!text.eof()) && (!decoded_text.eof()))
    {
        s = text.get();
        sym = decoded_text.get();
        if (s != sym)
        {
            text.close();
            decoded_text.close();
            return 0;
        }
    }
    text.close();
    decoded_text.close();
    return 1;
}

int main()
{
    char textway[] = "C:\\Users\\12\\Desktop\\c_labs\\haffman\\haff_text.txt";
    char codedway[] = "C:\\Users\\12\\Desktop\\c_labs\\haffman\\coded_text.txt";
    char decodedway[] = "C:\\Users\\12\\Desktop\\c_labs\\haffman\\decoded_text.txt";
    cout << "start" << endl;
    bool k = Code_haffman(textway, codedway);
    bool m = Decode_haffman(codedway, decodedway);
    bool res = File_compare(textway, decodedway);
    if (res == 1)
        cout << "text and decoded text are equal" << endl;
    map<char, vector<bool>>::iterator it;
    for (it = code.begin(); it != code.end(); it++)
    {
        cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); i++)
        {
            cout << it->second[i];
        }
        cout << endl;
    }

    cout << "end" << endl;
    ifstream text(textway, ios::binary);
    if (text.is_open() == 0)
    {
        cout << "can't open codedway";
        return 0;
    }
    ifstream coded(codedway, ios::binary);
    if (coded.is_open() == 0)
    {
        cout << "can't open codedway";
        return 0;
    }
    float ntx = 0;
    float ncode = 0;
    char tmp;
    while (!text.eof())
    {
        tmp = text.get();
        ntx++;
    }
    while (!coded.eof())
    {
        tmp = coded.get();
        ncode++;
    }
    float compress = ncode / ntx;
    cout << "compression = " << compress << endl;
    text.close();
    coded.close();
    return 0;
    //k=Code_haffman

    return 0;
}