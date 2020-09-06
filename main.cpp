#include <iostream>
#include <fstream>
#include <vector>
#include "users.h"

using namespace std;

int log_in(vector<Users> users_vector);
void register_the_user(vector<Users> &users_vector);
string give_nickname(vector<Users> users_vector, int active_user_id);
void show_users_menu(vector<Users> users_vector);

void save_users_to_file(string file_name, vector<Users> users_vector);
void load_users_from_file(string file_name, vector<Users> &users_vector);
string get_word_from_line_splited_by_character(string text_line, char splitting_character, int which_word_in_order_you_want_to_get);

int main()
{
    vector<Users> users_vector;
    string users_file_name = "Users.txt";
    int users_quantity;

    char user_choice;
    while (true)
    {
        users_vector.clear();
        load_users_from_file(users_file_name, users_vector);
        show_users_menu(users_vector);

        cin >> user_choice;
        switch (user_choice)
        {
            case '1':
            {
                // REGISTRATION

                register_the_user(users_vector);
                users_quantity = users_vector.size();
                save_users_to_file(users_file_name, users_vector);
                break;
            }

            case '2':
            {
                // LOGGING

                int active_user_id;
                while (true)
                {
                    active_user_id = log_in(users_vector);
                    //cout << "active_user_id: " << active_user_id << endl << endl;
                    if(0 < active_user_id)
                    {
                        cout << "You have correctly logged in :)" << endl;
                        cout << "Welcome: " << give_nickname(users_vector, active_user_id) << "!" << endl << endl;
                        system("pause");
                        break;
                    }
                }
                break;
            }

            case '9':
            {
                cout << "Exiting...";
                system("pause");
                exit(0);
            }
            break;
        }



    }


// LOOP SHOWING ALL USERS
/*
        users_quantity = users_vector.size();
        for (int i = 0; i < users_quantity; i++)
        {
            users_vector[i].show_user();
            cout << endl;
        }
*/
    return 0;
}

int log_in(vector<Users> users_vector)
{
    int users_quantity = users_vector.size();
    string nick;
    string pass;
    bool is_user_correct = false;
    bool is_password_correct = false;
    cout << "Nickname: "; cin >> nick;
    for (int i = 0; i < users_quantity; i++)
    {
        if(nick == users_vector[i].nickname)
        {
            is_user_correct = true;
            cout << "Password: "; cin >> pass;
            if (pass == users_vector[i].password)
            {
                is_password_correct = true;
                cout << endl;
                users_vector[i].show_user();
                cout << endl;
                return users_vector[i].id;
            }
        }
    }

    if (is_user_correct == false)
    {
        cout << "There is not any user with that nickname in our database." << endl << endl;
    }
    else
    {
        if (is_password_correct == false)
        {
            cout << "Password is not correct!" << endl << endl;
        }
    }
    return 0;
}

void register_the_user(vector<Users> &users_vector)
{
    Users user;
    string nick;
    string pass;
    int users_quantity = users_vector.size();
    int user_id = users_quantity + 1;

    cout << "Nickname: "; cin >> nick;

    bool is_user_in_database = false;
    while (true)
    {
        for (int i = 0; i < users_quantity; i++)
        {
            if (nick == users_vector[i].nickname)
            {
                is_user_in_database = true;
                cout << "That nickname has already taken. Please, choose another one :).";
                break;
            }
        }
        if (is_user_in_database == false)
        {
            cout << "Password: "; cin >> pass;
            user.set_user(user_id, nick, pass);
            users_vector.push_back(user);
            break;
        }
    }
}

string give_nickname(vector<Users> users_vector, int active_user_id)
{
    int users_quantity = users_vector.size();
    for (int i = 0; i < users_quantity; i++)
    {
        if (active_user_id == users_vector[i].id)
        {
            return users_vector[i].nickname;
        }
    }
    return "ERROR";
}

void show_users_menu(vector<Users> users_vector)
{
    system("cls");
    cout << "Welcome to address book!"<< endl;
    cout << "Users in database: " << users_vector.size() << endl;
    cout << endl;
    cout << "USERS MENU"<< endl;
    cout << endl;
    cout << "What do you want to do?" << endl;
    cout << "1. Register" << endl;
    cout << "2. Log in" << endl;
    cout << "9. Exit" << endl;
    cout << endl;
    cout << "Your choice: ";
}

//=========================== SAVING & LOADING USERS ===========================\\

void save_users_to_file(string file_name, vector<Users> users_vector)
{
    cout << "Saving data to file..." << endl;
    int users_in_database = users_vector.size();
    fstream file;
    file.open(file_name, ios::out);

    for (int index = 0; index < users_in_database; index++)
    {
        file << users_vector[index].id << "|";
        file << users_vector[index].nickname << "|";
        file << users_vector[index].password << "|" << endl;
    }
    file.close();
    cout << "...completed." << endl;
}

void load_users_from_file(string file_name, vector<Users> &users_vector)
{
    cout << "Loading data from file..." << endl;

    Users user;
    char splitting_character = '|';
    string word;
    fstream file;
    string line;
    int quantity_of_data_in_one_record = 3;
    file.open(file_name, ios::in);

    if (file.good())
    {
        int which_word = 1;
        int which_word_in_line;
        bool end_of_line;
        while(getline(file, line))
        {
            end_of_line = false;
            while(end_of_line == false)
            {
                which_word_in_line = which_word % quantity_of_data_in_one_record;
                if (which_word_in_line == 0) which_word_in_line = quantity_of_data_in_one_record;
                word = get_word_from_line_splited_by_character(line, splitting_character, which_word_in_line);
                switch(which_word_in_line)
                {
                    case 1: user.id = atoi(word.c_str()); break;
                    case 2: user.nickname = word; break;
                    case 3: user.password = word; break;
                }
                if (which_word_in_line == 3)
                {
                    users_vector.push_back(user);
                    end_of_line = true;
                }

                which_word++;
            }
        }
    }
    file.close();

    cout << "...completed." << endl;
}

string get_word_from_line_splited_by_character(string text_line, char splitting_character, int which_word_in_order_you_want_to_get)
{
    string word = "";

    int character_position = 0;
    char character = text_line[character_position];

    while (character != splitting_character)
    {
        word += character;
        character_position++;
        character = text_line[character_position];
    }
    text_line.erase(0, character_position + 1);

    if(which_word_in_order_you_want_to_get == 1)
    {
        return word;
    }
    else if(1 < which_word_in_order_you_want_to_get)
    {
        return get_word_from_line_splited_by_character(text_line, splitting_character, which_word_in_order_you_want_to_get - 1);
    }
}
