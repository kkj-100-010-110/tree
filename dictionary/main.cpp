#include "dictionary.hpp"

int main()
{
	 Dictionary<int, int> t1;

    // t1.insert(10,10);
    // t1.insert(8, 8);
    // t1.insert(9, 9);
    // t1.insert(6, 6);
    // t1.insert(7, 7);
    // t1.insert(4, 4);
    // t1.insert(5, 5);
    // t1.insert(3, 3);
    t1.insert(8, 8);
    t1.insert(9, 9);
    t1.insert(7, 7);
    t1.insert(6, 6);
    t1.print();
    std::cout << std::endl;
    t1.remove(8);
    t1.print();

	return 0;
}
