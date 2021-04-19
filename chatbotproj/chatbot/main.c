#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
 #include <strings.h>
 #include <stdbool.h>
#define LINELENGTH 80
#define SEPCHARS "* .,?\"\n"


struct node_s {
	
  char *key;
  char *value;
  struct node_s *nextPtr;
};

typedef struct node_s node_t;

struct hashtable_s {
	
  int size;
  struct node_s **table;
};

typedef struct hashtable_s hashtable_t;


//function to create hashtable with the size of given input
hashtable_t* create_hashtable(int size){

	hashtable_t *hashtable = NULL;
	int i;
	
	//if the size passed as argument is negative then reurn NULL	
  	if(size<1)
  		return NULL;
  		
	//Allocating memeory to the the hashtable itself
	if((hashtable=malloc(sizeof(hashtable_t)))==NULL){
		
		//if we are unable to allocate the memory then return null
		return NULL;
	}
	
	//Allocating memory to the head nodes
	if((hashtable->table=malloc(sizeof(node_t*)*size))==NULL){
		
		//if we are unable to allocate the memory then return null
		return NULL;
	}
	
	//for all the allocated table size initialize it to NULL	
	for(i=0;i<size;i++){
		hashtable->table[i] = NULL;
	}
	
	//initialize size of hashtable to the size given to the function	
	hashtable->size = size;
	
	//return the allocated hashtable	
	return hashtable;
}

//this function converts the key to a hash code
int hash_function(hashtable_t *hashtable,char *key){

	unsigned long int hash_code = 0;
	unsigned long i = 0;

	//converting string to intetger (this loop continues till characters in key ends)
	while(hash_code<ULONG_MAX && i<strlen(key)){
		
		//left shifting the hashcode by 8 bits		
	    hash_code = hash_code << 8;
		//adding the int value of key[i] to hashcode	    
	    hash_code += key[i];
	    i++;
	}
	
	return hash_code % hashtable->size;
}

//this function return the value for the key in the hashtable
char* get_hash_value( hashtable_t *hashtable, char *key ){
	
	//converting the key to hashcode	
	int val = hash_function(hashtable,key);;
	node_t *node;
	
	
	//Step through the val, looking for our value in the hashtable
	node = hashtable->table[val];
	 
	//iterating thought the linked list till we find the code or reach till the end	
	while(node!=NULL && node->key!=NULL && strcmp(key,node->key)>0){
		node = node->nextPtr;
	}
	
	//chechking if we actually found the hashcode or not if we didnt find it then we return NULL else we return the value 		
	if(node==NULL || node->key==NULL || strcmp(key,node->key) != 0){
		return NULL;
	}
	else{
		return node->value;
	}
}

//function to create a new node of key-vaue pair
node_t* create_newnode(char *key,char *value){
    
	//creating new node    
	node_t *newnode;
	
	//Allocating memory to the newnode
	if((newnode=malloc(sizeof(node_t)))==NULL){
		
		//if we are unable to allocate the memory then return null
		return NULL;
	}
	
	//Duplicating the kay passed as augument to the key of the newnode	
	if((newnode->key=strdup(key))==NULL){
		
		//if we are unable to duplicate it the return NULL		
		return NULL;
	}
	
	//Duplicating the valuue passed as augument to the value of the newnode	
	if((newnode->value=strdup(value))==NULL){
		
		//if we are unable to duplicate it the return NULL
	    return NULL;
	}
	
	//initializing the nextPtr pointer of newnode to NULL	
	newnode->nextPtr = NULL;
	
	return newnode;
}

//this function store key-value pair into the hashtable
void ht_set(hashtable_t *hashtable, char *key, char *value) {
  
	int val = hash_function(hashtable, key);;
	node_t *newnode = NULL;
	node_t *nextPtr = NULL;
	node_t *lastPtr = NULL;
	
  	nextPtr = hashtable->table[val];
  	
	//iterating till we reach the end of the linked list in the hashtable  	
	while(nextPtr != NULL && nextPtr->key != NULL && strcmp(key, nextPtr->key) > 0){
		
    	lastPtr = nextPtr;
    	nextPtr = nextPtr->nextPtr;
	}

	//if there already exists a pair eith same value then we need to replace it  	
	if( nextPtr != NULL && nextPtr->key != NULL && strcmp(key, nextPtr->key) == 0){
		
		free(nextPtr->value);
	    nextPtr->value = strdup( value );	  
	}
	//else we insert the new pair in the linked list	
	else{
		
		//creating a new node to be inserted
    	newnode = create_newnode(key, value);

		//if we are at the head of the linked list	    
	    if(nextPtr == hashtable->table[val]){
	    	
	      	newnode->nextPtr = nextPtr;
	      	hashtable->table[val] = newnode;	
	    }
		//if we are at the tail of the linked list	    
		else if (nextPtr == NULL) {
			
	      lastPtr->nextPtr = newnode;
	    }
	    //if we are at the middle of the linked list
		else{
			
	      newnode->nextPtr = nextPtr;
	      lastPtr->nextPtr = newnode;
	    }
  	}
}



int main(){
	
	int i;
	char line[LINELENGTH];
	char *word;
	bool check = false;

	//creating hashtable
  	hashtable_t *hashtable = create_hashtable(65536);
  	
	//adding key-value pairs to the hashtable, more can be added if you want to...
	ht_set(hashtable, "hi", "Hello, how are you?");
  	ht_set(hashtable, "hey", "Hey, What's up?'");
  	ht_set(hashtable, "hello", "Hi, What are you doing?");
  	ht_set(hashtable, "hear", "What you heard is right!");
  	ht_set(hashtable, "c", "Yeah, C Language is fun to learn");
  	ht_set(hashtable, "light", "Yes! i am afraid of darkness...");
  	ht_set(hashtable, "what", "It is clear, ain't it?");
  	ht_set(hashtable, "weather", "It's hot outside!");
	ht_set(hashtable, "darkness", "I hate darkness i'm afraid of it");
	ht_set(hashtable, "nothing", "Do something usefull!"); 

	while(1){
	  	
		printf("\nUser: ");
		//taking input		
	    fgets(line, LINELENGTH, stdin);
	    
		//lowering all the capital characters	    
	    for(i=0;i<=strlen(line);i++){
      		if(line[i]>=65&&line[i]<=90)
         		line[i]=line[i]+32;
   		}
	    
		if (strlen(line)<=1)
			break;
	    
		//tokenizing the querry of the user	    
		word = strtok(line, SEPCHARS);
	
	    while (word != NULL) {
	    	
			if (strncasecmp(word, "exit", 150) == 0) {
	        	exit(0);
	      	}
	      	
	      	// Some responses based on the keywords
	      	if (get_hash_value(hashtable, word) != NULL) {
	        	printf("\nBot: %s\n", get_hash_value(hashtable, word));
	        	check = true;
	      	}
	      	
	      	if(check == true)
	      		break;

	      	word = strtok(NULL, SEPCHARS);
	    }
	    
	    if(check == false)
	    	printf("\nBot: %s\n", "Sorry, I don't know what to say about that" );
	    	
	    check = false;
	}
}
