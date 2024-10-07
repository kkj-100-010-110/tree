#include "rb.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    RB<string, int> tt;
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
    tt.insert("E", int('A'));
    tt.print(4);
    tt.print(1);

    // RB<int, int> t;
    // t.insert(4, 4);
    // t.print(4);
    // t.insert(6, 6);
    // t.print(4);
    // t.insert(2, 2);
    // t.print(4);
    // t.insert(3, 3);
    // t.print(4);
    // t.insert(1, 1);
    // t.print(4);
    // t.insert(5, 5);
    // t.print(4);
    // t.insert(7, 7);
    // t.print(4);
    // t.print(1);
    // t.deleteMin();
    // t.print(4);
    // t.deleteMin();
    // t.print(4);
    // t.print(1);

    RB<char, char> ttt;
    // CESARHMHPFNT
    ttt.insert('C', 'C');
    ttt.insert('E', 'E');
    ttt.insert('S', 'S');
    ttt.insert('A', 'A');
    ttt.insert('R', 'R');
    ttt.insert('H', 'H');
    ttt.insert('M', 'M');
    ttt.insert('P', 'P');
    ttt.insert('F', 'F');
    ttt.insert('N', 'N');
    ttt.insert('T', 'T');
    ttt.print(4);
    ttt.print(1);
    ttt.remove('R');
    ttt.print(4);
    ttt.print(1);
    ttt.remove('E');
    ttt.print(4);
    ttt.print(1);
    ttt.remove('M');
    ttt.print(4);
    ttt.print(1);
    ttt.remove('N');
    ttt.print(4);
    ttt.print(1);
    ttt.remove('S');
    ttt.print(4);
    ttt.print(1);
    ttt.remove('P');
    ttt.print(4);
    ttt.print(1);
    ttt.clear();
    ttt.print(4);
    ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);
    // ttt.deleteMax();
    // ttt.print(4);
    // ttt.print(1);

    return 0;
}