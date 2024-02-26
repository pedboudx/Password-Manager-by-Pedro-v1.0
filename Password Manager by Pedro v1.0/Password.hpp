#pragma once

#include <iostream>
#include <string>

namespace Boudoux
{
	class Password {
	private:
		std::string website;
		std::string user;
		std::string password;

	public:
		Password();
		Password(std::string, std::string, std::string);
		~Password();

		void updatePassword(std::string);
		void updateUser(std::string);
		void updateWebsite(std::string); 

		std::string getPassword() const;
		std::string getUser() const;
		std::string getWebsite() const;

		friend std::ostream& operator<<(std::ostream& os, const Password& x) {

			std::cout << "Website: " << x.website << std::endl;
			std::cout << "Username: " << x.user << std::endl;
			std::cout << "Password: " << x.password << std::endl;

			return os;
		}

	};
}