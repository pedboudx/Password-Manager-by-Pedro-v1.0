
#include <iostream>
#include <string>

class MasterLogin {
private:
    std::string MASTERKEY;
    bool auth = false;

public:
    MasterLogin() {}

    MasterLogin(std::string setMASTERKEY) : MASTERKEY(setMASTERKEY) {}

    void isAuthorized(std::string keyAttempt) {
        if (keyAttempt == MASTERKEY) {
            auth = true; // Set auth to true if the key matches
        }
      
    }

    bool checkAuth()
    {
        return auth;
    }
   
};