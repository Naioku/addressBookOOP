#include <iostream>
#include <vector>

using namespace std;

class Users
{
    int id;
    string nickname;
    string password;

public:

    friend int log_in(vector<Users>);
    friend string give_nickname(vector<Users>, int);
    friend void register_the_user(vector<Users>&);
    friend void save_users_to_file(string, vector<Users>);
    friend void load_users_from_file(string, vector<Users>&);
    //Users(int, string, string);
    void set_user(int, string, string);
    void show_user();

    //void log_in();

    //void delete_user();


};
