#include "book_management.c"
#include "Users.c"
#include <string.h>
void user_menu();
void admin_menu();

//Checks if the entered email is correct one
int is_valid_email(char *email)
{
	int i;
	for(i=0; i<strlen(email); i++)
	{
		if(email[i] == '@' && i != 0 && i != strlen(email)-1)
			return 1;
	}
	return 0;
}

//Borrows the book by incrementing book's borrowed copy number
//Also adds the book index(index) to User's structure.
int borrow_Book(int index)
{
	if(Users.array[u].i >=10)
	{
		printf("More books cannot be borrowed, return other books before borrowing again.\n");
	}
	else
	{
		books.array[index].borrowed_copies++;
		Users.array[u].borrowedbooks[Users.array[u].i++] = index;
		printf("Book borrowed successfully!\n");
		store_users();
	}
	return 0;
}

//Returns the book by decrementing number of borrowed copies of book at index 'index'.
//Also removes this index from User data
int return_Book(int index)
{
	int i;
	for(i=0; i<10; i++)
	{
		if(Users.array[u].borrowedbooks[i] == index)
		{
			int j;
			for(j=i; j<Users.array[u].i; j++)
				Users.array[u].borrowedbooks[j] = Users.array[u].borrowedbooks[j+1];
			Users.array[u].i--;
			books.array[index].borrowed_copies--;
			printf("Book returned successfully!\n");
			store_users();
			return 1;
		}
	}
	return 0;
}

//Registration menu, takes appropriate input and makes appropriate function calls.
void registration()
{
	struct User u;
	printf("Enter your username: ");
	fflush(stdin);
	scanf("%s", u.username);
	if(user_exists(u.username))
	{
		printf("\nUsername already exists!\n");
		return;
	}
	else
	{
		printf("Enter your password: ");
		fflush(stdin);
		scanf("%s", u.password);
		printf("Enter your Name: ");
		fflush(stdin);
		scanf("%s", u.name);
		while(1)
		{
			printf("Enter your Email: ");
			fflush(stdin);
			scanf("%s", u.email);
			if(is_valid_email(u.email))
				break;
			else
				printf("Invalid email, does not contain '@' in correct position.\n");
		}
		register_user(u);
	}
}

//login menu. Takes input and then calls login_user from User.h
//also tells if its an admin login or user login (1 for user, 2 for admin)
//opens respective menu for admin/user.
void login()
{
	struct User u;
	printf("Enter your username: ");
	fflush(stdin);
	scanf("%s", u.username);
	printf("Enter your password: ");
	fflush(stdin);
	scanf("%s", u.password);
	
	int i =  login_user(u);
	if( i == 1)
		user_menu();
	else if(i == 2)
		admin_menu();
	else
	{
		printf("Invalid username/password\n");
		login();
	}
}

/*
Offers 4 options of navigation
1) All available books
2) Books by title
3) Books by authors
4) Books by Year
After showing the list, user can enter the code of the book he wants to enter
OR
enter "1" to go back.
*/
void search_books()
{
	struct BookArray searched;
	int check = 0;
	while(1)
	{
		check = 0;
		printf("1.Display all\n2.Search by title\n3.Search by author\n4.Search by Year\n5.Exit->");
		int in;
	    fflush(stdin);
		scanf("%d", &in);
		if(in == 1)
		{
			int i;
			printf("Displaying all books: \n");
			for(i=0; i<books.length; i++)
			{
				printf("Title: %s Author: %s Year: %d Code: %s\n", books.array[i].title, books.array[i].authors, books.array[i].year, books.array[i].code);
			}
			check = 1;
			break;
		}
		else if(in == 2)
		{
			char title[25];
			printf("Enter the title: ");
	        fflush(stdin);
			scanf("%s", title);
			searched = find_book_by_title(title);
			break;
		}
		else if(in == 3)
		{
			char author[25];
			printf("Enter the author: ");
	        fflush(stdin);
			scanf("%s", author);
			searched = find_book_by_title(author);
			break;
		}
		else if(in == 4)
		{
			int year;
			printf("Enter the year: ");
	        fflush(stdin);
			scanf("%d", &year);
			searched = find_book_by_year(year);
			break;
		}
		else if(in == 5)
		{
			exit(0);
		}
		else
			printf("Invalid option!\n");
	}
	printf("Displaying Books by your choice...\n");
	int i;
	if(check == 0)
	{
		for(i=0; i<searched.length; i++)
		{
			printf("Title: %s Author: %s Year: %d Code: %s\n", searched.array[i].title, searched.array[i].authors, searched.array[i].year, searched.array[i].code);
		}
	}
	printf("Enter 1 to go back, or code of the book that you want to borrow: ");
	char inp[25];
	fflush(stdin);
	scanf("%s", inp);
	
	if(!strcmp(inp, "1"))
		return;
	else
	{
		int x = book_exists(inp);
		if(x == -1)
		{
			printf("Invalid code entered!\n");
			return;
		}
		else
		{
			borrow_Book(x);
		}
	}
	
}

/*
Shows all the books borrowed by the user.
Once the code is entered from the list of the book, appropriate function is called to return the book.
*/
void return_books_menu()
{
	printf("Borrowed Books:\n");
	int i;
	for(i=0; i< Users.array[u].i; i++)
	{
		printf("Title: %s Author: %s Year: %d Code: %s\n", books.array[Users.array[u].borrowedbooks[i]].title, books.array[Users.array[u].borrowedbooks[i]].authors, books.array[Users.array[u].borrowedbooks[i]].year, books.array[Users.array[u].borrowedbooks[i]].code);
	}
	printf("Enter code of the book you want to return: ");
	char code[25];
	fflush(stdin);
	scanf("%s", code);
	int x = book_exists(code);
	if(x == -1)
	{
		printf("Invalid code entered!\n");
		return;
	}
	else
	{
		return_Book(x);
	}
}

/*
Shows admin menu when an admin logs in.
Offers 2 options for the library:
1) Add Book 
2) Remove Book
*/
void admin_menu()
{
	while(1)
	{
		printf("1.Add Book\n2.Remove Book\n3.Exit\n->");
		int in;
		scanf("%d", &in);
		if(in == 1)
		{
			printf("Enter book code: ");
			struct Book b1;
	        fflush(stdin);
			scanf("%s", b1.code);
			if(book_exists(b1.code) != -1)
			{
				printf("Book code already in the library!\n");
				continue;
			}
			printf("Enter Book Title: ");
	        fflush(stdin);
			scanf("%s", b1.title);
			printf("Enter Book Authors: ");
	        fflush(stdin);
			scanf("%s", b1.authors);
			printf("Enter Book Year: ");
	        fflush(stdin);
			scanf("%d", &b1.year);
			printf("Enter number of copies: ");
			scanf("%d", &b1.copies);
			b1.borrowed_copies = 0;
			add_book(b1);
		}
		else if(in == 2)
		{
			struct Book b1;
			printf("Enter Book Title: ");
	        fflush(stdin);
			scanf("%s", b1.title);
			printf("Enter Book Authors: ");
	        fflush(stdin);
			scanf("%s", b1.authors);
			printf("Enter Book Year: ");
	        fflush(stdin);
			scanf("%d", &b1.year);
			remove_book(b1);
		}
		else if(in == 3)
			exit(0);
	}
}

/*
Menu when an ordinary user logs in.
1) He can search/borrow (same option) (borrowing is optional)
2) Return books
*/
void user_menu()
{
	while(1)
	{
		printf("1.Search/Borrow Books\n2.Return Books\n3.Exit\n->");
		int in;
		scanf("%d", &in);
		if(in >3 || in <1)
		{
			printf("Invalid input, enter again.\n->");
			continue;
		}
		else if(in == 1)
		{
			search_books();
		}
		else if(in == 2)
		{
			return_books_menu();
		}
		else
			exit(0);
	}
	
}

int main(){

    FILE *file;
    Users.length = 0;
    load_users();
    load_books();
    /*
    struct Book b1 = {"Sea of Flames", "Shakespeare", 1999, 1000, 0};
    struct Book b2 = {"Sea of Flames", "Shakespeare", 2000, 1000, 0};
    struct Book b3 = {"Sea of Flames", "Shakespeare", 2001, 1000, 0};
    struct Book b4 = {"Sea of Flames", "William", 2001, 1000, 0};
    struct Book b5 = {"Sea of Flames", "Shakespeare", 2002, 1000, 0};
    add_book(b1);
    add_book(b2);
    add_book(b3);
    add_book(b4);
    add_book(b5);
    
    struct BookArray b = find_book_by_year(2001);
    
    int i;
    
    for(i=0; i<b.length; i++)
    {
    	printf("Name: %s Author: %s Year: %d Copies: %d\n", b.array[i].title, b.array[i].authors, b.array[i].year, b.array[i].copies);
	}
    */
    
    //while(1)
    while(1)
    {
    	printf("1.Register\n2.Login\n3.Exit\n->");
    	int in ;
    	scanf("%d", &in);
    	if(in == 1)
    	{
    		registration();
		}
		else if(in == 2)
		{
			login();
			break;
		}
		else if(in == 3)
			exit(0);
		else
		{
			printf("Invalid option!\n");
		}
	}
    
}
