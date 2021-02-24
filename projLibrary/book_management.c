#include "book_management.h"
#include <stdlib.h>

/*
All functions commenting is done in .h file.
*/

struct BookArray books;
static int ind=0;

int store_books()
{
	
	int i;
	FILE *fp = fopen("books.txt", "w");
	fwrite(&books, sizeof(struct BookArray), 1, fp);
	fclose(fp);
}

int load_books()
{
	int i=0;
	FILE *fp = fopen("books.txt", "r");
	if(fp)
	{
		fread(&books, sizeof(struct BookArray), 1, fp);
		fclose(fp);
	}
}

int add_book(struct Book book)
{
	int count = books.length;
	books.array[count] = book;
	books.length++;
	store_books();
	printf("Book added successfully!\n");

}

int remove_book(struct Book book)
{
	int i;
	for(i=0; i<books.length; i++)
	{
		if(!strcmp(books.array[i].title, book.title) && !strcmp(books.array[i].authors, book.authors) && books.array[i].year == book.year)
		{
			int j;
			for(j=i; j <books.length; j++)
				books.array[j] = books.array[j+1];
			break;
		}
	}
	books.length--;
	store_books();
	printf("Book removed successfully!\n");
}


struct BookArray find_book_by_title (const char *title)
{
	int i;
	struct BookArray temp;
	temp.length = 0;
	for(i=0; i<books.length; i++)
	{
		if(!strcmp(books.array[i].title, title))
		{
			temp.array[temp.length++] = books.array[i];
		}
	}
	return temp;
}

struct BookArray find_book_by_author (const char *author)
{
	int i;
	struct BookArray temp;
	temp.length = 0;
	for(i=0; i<books.length; i++)
	{
		if(!strcmp(books.array[i].authors, author))
		{
			temp.array[temp.length++] = books.array[i];
		}
	}
	return temp;
}

struct BookArray find_book_by_year (const unsigned int year)
{
	int i;
	struct BookArray temp;
	temp.length = 0;
	for(i=0; i<books.length; i++)
	{
		if(year == books.array[i].year)
		{
			temp.array[temp.length++] = books.array[i];
		}
	}
	return temp;
}

int book_exists(char *code)
{
	int i;
	for(i=0; i< books.length; i++)
	{
		if(!strcmp(code, books.array[i].code))
			return i;
	}
	return -1;
}
