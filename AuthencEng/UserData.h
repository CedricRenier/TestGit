//By Cedric Renier && Elimelec Rodriguez
#ifndef USERDATA
#define USERDATA
#include <string>
using namespace std;

class UserData {
private:
	/*variable to hold the number of objects created during the program
	and later subtract it 1000 in set ID function*/
	static int objectCount;

	//variable to hold the name inputed from the user
	string name;

	//variable to keep the last name of the user
	string lastName;

	//variable that hold the created username of the user
	string userName;

	//holds the desired id for the user
	int id;

	//holds the created password by the user
	string passWord;

	//Function to set the id once a new user is created or an existing one
	//is extracted from the file, this function is private since the program is the one
	//to set the id of the user.
	void setId();

	//function that encrypts or decrypts the users password, this password is later saved
	//to a file or decrypted in order to compare with the user login password
	string encryptDecrypt(string);

public:
	//Default constructor
	UserData();

	//Overloaded constructor used when a new user is being created
	UserData(string, string, string, string);

	//Overloaded constructor used for the information extracted from the file
	UserData(string, string);


	//setters
	void setName(string); //Sets the name of the user
	void setLastName(string); //Sets the last name of the user
	void setUserName(string); //Sets the username entered by the user
	void setPassWord(string); //Sets the password attribute to the one the user entered

	//getters
	string getName() const; //Retrieves the users name
	string getLastName() const; //Retrieves the users last name
	string getUserName() const; //Retrieves the users UserName
	string savePassWord() const; //Function used to save the encrypted password to a file
	string compPassWord(); //Function used to retrieve the decrypted password and compare it to the one 
						   //entered by the user
	int getId() const; //Retrieves the users id.
};
#endif
