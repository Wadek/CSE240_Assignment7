#include <stdio.h>   
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define MAX 100
 
typedef enum { diploma = 0, bachelor, master, doctor } education;
 
// A struct for nodes of the linked list. 
struct container {
  struct person *plink; // points to a struct person.
  struct container *next;
}; // size of pointers to person and plink
 
// A struct to hold attributes of a person
struct person {
  char name[32];
  char email[32];
  int phone;
  education degree;
}; // 72 bits;
 
void branching(char c);   // given
char* get_name(); // given
void printFirst(struct container* root);  // given
int insertion(struct container** pointerToHead);  // Question 1
struct container* search(struct container* root, char* sname);  // Question 2
void deleteFirst(struct container** pointerToHead);   // Question 3
void deleteAll(struct container** pointerToHead);   // Question 4
void printAll(struct container* root);  // Question 5
void printPerson(struct container* c); // prints person after found using search 
int main()
{
  struct container* head = NULL; // Declare head as a local variable of main function
  // Print a menu for selection
  char ch = 'i';
  do {
    printf("Enter your selection\n");
    printf("\ti: insert a new entry\n");
    printf("\td: delete one entry\n");
    printf("\tr: delete all entries\n");
    printf("\ts: search an entry\n");
    printf("\tp: print all entries\n");
    printf("\tq: quit \n");
    fflush(stdin);    // Flush the input buffer. 
    ch = tolower(getchar());  // Convert any uppercase char to lowercase.
    branching(ch, &head);
    printf("\n");
  } while (ch != 113);      // 113 is 'q' in ASCII
  return 0;
}
 
// Branch to different tasks: insert a person, search for a person, delete a person
// print all added persons.
void branching(char c, struct container** pointerToHead)
{
  /* we need a container pointer */
  struct container *pp;
  char *p;
  switch (c) {
  case 'i':
    insertion(pointerToHead);
    break;
  case 's':
    p = get_name();
    pp = search(*pointerToHead, p);
    printPerson(pp); /* print the person we found */
    free(p);
    break;
  case 'd':
    deleteFirst(pointerToHead);
    break;
  case 'r':
    deleteAll(pointerToHead);
    break;
  case 'p':
    printAll(*pointerToHead);
    break;
  case 'q':
    deleteAll(pointerToHead); // free all memory
    break;
  default:
    printf("Invalid input\n");
  }
}
// Read the input from the user.
char * get_name()
{
  char *p = (char *) malloc(32);//Use dynamic memory, which does not go out of scope
  pintf("Please enter a name for the search: ");
  scanf("%s", p);
  return p;
}
void printFirst(struct container* root)
{
  if (root != NULL)
  {
    printf("\n\nname = %s\n", root->plink->name);
    printf("email = %s\n", root->plink->email);
    printf("phone = %d\n", root->plink->phone);
    switch (root->plink->degree)
    {
    case diploma:
      printf("degree = diploma\n");
      break;
 
    case bachelor:
      printf("degree = bachelor\n");
      break;
 
    case master:
      printf("degree = master\n");
      break;
 
    case doctor:
      printf("degree = doctor\n");
      break;
 
    default:
      printf("System Error: degree information corruption.\n");
      break;
    }
    printFirst(root->next);
  }
}

void deleteAll(struct container** pointerToHead) {

  /*
  The function will delete all nodes in the linked list. 
  You must make sure no memory leak. The function must 
  use recursion, instead of loop, to traverse through 
  the linked list. You can call deleteFirst function 
  in this function.
  */
  }

void printPerson(struct container* c) {
  if(!c) {
    printf("\n\nname = %s\n", c->plink->name);
    printf("email = %s\n", c->plink->email);
    printf("phone = %d\n", c->plink->phone);
    switch (c->plink->degree)
    {
    case diploma:
      printf("degree = diploma\n");
      break;
 
    case bachelor:
      printf("degree = bachelor\n");
      break;
 
    case master:
      printf("degree = master\n");
      break;
 
    case doctor:
      printf("degree = doctor\n");
      break;
 
    default:
      printf("System Error: degree information corruption.\n");
      break;
    }
  }
}


struct container* search(struct container* root, char* sname) {
  struct container *c;
  c = root;

  while(!c) {
    if(strcmp(sname, c->plink->name) == 0 ) {
      break;
    }
    c = c->next;
  }
  return c;
}
 
int insertion(struct container** pointerToHead) {
  
  struct container *c, *head;
  struct person *p;

  c = malloc(sizeof(struct container));
  p = malloc(sizeof(struct person));
  c->plink = p;
  c->next = NULL;
  
  head = *pointerToHead;

  printf("Enter name, phone, email:\n");
  scanf("%s", p->name);
  scanf("%d", &p->phone);
  scanf("%s", p->email);
  printf("Please Enter Education: \n0: diploma \n1: bachelor \n2: master \n3: doctorate \n");
  unsigned int degree;
  scanf("%d", &degree);
  if (degree > 0x3) {
    printf("Error: degree %d is invalid\n", degree);
    free(p);
    free(c);
    return;
  }
  p->degree = degree;
 
  if(!*pointerToHead) {
    *pointerToHead = c;
  }
  else {
    struct person *current, *previous;
    current = previous = head;
    while (current) {
      if (strcmp(c->plink->name, current->name) <= 0) {
        if (current == head) {
          head = c;
        } else {
          previous->next = c;
        }
        c->next = current;
        break;
      } else if (!current->next) {
        current->next = c;
        c->next = NULL;
        break;
      }

      previous = current;
      current = current->next;
    }
  }
}

