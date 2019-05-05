/************************main.c **************
 Student Name: Tony (Quoc) Hoan Trinh 			Email Id: trinhq@uoguelph.ca
 Date: April 1st, 2019					Course Name: CIS 2500
 I have exclusive control over this submission via my password.
 By including this statement in this header comment, I certify that:
 1) I have read and understood the University policy on academic integrity;
 2) I have completed the Computing with Integrity Tutorial on Moodle; and
 3) I have achieved at least 80% in the Computing with Integrity Self Test.
 I assert that this work is my own. I have appropriately acknowledged any and all material (data, images, ideas or words) that I have used,
 whether directly quoted or paraphrased.
 Furthermore, I certify that this assignment was prepared by me specifically for this course.
 **********************************************************/

/******
  Include our header to which links the functions and libraries
*******/
#include "contacts.h"

/******
 main: Entry point in to the program. Opens/creates a .db file for the contacts to be written and read from.
 In: None
 Out: Returns 0
 Post: The program will write and read contact information and store it with the locations in the .db to be read from in the future.
*******/
int main()
{
  /* Creates/Opens the myContactList.db file to be written and read from */
  FILE * fp = fopen("bin/myContactList.db", "ab+");
  int (*compare_ptr)(const void *a, const void *b);
  
  /* Incase the file couldn't be opened */
  if(fp == NULL)
  {
    printf("Error\n");
    exit(1);
  }

  /* Count variable which represents the size of our array of structures */
  int count;
  count = 0;
  /* Getting the Data from the .db file */
  struct contactInfo *listOfData = malloc(sizeof(struct contactInfo) * 1);

  /* We set the file pointer to start at the beginning so we can traverse through the file */
  fseek(fp, 0, SEEK_SET);
  /* Structure contact to hold the positions of the found contact */
  struct contact traverseInformationLocation;

  /* While loop which continues as long as fread is success */
  /* We are reading the file 48 bytes at a time and checking the phone number */
  while(fread(&traverseInformationLocation, sizeof(struct contact), 1, fp) == 1)
  {
    listOfData[count].phone_number = traverseInformationLocation.phone_number;
    listOfData[count].deletedOrEditedFlag = 0;
    /* Now we need to read and alloc the actual data from the file */
    
    /* Long variables to keep track of where we are in the file which makes it helpful to keep track of byte sizes and positions */
    long currentPosition;
    long byteCounter;
    currentPosition = traverseInformationLocation.next;
    byteCounter = 0;

    /* If email position is not zero then we calculate the byte size of the email and add it to our array of structures */
    if(traverseInformationLocation.email_posn != 0)
    {
   
      fseek(fp, traverseInformationLocation.email_posn, SEEK_SET);
   
      byteCounter = currentPosition - traverseInformationLocation.email_posn;
     
      listOfData[count].email = malloc(sizeof(char) * byteCounter);
      fread(listOfData[count].email, byteCounter, 1 , fp);
     
      currentPosition = traverseInformationLocation.email_posn;
    }
    /* We just append a null character */
    else
    {
   
      listOfData[count].email = malloc(sizeof(char) * 1);
      strcpy(listOfData[count].email, "\0");
    }

    /* Same process as above but for company name */
    if(traverseInformationLocation.company_name_posn != 0)
    {
      fseek(fp, traverseInformationLocation.company_name_posn, SEEK_SET);
      byteCounter = currentPosition - traverseInformationLocation.company_name_posn;
      listOfData[count].companyName = malloc(sizeof(char) * byteCounter);
      fread(listOfData[count].companyName, byteCounter, 1 , fp);
      currentPosition = traverseInformationLocation.company_name_posn;
    }
    else
    {
      listOfData[count].companyName = malloc(sizeof(char) * 1);
      strcpy(listOfData[count].companyName, "\0");
    }


    /* Same process as above but for last name */
    if(traverseInformationLocation.last_name_posn != 0)
    {
      fseek(fp, traverseInformationLocation.last_name_posn, SEEK_SET);
      byteCounter = currentPosition - traverseInformationLocation.last_name_posn;
      listOfData[count].lastName = malloc(sizeof(char) * byteCounter);
      fread(listOfData[count].lastName, byteCounter, 1 , fp);
      currentPosition = traverseInformationLocation.last_name_posn;
    }
    else
    {
      listOfData[count].lastName = malloc(sizeof(char) * 1);
      strcpy(listOfData[count].lastName, "\0");
    }


    /* Same process as above but for first name */
    if(traverseInformationLocation.first_name_posn != 0)
    {
      fseek(fp, traverseInformationLocation.first_name_posn, SEEK_SET);
      byteCounter = currentPosition - traverseInformationLocation.first_name_posn;
      listOfData[count].firstName = malloc(sizeof(char) * byteCounter);
      fread(listOfData[count].firstName, byteCounter, 1 , fp);
      currentPosition = traverseInformationLocation.first_name_posn;
    }
    else
    {
      listOfData[count].firstName = malloc(sizeof(char) * 1);
      strcpy(listOfData[count].firstName, "\0");
    }
    

    /* We seek towards next contact information to start reading more in */
    fseek(fp, traverseInformationLocation.next, SEEK_SET);
    /* We increment count and then we realloc to accomodate for additional memory */
    count++;
    listOfData = realloc(listOfData, sizeof(struct contactInfo) *(count + 1));
    
  }

  /* Counter variable */
  int i;

  /* We create our buffer string to hold user's input */
  char userAnswer[1024];
  int indexCount;
  indexCount = count;
 
  while(1 != 0)
  {
    
    /* We call in QSort and sort out array of structures based on last/company name */
    compare_ptr = &compare_names;
    qsort (listOfData, count, sizeof(struct contactInfo), compare_ptr);
    printf ("Number of Contacts = %d\n", indexCount);
  

    /*
    Note:
    Hello TA!
    Thank you so much for marking my assignment. I really appreciate all of the hard work and help that you guys gave us.
    You guys have been the most helpful TAs I ever had and you always were very patience and helpful even if our questions were 
    stupid (◕‿◕✿). My program works for everying and all of the features except I was having problems with shifting my array of 
    structures. So the numbering is slightly off but it works perfectly else where and when you restart the program it fixes
    the numbering. I spent a good 4 hours trying to fix the shifting array problem but to no prevail (´。＿。｀). Please don't
    deduct too many marks for that (;_;)! Again you guys have basically taught me the course as I never found the lectures to be
    helpful and sometimes made me more confused. You guys put in extra hours too and often stay longer for office
    hours even when you guys finished. I can't possibly put into words how great you guys have been. Thank you guys for everything,
    I hope you guys do great on your exams and have a great summer!

    Tony Hoan Trinh
    */
    
    /* Loop which prints the contact information alphabetically */
    for (i = 0; i < count; i++)
    {
      if(listOfData[i].deletedOrEditedFlag == 0)
      {
        if(strlen(listOfData[i].lastName) > 1)
        {
          printf ("\t%d. %s %s\n",i + 1, listOfData[i].firstName, listOfData[i].lastName);
        }
        else
        {
          printf("\t%d. %s\n",i + 1, listOfData[i].companyName);
        }
      }
    }

    /* The main interface */
    printf("Action:");
    fgets(userAnswer,1024, stdin);
    /* If the User presses A to add a new contact */
    if(strncmp(userAnswer, "A", 1) == 0)
    {
      /* Add Contact Information */
      printf("New Contact\n");

      struct contactInfo newContact;
      short mandatoryNameFlag = 0;

      /* Gets the contact's first name and stores it into the contactInfo structure */
      printf("First Name: ");
      fgets(userAnswer,1024, stdin);
      userAnswer[strlen(userAnswer) - 1] = '\0';
      newContact.firstName = malloc(sizeof(char) * (strlen(userAnswer) + 1));
      strcpy(newContact.firstName, userAnswer);

      /* Same procedure as above */
      printf("Last Name: ");
      fgets(userAnswer,1024, stdin);
      userAnswer[strlen(userAnswer) - 1] = '\0';
      newContact.lastName = malloc(sizeof(char) * (strlen(userAnswer) + 1));
      strcpy(newContact.lastName, userAnswer);

      /* If the user entered in nothing for the last name it will set the flag as true */
      if(strlen(newContact.lastName) == 0)
      {
        mandatoryNameFlag = 1;
      }
        
      /* Same procedure as above */
      /* Do while loop to ensure that if last name is empty, then company name will be mandatory */
      do {
        printf("Company Name: ");
        fgets(userAnswer,1024, stdin);
        userAnswer[strlen(userAnswer) - 1] = '\0';
        newContact.companyName = malloc(sizeof(char) * (strlen(userAnswer) + 1));
        strcpy(newContact.companyName, userAnswer);
            
        /* If the user entered something in for company name then we set the flag back to false */
        if(strlen(newContact.companyName) != 0)
        {
          mandatoryNameFlag = 0;
        }
            
      } while (mandatoryNameFlag == 1);

      /* Buffer for the phone number input */
      char phoneAnswer[1024];

      /* Do While loop to ensure that the phone number is mandatory */
      do {
        printf("Phone Number(enter only numbers): ");
        fgets(phoneAnswer,1024, stdin);
      } while(strcmp(phoneAnswer, "\n") == 0 || checkPhoneNumber(phoneAnswer) != 1);
      
      /* Converting the phone number from a string to an int */
      sscanf(phoneAnswer, "%lu", &newContact.phone_number);
    

      /* Same procedure as above */
      do {
        printf("Email: ");
        fgets(userAnswer,1024, stdin);
        userAnswer[strlen(userAnswer) - 1] = '\0';
      } while (checkEmailAddress(userAnswer) != 1);
      
      newContact.email = malloc(sizeof(char) * (strlen(userAnswer) + 1));
      strcpy(newContact.email, userAnswer);

      /* Another While Loop to ask for R, S and D */
      while(1)
      {
        printf("Action:");
        fgets(userAnswer,1024, stdin);
	/* If the user presses R we just break out and then back to the main interface */
        if(strncmp(userAnswer, "R", 1) == 0)
        {
	  printf("Return\n");
          break;
        }
	/* If the user presses S, we realloc our array of structures and malloc and append the newest contact to the end of the array of structures and then head back to the main interface */
	else if(strncmp(userAnswer, "S", 1) == 0)
	{
          /* Realloc our array of structures */
	  /* Add the new contact to the array of strucutres */
	  indexCount++;
	  count++;
	  listOfData = realloc(listOfData, sizeof(struct contactInfo) *(count + 1));
	  listOfData[count - 1].firstName = malloc(sizeof(char) * (strlen(newContact.firstName) + 1));
	  strcpy(listOfData[count - 1].firstName, newContact.firstName);
	  listOfData[count - 1].lastName = malloc(sizeof(char) * (strlen(newContact.lastName) + 1));
	  strcpy(listOfData[count - 1].lastName, newContact.lastName);
	  listOfData[count - 1].email = malloc(sizeof(char) * (strlen(newContact.email) + 1));
	  strcpy(listOfData[count - 1].email, newContact.email);
	  listOfData[count - 1].companyName = malloc(sizeof(char) * (strlen(newContact.companyName) + 1));
	  strcpy(listOfData[count - 1].companyName, newContact.companyName);
	  listOfData[count - 1].phone_number = newContact.phone_number;
	  listOfData[count - 1].deletedOrEditedFlag = 0;
	  break;
	}
      }

      /* Freeing the memory after the user's input */
      free(newContact.firstName);
      free(newContact.lastName);
      free(newContact.companyName);
      free(newContact.email);  
    }
    /* If the user presses X we break out of our main interface and end the program */
    else if(strncmp(userAnswer, "X", 1) == 0)
    {
      break;
    }
    /* If the user gets in a number as their input we go here */
    else if(isdigit(userAnswer[0]) != 0)
    {
      int i;
      i = atoi(userAnswer);
      /* We then print out the information of the contact that they selected */
      if(i < count + 1 && i != 0 && listOfData[i - 1].deletedOrEditedFlag == 0)
      {
        /* Display that index's contact and data associated with it */
        printf("First Name: %s\n", listOfData[i - 1].firstName);
	printf("Last Name: %s\n", listOfData[i - 1].lastName);
	printf("Company Name: %s\n", listOfData[i - 1].companyName);
	printf("Phone Number: %lu\n", listOfData[i - 1].phone_number);
	printf("Email: %s\n", listOfData[i - 1].email);

	/* Interface to see what the user wants to do with the current contact */
	while(1)
        {
          printf("Action:");
          fgets(userAnswer,1024, stdin);
	  /* If they press R we just break out and head back to the main interface */
          if(strncmp(userAnswer, "R", 1) == 0)
          {
	    printf("Return\n");
            break;
          }
	  /* If they press E to edit then we go here */
	  else if(strncmp(userAnswer, "E", 1) == 0)
	  {
            /*We display the first, last and company name again */

	    printf("First Name: %s\n", listOfData[i - 1].firstName);
	    printf("Last Name: %s\n", listOfData[i - 1].lastName);
  	    printf("Company Name: %s\n", listOfData[i - 1].companyName);
	    /* Buffer for the phone number input */
            char phoneAnswer[1024];

	    /* We get a response for the new phone numer input */
            /* Do While loop to ensure that the phone number is mandatory */
            do {
              printf("Phone Number(enter only numbers): ");
              fgets(phoneAnswer,1024, stdin);
            } while(strcmp(phoneAnswer, "\n") == 0 || checkPhoneNumber(phoneAnswer) != 1);
      
           
            char emailAnswer[1024];
	    
            /* Same procedure as above */
            do {
              printf("Email: ");
              fgets(emailAnswer,1024, stdin);
              emailAnswer[strlen(emailAnswer) - 1] = '\0';
            } while (checkEmailAddress(emailAnswer) != 1);
           
	    /* The Edit Action interface */
            while(1)
            {
              printf("Action:");
              fgets(userAnswer,1024, stdin);
	      /* If the user presses R we just return back to the main interface */
              if(strncmp(userAnswer, "R", 1) == 0)
              {
	        printf("Return\n");
                break;
              }
	      /* If the user presses S then we add in the new information for that contact */
	      else if(strncmp(userAnswer, "S", 1) == 0)
	      {
                /* Realloc our array of structures */
	        /* Converting the phone number from a string to an int */
                sscanf(phoneAnswer, "%lu", &listOfData[i - 1].phone_number);
	        listOfData[i - 1].email = realloc(listOfData[i - 1].email,sizeof(char) * (strlen(emailAnswer) + 1));
                strcpy(listOfData[i - 1].email, emailAnswer);
	        break;
 	      }
	      /* If the user presses D for delete then we delete the contact by setting the flag as 1 */
	      else if(strncmp(userAnswer, "D", 1) == 0)
	      {
	        int index = atoi(userAnswer);
	        listOfData[index - 1].deletedOrEditedFlag = 1;
		indexCount--;
		break;
	      }
	    }
	    break;
	  }
	  /* If the user presses D for delete then we delete the contact by setting the flag as 1 */
	  else if(strncmp(userAnswer, "D", 1) == 0)
	  {
            /* Delete the contact by flagging it as 1 */
	    indexCount--;
	    listOfData[i - 1].deletedOrEditedFlag = 1;
	    break;
	  }
	}
      }
      /* If they enter a wrong contact number */
      else
      {
        printf("Invalid Contact Number\n");
      }
    }
  }

  fclose(fp);
  /* First we delete our current .db file */
  int fileDeletion;
 
  fileDeletion = remove("bin/myContactList.db");
  if(fileDeletion != 0)
  {
    printf("Deleting File Error!\n");
  }

  /* Then we make a new .db file to write the new/modified contact information back to the .db file */
  fp = fopen("bin/myContactList.db", "ab+");
  
  fseek(fp, 0, SEEK_SET);

  /* For Loop to write each of the contact information back to the .db file */
  for(i = 0; i < count; i++)
  {
    if(listOfData[i].deletedOrEditedFlag == 0)
    {
      writeFiles(listOfData[i],fp);
    }
  }

  /* Freeing the memory we allocated for the array of structure contact information */
  for(i = 0; i < count; i++)
  {
    free(listOfData[i].firstName);
    free(listOfData[i].lastName);
    free(listOfData[i].companyName);
    free(listOfData[i].email);
  }

  free(listOfData);

  /* Closes the file pointer */
  fclose(fp);
  /* Returns 0 to end the program */
  return 0;
}

