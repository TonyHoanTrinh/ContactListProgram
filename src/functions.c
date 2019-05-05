/* Header to link to the libraries in our contacts.h file */ 
#include "contacts.h" 

/******
 writeFiles: Takes in the contact location, information and file pointer to write the information into the file.
 In: struct contact contactLocation, struct contactInfo contactInformation, FILE *fp
 Out: Void
 Post: After it finishes writing to the file it will, return back to newcontactMenu
*******/
void writeFiles(struct contactInfo contactInformation, FILE* fp)
{
  /* Variables to hold position values which makes it easier to calculate byte sizes and positions */
  struct contact contactLocation;
  long contactStructureLocation;
  contactLocation.phone_number = contactInformation.phone_number;
  contactStructureLocation = ftell(fp);
  long currentPosition;
  currentPosition = 0;
  long secondaryByteCounter;
  secondaryByteCounter = 0;

  /* Calculating the positions of the contact locations in the file */

  /* If the the user entered nothing for the first name */
  if(strlen(contactInformation.firstName) == 0)
  {
    /* We set the first_name_posn as 0 and set our currentPosition as the 48 bytes + the location in the file */
    contactLocation.first_name_posn = 0;
    currentPosition = sizeof(struct contact) + contactStructureLocation;
  }
  /* If the user did entered information for the first name */
  else
  {
    /* We set the first_name_posn as the 48 bytes + the location in the file */
    contactLocation.first_name_posn = sizeof(struct contact) + contactStructureLocation;
    /* We set the currentPosition as the position of the first name to know where we are going to write for the next location */
    currentPosition = contactLocation.first_name_posn;
    /* Byte counter here to help condense a bit of code and makes it easier to count the size of the contact's information */
    secondaryByteCounter = strlen(contactInformation.firstName) + 1;
  }

  /* Same procedure as above but with last name */
  if(strlen(contactInformation.lastName) == 0)
  {
    contactLocation.last_name_posn = 0;
  }
  else
  {
    contactLocation.last_name_posn = currentPosition + secondaryByteCounter;
    currentPosition = contactLocation.last_name_posn;
    secondaryByteCounter = strlen(contactInformation.lastName) + 1;
  }

  /* Same procedure as above but with company name */
  if(strlen(contactInformation.companyName) == 0)
  {
    contactLocation.company_name_posn = 0;
  }
  else
  {
    contactLocation.company_name_posn = currentPosition + secondaryByteCounter;
    currentPosition = contactLocation.company_name_posn;
    secondaryByteCounter = strlen(contactInformation.companyName) + 1;
  }

  /* Same procedure as above but with email */
  if(strlen(contactInformation.email) == 0)
  {
    contactLocation.email_posn = 0;
  }
  else 
  {
    contactLocation.email_posn =  currentPosition + secondaryByteCounter;
    currentPosition = contactLocation.email_posn;
    secondaryByteCounter = strlen(contactInformation.email) + 1;
  }

  /* We calculate the next member for the contact positions */
  contactLocation.next =  currentPosition + secondaryByteCounter;

  /* We now write the contact location information now */
  fwrite(&contactLocation, sizeof(struct contact), 1 , fp);

 
  /* Then we write each of the actual contact information sequentially */
  if(contactLocation.first_name_posn != 0)
  {
    /* Writing first name into the file */
    fwrite(contactInformation.firstName, strlen(contactInformation.firstName) + 1, 1, fp);
  }

  if(contactLocation.last_name_posn != 0)
  {
    /* Writing last name into the file */
    fwrite(contactInformation.lastName, strlen(contactInformation.lastName) + 1, 1, fp);
  }

  if(contactLocation.company_name_posn != 0)
  {
    /* Writing company name into the file */
    fwrite(contactInformation.companyName, strlen(contactInformation.companyName) + 1, 1, fp);
  }

  if(contactLocation.email_posn != 0)
  {
    /* Writng email into the file */
    fwrite(contactInformation.email, strlen(contactInformation.email) + 1, 1, fp);
  }
 
}

/******
 checkPhoneNumber: Takes in the phone number information and checks if its between 7 and 10 digits and is numeric
 In: char phoneNumber
 Out: int
 Post: It will return a 0 if it does not meet the requirements and a 1 if it does
 *******/
int checkPhoneNumber(char phoneNumber[])
{
  /* Gets the length of the phoneNumber */
  int lengthOfPhoneNumber;
  lengthOfPhoneNumber = strlen(phoneNumber) - 1;
  int returnVal = 0;
  /* Checks if its between 7 or 10 digits long*/
  if (lengthOfPhoneNumber == 7 || lengthOfPhoneNumber == 10)
  {
    returnVal = 1;
  }

  int i;
  /* Checks through each character to ensure that they are numeric */
  for(i = 0; i < lengthOfPhoneNumber; i++)
  {
    if(isdigit(phoneNumber[i]) == 0)
    {
      returnVal = 0;
    }
  }
  /* If the string passes through both tests, it will reach here and return 1 for success */
  return returnVal; 
}

/******
 checkEmailAddress: Takes in the email address and checks if it follows the correct format with both a domain and TLD
 In: char emailAddress
 Out: int
 Post: It will return a 0 if it does not meet the requirements and a 1 if it does
 *******/
int checkEmailAddress(char emailAddress[])
{
  /* We get the length of email address to iterate with */
  int lengthOfEmail = strlen(emailAddress);
  /* It is valid for them to enter nothing for email as well and this if statement catches that case */
  if(lengthOfEmail == 0)
  {
    return 1;
  }
  /* Counter variables to use for loop, and to count for the number of @ and . */
  int i;
  int atCount;
  atCount = 0;
  int periodCount;
  periodCount = 0;
  /* For Loop to iterate through the length of the email */
  for(i = 0; i < lengthOfEmail; i++)
  {
    /* If our current character is an & and it's not at the begining or end of the email, then we increment @ count */
    if(emailAddress[i] == '@' && i != 0 && i != lengthOfEmail - 1)
    {
      atCount++;
    }

    /* If our current character is a . , @ has already been seen, the . is not at the end of the email and there is a 
       character between the @ and . , then we increment . */
    if(emailAddress[i] == '.' && atCount != 0 && emailAddress[i-1] != '@' && i != 0 && i != lengthOfEmail - 1)
    {
      periodCount++;
    }
  }

  /* If we have a single @ and period count is greater than 0 then we know that we have a valid format for the email address */
  if(atCount == 1 && periodCount != 0)
  {
    /* We return 1 on success for a proper email format */
    return 1;   
  }
  else
  {
    /* We return 0 on failure for a proper email format */
    return 0;
  }
}

/******
 compare_names: Takes in 2 void pointers and type casts them to check the last/company name to sorted them alphabetically
 In: const void *a, const void *b
 Out: int
 Post: Returns the strcmp between the last/company name of the 2 elements 
 *******/
int compare_names(const void *a, const void *b)
{
  /* We type cast our void pointers into pointers to our structure that contains the user's info */
  struct contactInfo *first = (struct contactInfo*)a;
  struct contactInfo *second = (struct contactInfo*)b;


  /* If last name is present for both elements then we go here */
  if((strlen(first->lastName) != 0) && (strlen(second->lastName) !=0))
  {
    return (strcmp(first->lastName, second->lastName));
  }
  /* If last name is not present for the first element but is present for the second element */
  if((strlen(first->lastName) == 0) && (strlen(second->lastName) !=0))
  {
    return (strcmp(first->companyName, second->lastName));
  }
  /* If last name is not present for the second element but is present for the first element */
  if((strlen(second->lastName) == 0) && (strlen(first->lastName) != 0))
  {
    return (strcmp(first->lastName, second->companyName));
  }
  /* If both elements do not have a last name then we go here and compare the company names */
  if((strlen(first->lastName) == 0) && (strlen(second->lastName) == 0))
  {
    return (strcmp(first->companyName, second->companyName));
  }

  return 1;
    
}

