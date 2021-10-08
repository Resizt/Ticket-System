#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void SystemLoad		(int[], int[], int&, string[]); // Loading in the database of existing IDs
void SystemUpdate	(int[], int[], int&, string[]); // Update the database if a new user is added
void ReturningID	(int[], int[], int&, string[]); // Returning Users (This will just load up a list of ID's with the users name in order
void NewID			(int[], int[], int&, string[]); // Entering a new ID to the database
void ManualInput	(int[], int[], int&, string[]); // Manually inputing a user ID to see if they exist and loading up their recent reports	

void userSelect		(int[], int[], int&, string[], int&); // User that been selected

void returnError();	// Error message for invalid amount of entries in the database
void menu();		// Menu of what function you want to choose
void userMenu();	// The menu after selecting and confirming the user

int main() {
	int* idNum = new int [10]; int reportNum[10], entries = 0, choice = 0;
	string name[10];
	SystemLoad(idNum, reportNum, entries, name);

	while (choice != 4) {
		menu();
		cin >> choice;
		while (choice < 0 || choice > 4) {
			cout << "You're input is invalid; Please Try Again" << endl;
			cin >> choice;
		}

		switch (choice) {
		case 1:
			(entries == 0)	? returnError() : ReturningID(idNum, reportNum, entries, name);
			break;
		case 2:
			(entries >= 10)	? returnError() : NewID(idNum, reportNum, entries, name);
			break;
		case 3:
			(entries == 0)	? returnError() : ManualInput(idNum, reportNum, entries, name);
			break;
		case 4:
			exit;
		}
	}
}

void userSelect (int idNum[10], int reportNum[10], int& entries, string name[10], int& user) {
	string confirm;
	system("CLS");
	cout << "ID: " << idNum[user] << " " << "User: " << name[user] << endl;
	cout << "---------------------------------" << endl;
	cin >> confirm;


}

void NewID(int idNum[10], int reportNum[10], int& entries, string name[10]){
	ofstream NewEntry;
	system("CLS");
	cout << "---------------------------------" << endl;

	cout << "Enter the user ID #" << endl;
	cin >> idNum[entries];

		while (idNum[entries] == 0 || idNum[entries] > 999999 || idNum[entries] == 0) {
		cout << "This user ID is invalid; make sure the 6 digit ID is correct" << endl;
		cin >> idNum[entries];
		}

	cout << "---------------------------------" << endl;
	cout << "Enter the name assoicated with the ID" << endl;

	cin >> name[entries];

	cout << "---------------------------------" << endl;
	cout << "Added to database" << endl;
	SystemUpdate(idNum, reportNum, entries, name);
	NewEntry.open(name[entries] + ".txt");
	entries++;
}

void SystemLoad(int idNum[10], int reportNum[10], int& entries, string name[10]) {
	string info, Name, ID;
	ifstream SystemLoadin;
	SystemLoadin.open("Database.txt");

	while (getline(SystemLoadin, info)) {
		ID =	info.substr(0, info.find(" "));
		Name =	info.substr(info.find(" ") + 1);

		stringstream(ID)	>> idNum[entries];
		stringstream(Name)  >>	name[entries];
		entries++;
	}
}

void ManualInput(int idNum[10], int reportNum[10], int& entries, string name[10]) {
	int idInput, id = 0;
	char confirm;
	system("CLS");

	cout << "Manual Input" << endl;
	cout << "---------------------------------" << endl;
	cin >> idInput;

	while (idInput != idNum[id] && idInput != 0) {
		id++;
		if (id > entries) {
			system("CLS");
			cout << "This ID doesn't exist, please enter the correct ID (Enter 0 To quit)" << endl;
			cout << "---------------------------------" << endl;
			cin >> idInput;
			id = 0;
		}
	}

	if (idInput == idNum[id]) {
		cout << "Is this the right user?" << endl;
		cout << "---------------------------------" << endl;
		cout << idNum[id] << " " << name[id] << endl;
		cout << "Yes or No? (Y/N)" << endl;
		cin >> confirm;
		while (confirm != 'n' && confirm != 'N' && confirm != 'y' && confirm != 'Y') {
			cout << "Invalid input" << endl;
			cin >> confirm;
		}
		do {
			userSelect(idNum, reportNum, entries, name, id);
		} while (confirm == 'Y' || confirm == 'y');
		if (confirm == 'n' || confirm == 'N') {
			cout << "Reenter the ID please" << endl;
			cin >> idInput;
		}
	}
}

void SystemUpdate(int idNum[10], int reportNum[10], int& entries, string name[10]) {
	ofstream SystemUpdate;
	SystemUpdate.open("Database.txt");
	for (int user = 0; user <= entries; user++)
		SystemUpdate << idNum[user] << " " << name[user] << endl;
}


void ReturningID(int idNum[10], int reportNum[10], int& entries, string name[10]) {
	int input;
	system("CLS");
	cout << "Users" << endl;
	cout << "---------------------------------" << endl;
	for (int user = 0; user < entries; user++)
		cout << user+1 << ". " << idNum[user] << " " << name[user] << endl;
	cout << "---------------------------------" << endl;
	cout << "Select a user" << endl;
	cin >> input;
	input = input - 1;
	userSelect(idNum, reportNum, entries, name, input);
}

void returnError() {
	string confirm;
	cout << "There isn't any user in the database, please add a member a try again" << endl;
	cin >> confirm;
}

void menu() {
	system("CLS");
	cout << "Ticket System" << endl;
	cout << "---------------------------------" << endl;
	cout << "1. Returning ID" << endl;
	cout << "2. New ID" << endl;
	cout << "3. Manual Input" << endl;
	cout << "4. Exit" << endl;
	cout << "---------------------------------" << endl;
}

void userMenu() {
	system("CLS");
	cout << "---------------------------------" << endl;
	cout << "1. Returning ID" << endl;
	cout << "2. New ID" << endl;
	cout << "3. Manual Input" << endl;
	cout << "4. Exit" << endl;
	cout << "---------------------------------" << endl;
}