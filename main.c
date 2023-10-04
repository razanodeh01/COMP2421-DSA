//Razan Abdelrahman - 1200531
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WIDTH 5
#define MAX_WIDTH2 7



//The structure of passenger node.
struct passengerNode
{
    int ID,Date;//ID&Date.
    char time[6], DestFrom [50], DestTo[50];//Time-DestinationFrom-DestinationTo.
    struct passengerNode * Next;//Pointer to next passenger.
};


//The structure of bus node.
struct busNode
{
    int busNum,Date,price,capacity;//Bus number-Date-Price-Capacity.
    char time[6],DestFrom [50], DestTo[50];//Time-DestinationFrom-DestinationTo.
    struct busNode * NextBus ;//Pointer to next bus.
    struct passengerNode * Next;//Pointer to next passenger.
};


//Functions definition.
void Menu();


//Functions related to buses linked list.
void LoadBusInfo(struct busNode* B);
void InsertBusNode (struct busNode*, char * []);
struct busNode* makeEmptyB ( struct busNode*);
void DeleteBusesList (struct busNode*);
int IsEmptyB (struct busNode*);
int IsLastB(struct busNode*, struct busNode*);
struct busNode* FindPreviousB (struct busNode*, int);
void PrintBussesList (struct busNode*);
struct busNode* FindBus (struct busNode*, int);
void PrintBusWithPassengers (struct busNode*);
int GetSize (struct busNode*);



//Functions related to passengers linked list.
void LoadPassengerInfo(struct passengerNode*);
void InsertPassengerNode (struct passengerNode*, char * []);
struct passengerNode* makeEmptyP ( struct passengerNode*);
void DeletePassengersList (struct passengerNode*);
int IsEmptyP (struct passengerNode*);
struct passengerNode* Find (struct passengerNode*, int);
int IsLastP(struct passengerNode*, struct passengerNode*);
struct passengerNode* FindPreviousP(struct passengerNode*, int );
void PrintPassengersList (struct passengerNode*);



//Functions related to both buses & passengers
int NewIsLast (struct busNode*, struct passengerNode * );
void AddPassengerToBus (struct busNode*, struct passengerNode*);
void AssignPassengeresToBusses(struct busNode*, struct passengerNode*,struct passengerNode*);
void DeletePassenger(struct busNode*,struct passengerNode* );
struct passengerNode* NewFindPervious (struct busNode* , int );
void DeleteBus(struct busNode* , struct passengerNode* );
void AddNewPassengers (struct busNode*,struct passengerNode* );
void AssignUnmatched (struct busNode*, struct passengerNode *, struct passengerNode*);
void InsertIntoUnmatched (struct passengerNode *, struct passengerNode*);


int main()
{
    char option[2];//Create a temporary variable.

    struct passengerNode* P;//Create the head of the passengers linked list.
    P =(struct passengerNode*)malloc(sizeof(struct passengerNode));
    P->Next=NULL;
    P = makeEmptyP(NULL);//Make sure that the linked list is empty.

    struct busNode* B;//Create the head of the buses linked list.
    B =(struct busNode*)malloc(sizeof(struct busNode));
    B->NextBus=NULL;
    B = makeEmptyB(NULL);//Make sure that the linked list is empty.


    struct passengerNode* Unmatched;//Create the head of the unmatched passengers linked list.
    Unmatched = (struct passengerNode*)malloc(sizeof(struct passengerNode));
    Unmatched->Next=NULL;
    Unmatched = makeEmptyP(NULL);//Make sure that the linked list is empty.


    // Do-While loop unless the user did not select 9th option.
    do
    {
        Menu();//Call the menu function to print options for user.
        printf("Option number:\n");
        scanf("%s",option);//Scan the option number.
        if(strlen(option)>1) // Make sure that the user enter a valid number.(option number from one digit).
                strcpy(option,"0");
        else
        {
            switch(atoi(option))//To know which option the user enter.
            {
            case 1://if option 1 selected.
                LoadBusInfo(B);
                break;
            case 2://if option 2 selected.
                LoadPassengerInfo(P);
                break;
            case 3://if option 3 selected.
                AssignPassengeresToBusses(B,P,Unmatched);
                break;
            case 4://if option 4 selected.
                PrintBusWithPassengers(B);
                break;
            case 5://if option 5 selected.
                {
                    if(Unmatched->Next==NULL)
                        printf("Please select other options to assign passengers to their buses and then found the unmatched passengers.\n\n");
                    else
                        PrintPassengersList(Unmatched);
                }

                break;
            case 6://if option 6 selected.
                   AddNewPassengers(B,Unmatched);
                break;
            case 7://if option 7 selected.
                DeletePassenger(B,Unmatched) ;
                break;
            case 8://if option 8 selected.
                DeleteBus(B,Unmatched);
                break;
            case 9://if option 9 selected.
                break;
            default :
                printf("Sorry ! But option number should be from 1-9.\n");
            }
        }

    }
    while(atoi(option) != 9);

    return 0;
}

// A menu contain the available operations in this program.
void Menu ()
{
    printf("************************************************* Menu ********************************************************");
    printf("\n Please enter an option you would to run it from this menu :");
    printf("\n 1. Load the bus information file.");
    printf("\n 2. Load the passenger information file.");
    printf("\n 3. Assign passengers and print assignment information of all busses.");
    printf("\n 4. Print a specific bus information along with its passengers information (names and IDs).");
    printf("\n 5. Print unmatched passengers.");
    printf("\n 6. Add new passenger.");
    printf("\n 7. Delete passenger.");
    printf("\n 8. Delete bus number.");
    printf("\n 9. Exit. \n");

}


//A method to read the information about buses from the file and load them into linked list.
void LoadBusInfo (struct busNode*B)
{
    char *t[MAX_WIDTH];
    char line[50];//Declare an array of characters to save every line in it.
    FILE *ftp_in ;//Make pointer to the buses file.
    ftp_in=fopen("busses.txt","r");//The mood of the operation on this file is just reading.
    if(ftp_in != NULL)//Check if the file is empty.
    {
        while(fgets(line,sizeof(line),ftp_in))//Make sure that it will read all lines.
        {
            line[strlen(line)-1]='\0';
            char *token ;
            token = strtok (line,"#");//Split the lines into tokens.
            t[0] = token;//First token will be the bus number.
            token = strtok (NULL,"#");
            t[1] = token;//Second token will be the Date.
            token = strtok (NULL,"#");
            t[2]=token;//Third token will be the time.
            token = strtok (NULL,"#");
            t[3]=token;//Fourth token will be the Destination (From).
            token = strtok (NULL,"#");
            t[4]=token;//Fifth token will be the Destination (To).
            token = strtok (NULL,"#");
            t[5]=token;//Sixth token will be the price.
            token = strtok (NULL,"#");
            t[6]=token;//Seventh token will be the capacity of the bus.

            InsertBusNode(B,t);//Pass the array to make node from it and insert the node into the buses linked list.
        }

        printf("\n");
        printf("The operation of reading the buses file is DONE , and buses's information were loaded into linked list.\n\n");
        fclose(ftp_in);//Close the file.

    }
    else // if the file is empty or there's no near file in this name.
        printf("\nError ! File is empty\n\n !");

    PrintBussesList(B);
}

// A routine to add a new node to buses linked list.
void InsertBusNode (struct busNode* B, char *temp[7])
{
    struct busNode* node= (struct busNode*)malloc(sizeof(struct busNode));//Create the node and reserve a space for it.
    node->NextBus=NULL;

    //Assign values to the contents of the each node.
    node->busNum=atoi(temp[0]);
    node->Date=atoi(temp[1]);
    strcpy(node->time,temp[2]);
    strcpy(node->DestFrom,temp[3]);
    strcpy(node->DestTo,temp[4]);
    node->price=atoi(temp[5]);
    node->capacity=atoi(temp[6]);
    node->Next=NULL;
    node->NextBus=NULL;

    if(B!=NULL && node!=NULL)//Make sure that the linked list && the node have  been created.
    {
        struct busNode* t;//Create a temporary node .
        t=B;//Make the temporary node points to the linked list.
        while (t->NextBus != NULL)//Check if its reach to the end of list.
        {
            t=t->NextBus;// if not , move the pointer to next node.
        }
        t->NextBus=node;//After reaching the last node, change the pointers to insert the node.
        node->NextBus=NULL;//Make the last node in the list points to NULL.
    }
    else//Printing this to user if the linked list is NULL.
        printf("Error ! There's no linked list to insert a node in it or the node is NULL!");
}


//A routine to Make the linked list empty.
struct busNode* makeEmptyB ( struct busNode* B)
{
    if(B!= NULL)//if not empty..
        DeleteBusesList(B); // Call function to delete the Linked List as a data and as a structure.

    B=(struct busNode*)malloc (sizeof(struct busNode));
    if(B==NULL)//If b still null so its out of memory.
        printf("Error ! Out of memory , the memory is full!");// Printing this error message ,if there is no place for the Linked List.

    B->NextBus=NULL;//Make the next pointer points to null in order to make sure that the linked list is empty.
    return B;
}


//A routine to delete all its elements(to make sure that the linked list is empty before insert any node).
void DeleteBusesList (struct busNode* B)
{
    struct busNode* temp1, *temp2;//Create temporary pointers.
    temp1=B->NextBus;//Make the temporary node points to the first node in the buses linked list.
    B->NextBus=NULL;

    while (B!=NULL)//Check if the pointer reach the end.
    {
        temp2=temp1->NextBus;
        free(temp1);
        temp1=temp2;
    }
}


//A boolean function to Check if the linked list is empty or not
int IsEmptyB (struct busNode* B)
{
    //If the next of the head points to null, then there is no nodes in this linked list.
    return B->NextBus==NULL; //0 if it has a next node, 1 if there is no next node

}



//A method to print the contents of passengers linked list.
void PrintBussesList (struct  busNode* B)
{
    struct busNode* temp=B;
    if(IsEmptyB(B))//Check if the linked list empty.
        printf("Error! The linked list is empty , you should select option number 1 first.!");//If is, print this error message for the user.
    else
    {
        printf("The buses list :\n");
        do
        {

            temp=temp->NextBus;//Make the pointer points to the first node in linked list.
            printf("\n");
            printf("%d\t",temp->busNum);//Print the contents of each node.
            printf("%d\t",temp->Date);
            printf("%s\t\t",temp->time);
            printf("%s\t\t",temp->DestFrom);
            printf("%s\t\t",temp->DestTo);
            printf("%d\t\t",temp->price);
            printf("%d\t",temp->capacity);


        }//Check that we didn't reach the last node, in order to not make the pointer points to NULL.
        while(!IsLastB(B,temp));
        printf("\n");

    }

}


//****************************************************************************************************************************


//A method to read the information from passengers file.
void LoadPassengerInfo(struct passengerNode* P)
{
    FILE *ftp_in ;//Make a pointer to input file.
    ftp_in=fopen("passengers.txt","r");//The mode in this file will be just reading information.
    char line [50];
    char *t[MAX_WIDTH2];
    if(ftp_in != NULL)//Check if the file is empty.
    {
        while(fgets(line,sizeof(line),ftp_in))//Make sure that it will read all lines.
        {
            line[strlen(line)-1]='\0';
            char *token ;//After reading the line , it has been split according to specific token.
            token = strtok(line,"#");
            t[0]=token;//First token will be the ID.
            token = strtok(NULL,"#");
            t[1]=token;//Second token will be the Date.
            token = strtok(NULL,"#");
            t[2]=token;//Third token will be the time.
            token = strtok(NULL,"#");
            t[3]=token;//Fourth token will be the Destination (From).
            token = strtok(NULL,"#");
            t[4]=token;//Fifth token will be the Destination (TO).
            InsertPassengerNode(P,t);//Pass the node to insert it into the passenger list.
        }
        printf("\n");
        printf("The operation of reading a file is DONE , and passenger's information were loaded in linked list.\n\n");
        fclose(ftp_in);//Close the file.
    }
    else
        printf("\nError ! File is empty \n\n!");//Printing this if the file is empty or is not exist.

    PrintPassengersList(P);

}


// A routine to add a new node to passengers linked list.
void InsertPassengerNode (struct passengerNode* P, char *temp[5])
{
    struct passengerNode* node = (struct passengerNode*)malloc(sizeof(struct passengerNode));//Reserve a space for the node.
    node->Next=NULL;

    //Assign values to the contents of each node.
    node->ID=atoi(temp[0]);
    node->Date=atoi(temp[1]);
    strcpy(node->time,temp[2]);
    strcpy(node->DestFrom,temp[3]);
    strcpy(node->DestTo,temp[4]);


    if(P!=NULL && node!=NULL)//Make sure that the linked list && the node have  been created.
    {
        struct passengerNode* t;//Create a temporary node .
        t=P;//Make the temporary node points to the linked list.
        while (t->Next != NULL)//Check if its reach to the end of list.
        {
            t=t->Next;// if not , move the pointer to next node.
        }
        t->Next=node;//After reaching the last node, change the pointers to insert the node.
        node->Next=NULL;//Make the last node in the list points to NULL.
    }
    else//Printing this to user if the linked list is NULL.
        printf("Error ! There's no linked list to insert a node in it or the node is NULL!");
}


//A routine to Make the linked list empty.
struct passengerNode* makeEmptyP ( struct passengerNode* P)
{
    if(P!= NULL)//if not empty..
        DeletePassengersList(P); // Call function to delete the Linked List as a data and as a structure.

    P=(struct passengerNode*)malloc (sizeof(struct passengerNode));
    if(P==NULL)//If p still null after malloc operation , so there's no space in memory.
        printf("Error ! Out of memory , the memory is full!");// Printing this error message ,if there is no place for the Linked List.

    P->Next=NULL;
    return P;
}


//A routine to delete all its elements(to make sure that the linked list is empty before insert any node).
void DeletePassengersList (struct passengerNode* P)
{
    struct passengerNode* temp1, *temp2;//Create temporary pointers.
    temp1=P->Next;//Make the temporary node points to the first node in the passenger linked list.
    P->Next=NULL;

    while (P!=NULL)//Check if the pointer reach the end.
    {
        temp2=temp1->Next;
        free(temp1);
        temp1=temp2;
    }
}


//A boolean function to Check if the linked list is empty or not.
int IsEmptyP (struct passengerNode* P)
{
    //If the next of the head points to null, then there is no nodes in this linked list.
    return P->Next==NULL; //0 if it has a next node, 1 if there is no next node.

}


//A routine to check if this node is the last or not.
int IsLastP(struct passengerNode* P, struct passengerNode* temp)
{
    return temp->Next == NULL;//If the node in the linked list points to null , so its last.
}


//A method to return the previous passenger of specific passenger.
struct passengerNode* FindPreviousP(struct passengerNode* b, int id)
{
    struct passengerNode* t;//Create temporary passenger.
    t=b;//Make it points to the head of list.
    while(t->Next != NULL && t->Next->ID != id)//Check these conditions.
        t=t->Next;//Move the pointer.
    return t;//Return the pointer of node.
}


//A method to print the contents of passenger's linked list.
void PrintPassengersList (struct passengerNode* P)
{
    struct passengerNode* temp=P;
    if(IsEmptyP(P))//Check if the linked list is empty.
        printf("Error! The linked list is empty , you should select option number 2 first !");//Printing this if the linked list is empty.
    else
    {
        printf("The passengers list :\n");
        do
        {
            temp=temp->Next;//Move the pointer in order to points to first node in the linked list.
            printf("\n");
            printf("%d\t",temp->ID);//Printing passenger's information.
            printf("%d\t",temp->Date);
            printf("%s\t",temp->time);
            printf("%s\t\t",temp->DestFrom);
            printf("%s\n",temp->DestTo);

        }
        while(!IsLastP(P,temp));//Check if the pointer reach the last node in order to not make the node points to NULL.
        printf("\n");
    }


}


//****************************************************************************************************************************

//A method to add passenger to specific bus after satisfying all conditions.
void AddPassengerToBus (struct busNode* temp1, struct passengerNode* temp2)
{
    if (temp1 != NULL && temp2 != NULL)//Check that neither bus or the node is null.
    {
        struct passengerNode* p;//Create a temporary bus node points to the passengers in the bus.
        p=temp1->Next;
        if(p==NULL)//If p equal null , then the linked list is empty , so the node will be inserted directly.
        {
            temp1->Next=temp2;//Change the pointers to include the node.
            temp2->Next=NULL;
        }
        else
        {
            while (p->Next != NULL)//Check if the pointer reach the end of the linked list.
                   p=p->Next;//Move the pointer until it reach the end.

            p->Next=temp2;//If the pointer reach to the end of linked list , then the node(passenger will be inserted).
            temp2->Next=NULL;
        }
    }
    else
        printf("Error ! Either the bus is NULL or the node.");//Printing this if one of the parameters is NULL.
}


//A routine to print the information of all buses after assigning passengers to it.
void PrintAllBusesInfromation (struct busNode*B)
{
    if (IsEmptyB(B))//Check if the linked list is empty.
        printf("Error ! You should select 1 & 2 options to load the informations then make assign between them!\n\n");//Printing this if is.

    else
    {
        struct passengerNode* temp1;//Create a temporary pointer to passengers node.(To move on each passenger in the bus).
        struct busNode* temp2;//Create a temporaries pointers to buses nodes .

        temp2 = B->NextBus;//Make the pointer points to the first bus.

        while(temp2 != NULL)//Check if we reach the end of the buses linked list.
        {
            printf("\n");
            printf("Bus information : Bus Number:%d\tDate:%d\tTime:%s\tDestination From:%s\t",temp2->busNum,temp2->Date,temp2->time,temp2->DestFrom);
            printf("Destination To:%s\t price of ticket:%d\tCapacity:%d\n\n",temp2->DestTo,temp2->price,temp2->capacity);
            temp1=temp2->Next;//Make the pointer points to the first passenger in the first bus.

            if(temp1 == NULL)//Check if this bus is empty.
                printf("No Passengers in this Bus.\n\n");
            else
            {//If not start printing the information of the passengers in each bus.
                printf("The information of it's passengers :\n");
                while(temp1 != NULL)//Check if we reach the end of the passenger's linked list in the bus.
                {
                    printf("%d.\n",temp1->ID);
                    temp1=temp1->Next;//Move the pointer to the next passenger.
                }
            }
            printf("                                       -------------------------------------                   \n");
            temp2=temp2->NextBus;//Move the pointer to the next Bus.
        }

    }
}


//A method to assign passengers to buses.
void AssignPassengeresToBusses (struct busNode* B, struct passengerNode * P, struct passengerNode* Unmatched)
{
    if(!IsEmptyB(B) && (!IsEmptyP(P)))//Check if the passenger list or buses list is empty.
    {
        struct busNode* temp1,*t1;//Create a temporary nodes.
        struct passengerNode* temp2,*t2,*t3;
        int count=0;//Create this variable to Know the number of people in each bus.
        temp1=B, temp2=P;
        t2=temp2->Next;
        while (t2 != NULL)//Check if the pointer reach to the end of passengers list.
        {
            t3=t2->Next;
            t1=temp1->NextBus;
            while (t1 != NULL)//Check if the pointer reach to the end of buses list.
            {
                if((t2->Date == t1->Date )&&(strcmp(t2->time,t1->time)==0))//Check if the passengers and buses have the same info.
                {
                    if((strcmp(t2->DestFrom,t1->DestFrom)==0) && (strcmp(t2->DestTo,t1->DestTo)==0))
                    {
                        if(count<t1->capacity)//Check if the bus full or not before adding more passengers.
                        {
                            AddPassengerToBus(t1,t2);
                            ++count;
                        }

                        else//Printing this if the bus full!
                        {
                            printf("Error ! The capacity of the bus is full , you can't add more passengers, he/she will be inserted into the unmatched list!");
                            InsertIntoUnmatched(Unmatched,t2);
                        }
                    }
                }
                t1=t1->NextBus;//Move the pointer to next bus.

            }
            t2=t3;//Move the pointer to next passenger.
        }

        PrintAllBusesInfromation(temp1);//Call the print function , to print the information of both passengers & buses after assign.
        AssignUnmatched(B,P,Unmatched);
    }
    else//Print this error message if any of the two lists are empty.
        printf("Error!You should select 1&2 options to load informations");
}


//A routine to assign unmatched passengers to their linked list.
void AssignUnmatched (struct busNode* B , struct passengerNode * P , struct passengerNode* Unmatched)
{
    if(!IsEmptyB(B) && (!IsEmptyP(P)))//Check if the passenger list or buses list is empty.
    {
        struct busNode*temp1,*t1;//Create a temporary nodes.
        struct passengerNode* temp2,*t2,*t3;
        temp1=B, temp2=P;//One for the head of buses list, and other for the head of passengers list.
        t2=temp2->Next;//One pointer for the passengers in the bus.
        while (t2 != NULL)//Check if the pointer reach to the end of passengers list.
        {
            t3=t2->Next;
            t1=temp1->NextBus;//One pointer for the buses.
            while (t1 != NULL)//Check if the pointer reach to the end of buses list.
            {
                if((t2->Date != t1->Date )&&(strcmp(t2->time,t1->time)!=0))//Check if the passengers does not match any bus.
                {
                    if((strcmp(t2->DestFrom,t1->DestFrom)!=0) && (strcmp(t2->DestTo,t1->DestTo)!=0))
                    {
                        InsertIntoUnmatched(Unmatched,t2);
                    }
                }
                t1=t1->NextBus;//Move the pointer to next bus.

            }
            t2=t3;//Move the pointer to next passenger.
        }
    }
    else//Print this error message if any of the two lists are empty.
        printf("Error!You should select 1&2 options to load informations.\n\n");
}


//A method to insert the nodes in the Unmatched linked list.
void InsertIntoUnmatched (struct passengerNode *Unmatched , struct passengerNode* temp)
{
    if(Unmatched!=NULL && temp!=NULL)//Make sure that the linked list && the node have  been created.
    {
        struct passengerNode* t;//Create a temporary node .
        t=Unmatched;//Make the temporary node points to the linked list.
        while (t->Next != NULL)//Check if its reach to the end of list.
        {
            t=t->Next;// if not , move the pointer to next node.
        }
        t->Next=temp;//After reaching the last node, change the pointers to insert the node.
        temp->Next=NULL;//Make the last node in the list points to NULL.
    }
    else//Printing this to user if the linked list is NULL.
        printf("Error ! There's no linked list to insert a node in it or the node is NULL!");

}


//A routine to print the informations of the passengers in specific bus.
void PrintBusWithPassengers (struct busNode* B)
{
    if(!IsEmptyB(B))//Check if the information were loaded into the linked list.
    {
        int n, i=1; //Ask user to enter the number of the bus.
        printf("Please enter the number of bus you would to see the information of its passengers:");
        scanf("%d",&n);//Scan the number of the bus.
        struct busNode* temp1 ;//Create temporary nodes.
        struct passengerNode *temp2;
        temp1=FindBus(B,n);//Call the find function to find the bus.
        if(temp1==NULL)//Check if the node is null.
            printf("Sorry, but there' no bus match this number.\n\n");//If is print this.
        else//Else, print the information of the passengers.
        {
            printf("\n");
            printf("Bus information : Bus Number:%d\t  Date:%d\t  Time:%s\tDestination From:%s\t",temp1->busNum,temp1->Date,temp1->time,temp1->DestFrom);
            printf("Destination To:%s\t price of ticket:%d\tCapacity:%d\n\n",temp1->DestTo,temp1->price,temp1->capacity);
            temp2=temp1->Next;
            if (temp2==NULL)
                printf("No passengers in this bus.\n");//Printing this if the bus is empty.
            else
            {
                printf("The information of it's passengers :\n");
                while(temp2 != NULL)
                {
                    printf("Passenger %d :",i);//Print the information of each passenger.
                    printf("%d\n",temp2->ID);
                    ++i;
                    temp2=temp2->Next;
                }
                printf("\n");
            }
        }
    }
    else//Print this error message if the list is empty.
        printf("Error!This list is empty , you should select options 1,2&3 to load passengers and buses information and make assign.\n\n");


}


//A method to find a specific bus through its number , if exist return a pointer to this node.
struct busNode* FindBus (struct busNode* B, int number)
{
    struct busNode* temp;//create a pointer to node that will point to the linked list(head).
    temp=B->NextBus;
    while (temp != NULL && temp->busNum != number)//Check if the pointer reach the end of the list or find the needed bus.
    {
        temp=temp->NextBus;
    }
    return temp;
}


//A routine to add new passenger and assign him/her to the buses.
void AddNewPassengers (struct busNode* B, struct passengerNode* Unmatched)
{
    int id,date;
    char time[10],From[25],To[25];
    printf("Please enter the information for the passenger:\n");//Ask user to enter the information of passenger.
    printf("ID (note: must be unique) :");
    scanf("%d",&id);//Scan the id.
    printf("\nDate:");
    scanf("%d",&date);//Scan the date.
    printf("\nTime:");
    scanf("%s",time);//Scan the time.
    fflush(stdin);//Clean the input.
    printf("\nDestination From:");
    gets(From);//Scan destination from.
    printf("\nDestination To:");
    gets(To);//Scan destination to.

    struct passengerNode* node;//Create a node.
    node= (struct passengerNode*)malloc(sizeof(struct passengerNode));//Reserve space for node in memory.
    node->Next=NULL;
    node->ID = id;//Give the contents of the node their values.
    node->Date = date;
    strcpy(node->time,time);
    strcpy(node->DestFrom,From);
    strcpy(node->DestTo,To);


    int size;
    struct busNode* temp,*t;//Create temporary pointers.
    temp=B , t=temp->NextBus;//One points to the head ,and the other for the first bus.
    if (!IsEmptyB(B))//Make sure that the linked list is not empty.
    {
        while(t != NULL)//Check if we reach the last bus in the linked list.
        {
            if(t->Date==node->Date && (strcmp(t->time,node->time)==0))//Check the conditions.
            {
                if((strcmp(t->DestFrom,node->DestFrom)==0)&&(strcmp(t->DestTo,node->DestTo)==0))
                {
                    size=GetSize(t);//Call get size function to know the actual number of passengers in the bus.
                    if(size < t->capacity)//Compare it with the capacity.
                    {
                        AddPassengerToBus(t,node);//If the bus is not full, add the passenger to it.
                        node=NULL;//Make the node equal null.
                        printf("Every thing is DONE! the passenger has been added to one of the buses.\n\n");
                    }
                    else
                    {
                        printf("Sorry! The suitable bus for this passenger is full!\n");//If the bus is full, this message will appear for the user.
                        InsertIntoUnmatched(Unmatched,node);//Then, add the passenger to the unmatched.
                        printf("The passenger has been added to the unmatched list.\n\n");
                    }
                }
            }
            t=t->NextBus;//Move the pointer to next bus.
        }
        printf("\n");

        if (node != NULL)//if the node does not equal null , so there's no bus match with him/her, so it will be inserted in the unmatched.
        {
            node->ID=id;//Give the node values again.
            node->Date=date;
            strcpy(node->time,time);
            strcpy(node->DestFrom,From);
            strcpy(node->DestTo,To);

            InsertIntoUnmatched(Unmatched,node);//Call this function to insert it in the unmatched list.
            printf("Sorry ! There's no bus match this passenger, so he/she has been added to unmatched passenger.\n\n");

        }

    }
    else//Print this error message if the list is empty.
        printf("Error ! You should first select options number 1,2 & 3 to load information and make assign! ");

}


//A method to return the number of passengers in the bus.
int GetSize (struct busNode* b)
{
    int count=0;//Create temporary variable.
    struct passengerNode* temp;//Create temporary pointer.
    temp=b;//Make the pointer points to the head.
    while (temp->Next != NULL)//Check if the pointer reach the end.
    {
        temp=temp->Next;//Move the pointer on the passengers.
        ++count;//Increment the value of the counter.
    }
    return count;//Return the value of the counter.
}


// A routine to Delete a specific passenger in bus.
void DeletePassenger(struct busNode* B, struct passengerNode* Unmatched )
{
    if (!IsEmptyB(B))//Check if the list is empty.
    {
        int id;//Create a variable.
        printf("Please enter the id of the passenger you would to delete him/her:\n");//Ask user to enter the id.
        scanf("%d",&id);//Scan the id.
        struct busNode* temp1,* t1,*t3;//Create temporary pointers.
        struct passengerNode *temp2, *t2;
        temp1=B ;//One for the head.
        t1=temp1->NextBus;//One for the next bus.
        while (t1 != NULL)//Check if the pointer reach the last bus.
        {
            t3=t1->NextBus;//Save the next position to move the pointer.
            t2=t1->Next;//One pointer for the passengers.
            while (t2 != NULL)//Check if we reach the last passenger in the bus.
            {
                if (t2->ID==id)//Compare the id.
                {
                    if (t1->Next==t2)//First case if the node first , change the pointer and delete directly.
                    {
                        struct passengerNode* t;
                        t=t1->Next;
                        t1->Next=t->Next;
                        free(t);
                        printf("The passenger has been deleted.\n\n");//Print this for user to make sure that the passenger
                        //has been deleted.
                        //PrintAllBusesInfromation(B);

                    }
                    //Second case if the passenger is not first one,we need the previous passenger here.
                    else
                    {
                        struct passengerNode* result;
                        result = NewFindPervious(t1,id);//Find the previous node.
                        if (result->Next==NULL)
                            //Print this for user if the passenger not found.
                            printf("Sorry ! This passenger is not exist neither in the buses or in the Unmatched list.\n\n");
                        else
                        {
                            if(!NewIsLast(t1,result))
                            {
                                struct passengerNode* t;
                                t=result->Next;
                                result->Next=t->Next;
                                free(t);
                                printf("The passenger has been deleted.\n\n");//Print this for user to make sure that the passenger
                                //has been deleted.
                                PrintAllBusesInfromation(B);
                            }
                        }

                    }
                }
                t2=t2->Next;//Move the pointer to next passenger.
            }
            t1=t3;//Move pointer to next bus.
        }

        //If the passenger is not in any of buses , then the search operation will be done on the unmatched.
        temp2=Unmatched;
        t2=temp2->Next;
        while (t2 != NULL)
        {
            if(t2->ID==id)
            {
                struct passengerNode* result;
                result = FindPreviousP(temp2,id);

                if(result==temp2)//First case , if the passenger is the first in the unmatched linked list .
                {
                    struct passengerNode* t;
                    t=temp2->Next;
                    temp2->Next=t->Next;
                    free(t);
                    printf("The passenger has been deleted.\n\n");//Print this for user to make sure that the passenger
                    //has been deleted.
                    PrintPassengersList(Unmatched);
                }
                else if(result != temp2)//Second case if is not the first one,(in the middle or end).
                {
                    if(!IsLastP(temp2,result))
                    {
                        struct passengerNode* t;
                        t=result->Next;
                        result->Next=t->Next;
                        free(t);
                        printf("The passenger has been deleted.\n\n");//Print this for user to make sure that the passenger
                        //has been deleted.
                        PrintPassengersList(Unmatched);
                    }
                }
            }
            t2=t2->Next;
        }


    }
    else//Print this error message if the list is empty.
        printf("Error ! You should first select options number 1,2&3 to load information and make assign between them.\n\n ");
}


//A routine to check if the passenger is the last in this Bus.
int NewIsLast (struct busNode* b, struct passengerNode * p)
{
    return p->Next==NULL;//return 1 if the node is last one, and 0 if not.structg
}


//A method to find the previous of a specific passenger in specific bus.
struct passengerNode* NewFindPervious (struct busNode* b, int id)
{
    struct passengerNode* temp;//Create a temporary node .
    temp=b->Next;//Make it points to the passenger.
    while (temp->Next != NULL && temp->Next->ID != id)//Start checking on passengers or if the pointer reach the end before finding the passenger.
        temp=temp->Next;//Move the pointer.

    return temp;

}


//A routine to delete a specific bus
void DeleteBus (struct busNode* B , struct passengerNode* Unmatched)
{
    if(!IsEmptyB(B))//Check if the list of buses is empty or not.
    {
        int num;//Ask user to enter the number of bus.
        printf("Please enter the number of bus you would to delete it:\n");
        scanf("%d",&num);//Scan the number .

        struct busNode *temp1, *temp2;//Create temporary pointers.
        struct passengerNode* t;
        temp1 = FindPreviousB(B,num);//Call the find previous function to find the previous node .

        if (temp1->NextBus != NULL)
        {
            t=temp1->NextBus->Next;//Make the pointer points to the passenger in the bus.(in order to not lose them).
            if(t==NULL)//Print this ,if there's no passengers in the bus.
                printf("No passengers in the bus, it will be deleted without adding any passengers to the unmatched list.\n\n");
            else
            {
                struct passengerNode* p,*temp;//Create temporary pointer.
                p=t;//Make it points to the passengers in the bus.
                while (p != NULL)//Check if we reach the end of the linked list.
                {
                    temp=p->Next;
                    InsertIntoUnmatched(Unmatched,p);//Insert each node in the unmatched list.
                    p=temp;//Move the pointer to next passenger.
                }
                printf("The passengers have been added to the unmatched list.\n\n");
            }

        }


        if (temp1->NextBus == NULL)//Check if the bus exist.
            printf("Sorry !But this bus is not exist !\n\n");//If not,print this error message.


        else if (temp1==B)//Check if the bus is the first bus in the list.
        {
            struct busNode* t;
            t=temp1->NextBus;
            temp1->NextBus=t->NextBus;//Make connection between the head and the next bus of the bus will be deleted.
            free(t);//Delete the bus.
            printf("Buses after delete one of them:\n");
            PrintAllBusesInfromation(B);//Call function print to make sure that bus has been deleted.
            printf("\n");

        }

        else//If is , start the deletion operation.
        {
            if(!IsLastB(B,temp1))
            {
                temp2 = temp1->NextBus;
                temp1->NextBus = temp2->NextBus;
                free(temp2);
                printf("Buses after delete one of them:\n");
                PrintAllBusesInfromation(B);//Call function print to make sure that bus has been deleted.
                printf("\n");
            }
        }
    }
    else//If the linked list is empty, the user should select other options.
        printf("Error ! You should select 1,2 & 3 options to load information and make assign.\n\n");
}


//A method to find the previous of specific node according to the number of bus.
struct busNode* FindPreviousB (struct busNode* B, int n)
{
    struct busNode* temp;//Create temporary pointer.
    temp=B;//Make it points to the head.
    while (temp->NextBus != NULL && temp->NextBus->busNum != n)//Check these conditions.
        temp=temp->NextBus;//Move the pointer.

    return temp;//Return the node.
}


//A routine to check if this bus is the last in the buses list or not.
int IsLastB(struct busNode* B, struct busNode* temp)
{
    return temp->NextBus == NULL;//If the node in the linked list points to null , so its last.
}
