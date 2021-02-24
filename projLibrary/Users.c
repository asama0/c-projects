#include "Users.h"
int u;

int register_user(struct User user)
{
	Users.array[Users.length++] = user;
	store_users();
	printf("Registration successfull!\n");
	return 1;
}

//returns -1 if invalid username/password
//returns 2 if its admin
//returns 1 if its correct username/password
int login_user(struct User user)
{
	int i;
	for(i=0; i<Users.length; i++)
	{
		if(!strcmp(Users.array[i].username, user.username) && !strcmp(Users.array[i].password, user.password))
		{
			u = i;
			printf("Login successfull!\n");
			if(!strcmp(user.username, "admin"))
				return 2;
			else
				return 1;
		}
	}
	return -1;
}

int user_exists(char username[25])
{
	int i;
	for(i=0; i< Users.length; i++)
	{
		if(!strcmp(Users.array[i].username, username))
			return 1;
	}
	return 0;
}

int store_users()
{
	
	int i;
	FILE *fp = fopen("users.txt", "w");
	fwrite(&Users, sizeof(struct UserArray), 1, fp);
	fclose(fp);
}

int load_users()
{
	int i=0;
	FILE *fp = fopen("users.txt", "r");
	if(fp)
	{
		fread(&Users, sizeof(struct UserArray), 1, fp);
		fclose(fp);
	}
}
