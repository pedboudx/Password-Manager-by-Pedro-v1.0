#include <iostream>
#include <string>
#include "Password.hpp"

namespace Boudoux {

	Password::Password() {
		website = "";
		user = "";
		password = "";
	}

	Password::Password(std::string new_website, std::string new_user, std::string new_password) {
		website = new_website;
		user = new_user;
		password = new_password;
	}

	Password::~Password() {}

	void Password::updatePassword(std::string input) {
		password = input;
	}

	void Password::updateUser(std::string input)
	{
		user = input;

	}

	void Password::updateWebsite(std::string input) 
	{
		website = input;
	}

	std::string Password::getPassword()  const {
		return password;
	}

	std::string Password::getUser() const {
		return user;
	}

	std::string Password::getWebsite()const {
		return website;
	}

	


}