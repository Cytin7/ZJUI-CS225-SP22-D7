#include "../head.h"

string genProfRome(const int& prof)
{
	switch (prof)
	{
	case 1:
		return "I";
	case 2:
		return "II";
	case 3:
		return "III";
	case 4:
		return "IV";
	case 5:
		return "V";
	case 6:
		return "VI";
	case 7:
		return "VII";
	case 8:
		return "VIII";
	default:
		return "Error, profession code out of range";
	}
}

// Print functions for main menu
int PrintMainPage() {
	int key;
	cout << "Input the key number to choose the operation:" << endl;
	cout << "[0]\tClose the program" << endl;
	cout << "[1]\tSet register information" << endl;
	cout << "[2]\tSet hospital information" << endl;
	cout << "[]\tWithdraw Record using ID" << endl;
	cout << "[]\tModify Record information" << endl;
	cout << "[]\tRead file for the registry" << endl;
	cout << "Please input the key value here:" << endl << ">>>";
	cin >> key;
	cout << endl;
	return key;
}

// print function for registry sub-menu
int PrintRegistrySetupPage()
{
	int key;
	cout << "Input the key number to choose the operation of registry setup:" << endl;
	cout << "[0]\tReturn to the main page" << endl;
	cout << "[1]\tAdd one new registry" << endl;
	cout << "[2]\tSet maximim registery patient for simulation" << endl;
	cout << "[3]\tSet minimum registry patient for simulation" << endl;
	cout << "Please input the key value here:" << endl << ">>>";
	cin >> key;
	cout << endl;
	return key;
}

// print function for hospital sub-menu
int PrintHospitalSetupPage()
{
	int key;
	cout << "Input the key number to choose the operation of hospital setup:" << endl;
	cout << "[0]\tReturn to the main page" << endl;
	cout << "[1]\tAdd one new hospital" << endl;
	cout << "[2]\tSet capacity of the hospital" << endl;
	cout << "Please input the key value here:" << endl << ">>>";
	cin >> key;
	cout << endl;
	return key;
}
