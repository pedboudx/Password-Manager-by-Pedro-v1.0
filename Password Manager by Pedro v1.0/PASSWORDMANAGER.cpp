#include <iostream>
#include "MasterLogin.hpp"
#include "Password.hpp"
#include "stackfunctions.hpp"
#include "textFileFunctions.h"
#include <string>
#include <Windows.h>
#include "MasterEncrypt.hpp"


using namespace std; 
using namespace Boudoux;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


int main()
{


	std::cout << "Password Manager by Pedro v1.0 \n\n";

	int attempt = 3;

	// IF THERE IS NO ENCRYPTED MASTER.TXT FILE
	const string MASTER_KEY_FILE = "master.txt";
	ifstream Master(MASTER_KEY_FILE);
		
		// IF THERE IS NO MASTER FILE ASK USER TO CREATE A PASSWORD

	if (!Master) {

		// Ask user to set master password

		cout << "No existing master key detected, please set a master key for the program. \n";
		SetConsoleTextAttribute(h, 4);
		cout << "NOTE: This master key will be the password to utilizing this program FOREVER, if you lose it, you will lose your data." << endl;
		cout << "Do NOT forget this password otherwise you will not be able to access the program in the future." << endl;
		SetConsoleTextAttribute(h, 15);
		cout << "Set your master password below: " << endl << endl;

		string Master1, Master2 = " ";
		char master_confirmation = 'N';

		while (master_confirmation == 'N') {
			while (Master1 != Master2) {
				cout << "New Master Password: ";
				cin >> Master1;
				cout << "Confirm Master Password: ";
				cin >> Master2;

				if (Master1 != Master2) {
					cout << "Passwords don't match, enter them again. \n";
				}
			}
			cout << "This will be your master password FOREVER, do you wish to proceed with this? (Y/N) \n ";
			cin >> master_confirmation;
		}

		masterEncrypt(Master1);

	}

	string MASTER_KEY_DEFINITION = masterDecrypt();

	MasterLogin masterAuth(MASTER_KEY_DEFINITION);

	do {


		string keyAttempt;
		cout << "Please Enter the Master Key in order to proceed and access other passwords." << endl << "Master Key: ";
		cin >> keyAttempt;

		masterAuth.isAuthorized(keyAttempt);

		if (masterAuth.checkAuth() == false) {
			cout << "Wrong key... " << attempt << " attempts left." << endl;

			attempt--;

		}
		if (attempt < 0)
		{
			SetConsoleTextAttribute(h, 4);
			cout << "No more attempts left... Closing Program..." << endl;
			SetConsoleTextAttribute(h, 15);

		}

	} while (attempt >= 0 && masterAuth.checkAuth() == false);

	if (masterAuth.checkAuth() == true)
	{
	

		vector <Boudoux::Password> passwordList;

		cout << "Correct Key... Proceeding to main program now..." << endl;
		cout << "Retrieving and loading information from storage files..." << endl;
		decrypt();
		retrieveFromTxt(passwordList);
		cout <<  "Data successfully retrieved..." << endl;
		
		
		char input = ' ';
		bool back = false;

		while (input != 'E') {
			cout  << endl << "Now choose desired action: \n" << "A - Add a new password \nB - Remove and forget a password \nC - Search for specific password \nD - View all info in a list \nE - Exit Program" << endl << endl;
			cin >> input;
			input = toupper(input);

			string newWebsite, newUsername, newPassword1 = "1";
			string newPassword2 = "2";
			string websitesearch = "";

			switch (input) {
			case 'A': // Add a new Password to your password list.

				cout << "Now Enter your login info for the new website you'd like to add. (X - To go Back)" << endl << endl;
				cout << "Website Name: ";
				cin.ignore();
				getline(cin, newWebsite);

				if (newWebsite == "X") {
					cout << "Going back... \n";
					break;
				}
				else {

					cout << "Username: ";
					cin >> newUsername;

					while (newPassword1 != newPassword2) {
						cout << "Password: ";
						cin >> newPassword1;
						cout << "Confirm Password: ";
						cin >> newPassword2;

						if (newPassword1 != newPassword2) {
							cout << "Passwords don't match, enter them again. \n";
						}
					}

					createNewPassword(newWebsite, newUsername, newPassword1, passwordList);

					break;
				}

			case 'B': // Remove a website from the list
				while (findIndex(websitesearch, passwordList) == -1 && back == false) {

					cout << "Enter below the name of the website you'd like to forget login info for. (X - To go back)\nWebsite Name: ";
					cin.ignore();
					getline(cin, websitesearch);

					if (websitesearch == "X") {
						cout << "Going back...\n";
						back = true;
						break;
					}
					else {

						if (findIndex(websitesearch, passwordList) == -1 && websitesearch != "X") {
							cout << "Unable to find website named... typo maybe?? Or Website information non-existent." << endl;
						}
					}

				}
				if (websitesearch != "X") {
					deletePassword(websitesearch, passwordList);
				}
				break;


			case 'C': // Search and Display a Specific Password

				do {
					cout << "Enter below the name of the website you'd like to access your login info for. (X - To go back) \nWebsite Name: ";
					cin.ignore();
					getline(cin, websitesearch);
					if (websitesearch == "X") {
						cout << "Going back...\n";
						back = true;
						break;
					}
					else {

						if (findIndex(websitesearch, passwordList) == -1 && websitesearch != "X") {
							cout << "Unable to find website named... typo maybe?? Or Website information non-existent." << endl;
						}
						else {
							cout << passwordList[findIndex(websitesearch, passwordList)];
						}
					}
				} while (findIndex(websitesearch, passwordList) == -1 && back == false);
				break;

			case 'D':

				for (auto n : passwordList) {
					cout << n << endl;
				}

			}
		
		}

		writeToTxt(passwordList);
		encrypt();

	}
	
}
