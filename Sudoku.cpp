#include "pch.h"
#include <iostream>

int main()
{
	string fileName;
	string input;
	bool cont = true;
	while (cont == true)
	{
		cout << "Enter a .txt file" << endl;
		cin >> fileName;
		puzzle p(fileName);
		cout << "Enter C to input another file\nEnter anything else to quit" << endl;
		cin >> input;
		if ((input != "C") && (input != "c"))
			cont = false;
	}
	cout << "Goodbye\n";
	return 0;
}