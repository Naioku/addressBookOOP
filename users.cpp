#include <iostream>
#include <fstream>
#include "users.h"

using namespace std;

void Users::set_user(int identif, string nick, string pass)
{
    if (identif < 1 || nick == "" || pass == "")
        cout << "ERROR: Nickname or password cannot be empty. Id cannot be under 1.";
    else
    {
        id = identif;
        nickname = nick;
        password = pass;
    }
}

void Users::show_user()
{
    cout << "id: " << id << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Password: " << password << endl;
}

/*
void Users::log_in()
{

}
*/
