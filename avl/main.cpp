#include "avl.hpp"
#include <string>

using namespace std;

int main()
{
    AVL<int, int> t;

    t.insert(100, 100);
    t.print(4);
    t.insert(50, 50);
    t.print(4);
    t.insert(10, 10);
    t.print(4);
    t.insert(80, 80);
    t.print(4);
    t.insert(70, 70);
    t.print(4);
    t.insert(60, 60);
    t.print(4);
    t.insert(90, 90);
    t.print(4);
    t.insert(30, 30);
    t.print(4);
    t.insert(20, 20);
    t.print(4);
    t.insert(40, 40);
    t.print(4);
    t.insert(5, 5);
    t.print(4);
    t.print(1);

    AVL<string, int> tt;
    string keys = string("SEARCHXMPL");
    tt.insert("S", int('S'));
    tt.print(4);
    tt.insert("E", int('E'));
    tt.print(4);
    tt.insert("A", int('A'));
    tt.print(4);
    tt.insert("R", int('R'));
    tt.print(4);
    tt.insert("C", int('C'));
    tt.print(4);
    tt.insert("H", int('H'));
    tt.print(4);
    tt.insert("X", int('X'));
    tt.print(4);
    tt.insert("M", int('M'));
    tt.print(4);
    tt.insert("P", int('P'));
    tt.print(4);
    tt.insert("L", int('L'));
    tt.print(4);
    tt.print(1);


    return 0;
}
