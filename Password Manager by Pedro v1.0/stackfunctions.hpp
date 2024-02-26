#pragma once
#include <iostream>
#include "Password.hpp"
#include <vector>

// passwordList[i].getWebsite();

namespace Boudoux {

	int findIndex(std::string websiteName, std::vector <Password> passwordList) {

		// Function finds where the information for websiteName is stored within the vector and returns its index  

		for (int i = 0; i < size(passwordList); i++)
		{
			if ( websiteName == passwordList[i].getWebsite()  )
			{
				return i;
			}
		}
		
		return -1;

	}

	void deletePassword(std::string websiteName, std::vector <Password>& passwordList)
	{
		// Function takes websiteName then uses findIndex to find where that website is located then delete it from the stack

		passwordList.erase(std::next(passwordList.begin(), findIndex(websiteName, passwordList)));

		std::cout << websiteName << " successfully forgotten and removed from list." << std::endl;

	}

	void createNewPassword(std::string websiteName, std::string user, std::string Password, std::vector <Boudoux::Password>& passwordList)
	{
		// Function takes website name, username, password and passwordList vector
		// Adds a new element to passwordList and constructs it with websiteName, user and password

		Boudoux::Password temp(websiteName, user, Password);

		passwordList.push_back(temp);

	}



}