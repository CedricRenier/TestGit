//By Cedric Renier && Elimelec Rodriguez
#include <iostream>
#include <string>
#include "UserData.h"
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

//Function that displays the options for the user once the program starts.
void displayMenu();

//Function that asks for the new users account information.
void createAccount(vector<UserData> &);

//Function that asks for the users info to that they may log in.
void logIn(vector<UserData> &);

//Function that retrieves the users saved data in a file, runs every time the programs starts.
void readSavedData(vector<UserData> &);

//Function that runs everytime the program is to be terminated, it saves the users data in a text file.
void saveData(vector<UserData> &);

int main() {
	char choice; //Variable for the choice of the user. 
	vector<UserData> user; //Creates a vector of objects. 

	readSavedData(user); //Read data from text file. 

	do
	{
		displayMenu(); //Menu of choices.
		cout << "Enter your Choice: ";
		cin >> choice;

		while (toupper(choice < 'A' || toupper(choice) > 'C')) { //Validates the users choice.
			cout << "Please choose a valid option from the menu (A-C): ";
			cin >> choice;
			cin.ignore();
		}

		cout << endl;
		switch (choice) {
		case'a':
		case'A':
			//If option is A the user calls the createAccount function and sends the vector of objects called user.
			createAccount(user);
			cin.get();
			break;

		case'b':
		case'B':
			//If option is B the logIn function is called and sends the vector of objects.
			logIn(user);
			cin.get();
			break;
		}
		cout << endl;
		system("CLS");
	} while (toupper(choice) != 'C'); //If the user choice is C the program is terminated. 

	//Saves data before the program closes.
	saveData(user);

	system("pause");
	return 0;
}

void displayMenu() {
	cout << "A.Create new Account" << endl;
	cout << "B.Log In to an Existing Account" << endl;
	cout << "C.Exit" << endl;
}

void createAccount(vector<UserData> &user) {
	//Variables to hold the users entered data.
	string userRealName, userLastName, userName, userPassWord;

	cout << endl;
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, userRealName);

	cout << "Enter your last name: ";
	getline(cin, userLastName);
	//cin.ignore();

	cout << "Create your userName(can only contain letters, spaces and numbers): ";
	getline(cin, userName);
	//cin.ignore();

	cout << "Enter your PassWord: ";
	getline(cin, userPassWord);
	//cin.ignore();

	//Here we do what is called as an instanziation of the object, and use the overloaded constructor for
	//new users.
	UserData instanceObject(userRealName, userLastName, userName, userPassWord);

	//Here we used the .push_back member function of vectors that lets us expand the vector length with
	//new objects. 
	user.push_back(instanceObject);

	//Variable tol hold the size of the vector, will be used to print the id of each new member created.
	int size = user.size();

	cout << endl;
	cout << "Your Account has been created!" << endl;
	cout << "Your ID number is " << user[size - 1].getId() << endl;
	cout << "You can use this ID to log in later or your user name and password" << endl;

}

void logIn(vector<UserData> &user) {

	//Variable tol hold the size of the vector, will be used to print the id of each new member created.
	int size = user.size();

	char option;

	//Variable to hold the id entered by the user and compare it with the ids of each member in the vector.
	int display;

	cout << "Do you wish to Log In using the ID on your account ";
	cout << "or using your user name and password? (A.ID,B.Name and PassWord): ";
	cin >> option;
	cout << endl;

	while (toupper(option) < 'A' || toupper(option) > 'B') { //Validates the users input for the the login option.
		cout << "Please choose a valid option from the menu (A-B): ";
		cin >> option;
		cin.ignore();
	}

	//If user entered A we login using the id. 
	if (toupper(option) == 'A') {

		/*Here we implement a search algorithm, and if a match is found between
		 the id entered and an existing one in the vector we login succcesfully.*/

		int index = 0;
		int position = -1; //Will hold the position of the id inside the vector if a match is found.
		bool found = false; /*Boolean set tto false if this value changes a match has been
							 found and we conclude the search.*/

		cout << "Please enter your account ID ";
		//cin.ignore();
		cin >> display;

		/*There are two ways of finishing the search either a match has been found or we have reached
		 the end of the vector objects.*/
		while (index < size && !found) {
			if (user[index].getId() == display) {
				found = true;
				position = index;
			}
			index++;
		}

		if (position == -1) {
			cout << "ID not found!" << endl << endl;
		}
		else {
			cout << "Welcome " << user[position].getName() << " ";
			cout << user[position].getLastName() << "!" << endl;
			cout << "Your user name is: " << user[position].getUserName() << endl;
		}
	}
	//If the option is B we login using the username and password. 
	else if (toupper(option) == 'B') {

		int index = 0;
		int position = -1;
		bool found = false;
		string userName, passWord;

		cout << "Please enter your username: ";
		cin.ignore();
		getline(cin, userName);
		//cin.ignore();

		cout << "Enter your password: ";
		getline(cin, passWord);
		//cin.ignore();

		//passWord = encryptPassWord(passWord);

		while (index < size && !found) {
			if (user[index].getUserName() == userName) {
				found = true;
				position = index;
			}
			index++;
		}

		/*In this case we have 3 options: -Invalid username
										  -Invalid passWord
										  -Or succesfull login
		*/
		if (position == -1) { //If position stays in -1 there where no match
							  //between usernames.

			cout << "Invalid username!" << endl;
		}
		//If there is a match in userNames then we compare passwords with the 
		//position found, if they are the same we login
		else if (passWord == user[position].compPassWord()) {
			cout << "Welcome " << user[position].getName() << " ";
			cout << user[position].getLastName() << "!" << endl;
			cout << "Your user name is: " << user[position].getUserName() << endl;
		}
		else {
			cout << "Invalid password!" << endl;
		}

	}
	cin.get();
}


void readSavedData(vector<UserData> &user) {

	string name, lastName, userName, passWord;
	int pos = 0;

	ifstream input;
	input.open("UserInformation.txt");//Opens the file.
	//If file exits extract the data from it, else print that no file exits yet.
	if (!input.fail()) {
		while (input >> name >> lastName >> userName >> passWord) {

			//Instanziation of the object with the overloaded constructor for the data extracted from the file.
			UserData instanceObject(name, passWord);

			/*The overloaded constructor cannot set all member variables or it would not be possible
			to distinguish between which one to use, because of that we use the set function for the
			other 2 remaining data.*/
			instanceObject.setLastName(lastName);
			instanceObject.setUserName(userName);

			//Use the vector push_back member function to expand the vector with new members.
			user.push_back(instanceObject);
		}
	}
	else {
		cout << "No file exits yet." << endl;
	}
	input.close(); //Closes the file.
}

void saveData(vector<UserData> &user) {
	ofstream output;

	//Opens the file and with ios::trunc all previous data is removed, this is done so that we dont copy
	//data that alredy existed.
	output.open("UserInformation.txt", ios::trunc);

	//If for some reason the file couldnt be opened it terminates the program with a failure.
	if (!output.is_open()) {
		cout << "File not open" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		//For loop to go through every member in the vector and save it in the file.
		for (unsigned int x = 0; x < user.size(); x++) {
			output << user[x].getName() << " " << user[x].getLastName() << " ";
			output << user[x].getUserName() << " " << user[x].savePassWord() << endl;
		}
	}
	output.close();//Closes the file.
	cout << "Data saved" << endl;
}
