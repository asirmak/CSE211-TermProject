// Ali Sencer Irmak
// 20200702096

#include <iostream>
#include "termproject.h"
using namespace std;

int main()
{
	LList database;
	database.loadFile("input.txt");
	database.printbyAge();
	database.printbyName();
	database.saveToFileByAge("age.txt");
	database.saveToFileByName("name.txt");
}
