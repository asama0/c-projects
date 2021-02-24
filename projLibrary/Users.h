#ifndef USERS_H 
#define USERS_H

struct User {
	char name[25];
	char email[30];
	char username[25];
	char password[25];
	int borrowedbooks[10]; //codes of books borrowed, max 10 can be borrowed.
	int i; //number of books borrowed
};

struct UserArray {
	struct User array[100]; //stores all users
	unsigned int length; //number of registered users
};

struct UserArray Users; //Global variable to store Users.

int register_user(struct User user); //Registers user
 
int login_user(struct User user); //Checks if the User exists and logs in appripriately

int user_exists(char username[25]);  //Checks if the user exists.

int save_users(); //Stores all users in user.dat file.

int load_users(); //Loads all users from user.dat file



#endif

