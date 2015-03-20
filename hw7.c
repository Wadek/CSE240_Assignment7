#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)
typedef enum {diploma, bachelor, master, doctor} education;  //education is name of enum type
char *myDatabase = "filename"; // global declaration of file pointer

struct person {              // a node to hold personal details
  char name[31];
  char email[30];
  int phone;
  education degree;
  struct person *next;
};
//note to grader: this makes more sense in my head rather than using head* on line 16
struct person *head;

void flush();                 // forward declaration of functions
void branching(char c);       
void insertion();
void delete_person();
void deletion(char *sname);
void search_person();
int print_all(); 
int print_person(struct person *p); 
struct person *search(char *sname);

int main() {  // print a menu for selection
  char ch = 'i';

  ungetc('\n', stdin); // inject the newline character into input buffer

  do {
    printf("Enter your selection\n");
    printf("\ti: insert a new entry\n");
    printf("\td: delete an entry\n");
    printf("\ts: search an entry\n");
    printf("\tp: print all entries\n");
    printf("\tq: quit \n");

    flush();  // flush the input buffer. To be discussed later
    ch = tolower(getchar());      
    branching(ch);
  } while (ch != 113);//"q" 
  return 0;
}

void flush() {  // flush the input buffer. To be discussed later
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}


void branching(char c) {    // branch to different tasks
  switch (c) {
    case 'i':
      insertion();
      break;
    case 's':
      search_person();
      break;
    case 'd':
      delete_person();
      break;
    case 'p':
      print_all(); 
      break;
    case 'q':
      break;
    default:
      printf("Invalid input\n");
  }
}

  /* **********************************************************
   * Insert function in English
   * reserve memory allocation on the heap for a new person
   * being added to struct
   * ask for the person info to be added
   *
   * if the list is empty assign head to point to new
   * else
   * while current points to a person 
   * if new->name is less than or equal to current->name
   * if the comparison is done to the head position
   * then we have the case that head is set as the new
   * else insert new before current
   * else if it's the end of the list
   * insert it at the end
   * move on to the next person
   ************************************************************/   
void insertion() 
{
  struct person *new =(struct person*)malloc(sizeof(struct person));

  printf("Enter name, phone, email:\n");
  scanf("%s", new->name);
  scanf("%d", &new->phone);
  scanf("%s", new->email);
  printf("Please Enter Education: \n0: diploma \n1: bachelor \n2: master \n3: doctorate \n");
  unsigned int degree;
  scanf("%d", &degree);
  if (degree > 0x3) {
    printf("Error: degree %d is invalid\n", degree);
    free(new);
    return;
  }
  new->degree = degree;

  if (!head) {
    head = new;
  }
  else
  {
    struct person *current, *previous;
    current = previous = head;
    while (current) {
      if (strcmp(new->name, current->name) <= 0) {
        if (current == head) {
          head = new;
        } else {
          previous->next = new;
        }
        new->next = current;
        break;
      } else if (!current->next) {
        current->next = new;
        new->next = NULL;
        break;
      }

      previous = current;
      current = current->next;
    }
  }
}

 /********************************************************
 * Print functions in English.
 * print person first prints name,email,phone and degree in order
 * switch required to print the correct word associated with degree choice
 * print_all first checks to see if head is null
 * when not null is found, head is assigned to p
 * while p exists (not null)
 * it prints the person, then sets p to p->next, until p is null   
 */
int print_person(struct person *p) { 
  
  printf("\n\nname = %s\n", p->name);
  printf("email = %s\n", p->email);
  printf("phone = %d\n", p->phone);


  switch(p->degree) {
    case diploma:
      printf("degree = diploma \n");
      break;
    case bachelor:
      printf("degree = bachelor \n");
      break;
    case master:
      printf("degree = master \n");
      break;
    case doctor: 
      printf("degree = doctor \n");
      break;
  }

  return 0;

}

int print_all() { 
  struct person *p;
  
  if (!head) {
    printf("No entries found.");
  }
  else {
    p = head;
    while(p) {
      print_person(p);
      p = p->next;
    }
  }
  return 0; 
}

/* search for a struct person with sname and return a pointer to it
 * otherwise return null if not found */
struct person *search(char *sname) {
  struct person *current;
  
  current = head;
  while(current)
  {
    if(strcmp(sname, current->name) != 0)
        current = current->next;
    else
      break;
  }
  return current;
}

void deletion(char *sname) {
  /**********************************************
  * Goal: Remove a struct person from a linked list and free it.
   *
   * What do we need to find the correct person?
   * How do we go through the list and check for that name?
   * same as in insertion.
   * */
    struct person *current, *previous;
    current = previous = head;
    while (current) {
      if (strcmp(sname, current->name) == 0) {
        if (current == head) {
          head = current->next;
        } else {
          previous->next = current->next;
        }
        free(current);
        break;
      }

      previous = current;
      current = current->next;
    }
}
    
    /* name (char pointer) We need to scanf for a string (char array) */
void delete_person() {
  char sname[30]; 
  printf("which person do you want to delete? \n");
  scanf("%s", sname);
  deletion(sname); 
} 

void search_person() {
  char sname[30]; 
  struct person *foundPerson;
  printf("which person do you want to find?\n");
  scanf("%s", sname);
  /* search(sname) will return a pointer to a struct person */
  /* we need to assign that to another pointer
   * and check if it is null. If it is not null, then print that person */
  /* We need a struct person pointer in this function.
   * We need to assign that new pointer the pointer that search(sname) returns.
   * We need to check that new pointer to see if it is null.
   * If it is null. Print out that we could not find a person by that name.
   * if it is not null, pass that new pointer into print_person(pointergoeshere).
   * NOTE: print_person will take any pointer which is of type (struct person *).
   * The name of that pointer does not matter. */
  foundPerson = search(sname);
  if(!foundPerson) {
    printf("Terribly Sorry ol' chap, %s doesn't exist, they might be\n", sname);
    printf("persuing their dreams of being a professional cricketeer.\n");
  }
   else
    print_person(foundPerson);
} 

