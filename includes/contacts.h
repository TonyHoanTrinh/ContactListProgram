#ifndef __CONTACTSH__
#define __CONTACTSH__ 

/* Libraries declaration */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Structure data type declarations here */
/* Structure data type declaration of contact information location */
struct contact
{
  unsigned long phone_number;
  long first_name_posn;
  long last_name_posn;
  long company_name_posn;
  long email_posn;
  long next;
};

/* Structure data type declaration of contact information */
struct contactInfo
{
  char *firstName;
  char *lastName;
  char *companyName;
  char *email;
  unsigned long phone_number;
  int deletedOrEditedFlag;
};

/* Function Prototypes here */
void writeFiles(struct contactInfo, FILE*);
int checkPhoneNumber(char[]);
int checkEmailAddress(char[]);
int compare_names(const void *, const void *);

#endif
