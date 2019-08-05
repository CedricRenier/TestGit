//By Cedric Renier && Elimelec Rodriguez
#include "UserData.h"
#include <iostream>
#include <string>
using namespace std;

//Definition of the static member variable outside the class, used to keep a count 
//on the number of objects (users) created.
int UserData::objectCount = 0;


//Default constructor that sets every attribute to 0 or a null string
UserData::UserData() {
	objectCount++;
	name = "";
	lastName = "";
	userName = "";
	id = 0;
	passWord = "";
}

/*Construtor for the name and password extracted from the file, this was necessary since
the password extracted from the file and that of a new user were not homogeneous.*/
UserData::UserData(string name, string passW) {
	objectCount++;
	setName(name);
	passWord = passW; //Here we set directly the password extracted from the file to
					  //the attribute because is alredy encrypted. 
}

/*Overloaded constructor called when a new user is created, this constructor
 at the same time calls the setter function for each attribute*/
UserData::UserData(string userRealName, string userLastName,
	string userNm, string userPassWord) {
	objectCount++;
	setName(userRealName);
	setLastName(userLastName);
	setUserName(userNm);
	setPassWord(userPassWord);
}

//Function that encrypts and decrypts the users password with an XOR encryption
string UserData::encryptDecrypt(string passW) {
	string key = "QWERTYUIOPASDFGHJKLZXCVBNM";
	string temp = key;

	/*while loop, used in case the key is shorter than the password entered by the user
	 in which case the key is expanded using the temp variable*/
	while (key.length() < passW.length()) {
		key += temp;
	}
	//For every iteration the character in that particular location is changed with the algorithm below.
	for (unsigned int i = 0; i < passW.length(); i++) {
		passW[i] = passW[i]^(int(key[i]) + i) % 255;
	}

	return passW;
}

/*Sets the ids of users starting at 1000 and going to infinity, this function used
the objectCount variable to assigns the values.*/
void UserData::setId() {
	id = 1000 + (objectCount - 1);
}

//Sets the users name, it validates the users entry to just letters and spaces.
void UserData::setName(string userRealName) {
	//Inside this function for every new user the setId function is called.
	setId();
	unsigned int x;

	//Validation part of the member function.
	for (x = 0; x < userRealName.length(); x++) {
		while (!(isalpha(userRealName[x]) || isspace(userRealName[x]))) {
			cin.ignore();
			cout << "Please enter a valid name: ";
			getline(cin, userRealName);
			x = 0; //x is set to 0 so that it starts from the beginning to check
				   //if the user entry is correct. 
		}
	}
	name = userRealName;
}

//Sets the users last name and validates the users entry to just letters and spaces/
void UserData::setLastName(string lastN) {

	for (unsigned int x = 0; x < lastN.length(); x++) {
		while (!(isalpha(lastN[x]) || isspace(lastN[x]))) {
			cin.ignore();
			cout << "Please enter a valid last name: ";
			getline(cin, lastN);
			x = 0;
		}
	}
	lastName = lastN;
}


//Sets the username and validates it, so that it containts letters, spaces and numbers.
void UserData::setUserName(string userNm) {

	for (unsigned int x = 0; x < userNm.length(); x++) {
		while (!(isalpha(userNm[x]) || isspace(userNm[x]) || isdigit(userNm[x]))) {
			cin.ignore();
			cout << "Please enter a valid user name: ";
			getline(cin, userNm);
			x = 0;
		}
	}
	userName = userNm;
}

/*Function that has a call to the encryption/decription function with the password entered by
 the user, after this password is encrypted it is assigned to the member variable passWord.*/
void UserData::setPassWord(string passW) {
	passWord = encryptDecrypt(passW);
}

//Function that returns the name in order to print it.
string UserData::getName() const {
	return name;
}

//Function that returns the last name in order to print it.
string UserData::getLastName() const {
	return lastName;
}

/*Function that returns the userName in order to print it or compare it with the one
 entered by the user so that he/she may log in.*/
string UserData::getUserName() const {
	return userName;
}

//Function that returns the encrypted password so that it may be saved in a text file. 
string UserData::savePassWord() const {
	return passWord;
}

/*Function that returns the decrypted password to compare it with the one entered by the user
 so that he/she may log in.*/
string UserData::compPassWord() {
	return encryptDecrypt(passWord);
}

/*Returns the id so that it may be printed or compared with the one the user entered, and if its the same
grant them accesss to the account*/
int UserData::getId() const {
	return id;
}