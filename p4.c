#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define numOfArgs 4
#define Flag 1
#define InFileArg 2
#define OutFileArg 3
#define TextArea 1
#define DataArea -1

<<<<<<< HEAD

//KNOWN PROBLEMS: DOES NOT READ COMMENTS, READS LINE AND PRINTS LINE OF IDENTIFIER, BUT ONLY FOR THE ONES IT READS AND NOT ACTUAL LINE
//DOES NOT PARS=


//continues skip the current iteration and goes to the next iteration
=======
>>>>>>> my-temporary-work
//France Le
//FL193361
//LAB: Wed 4:15

<<<<<<< HEAD
//ctrlshift c comments
//ctrlshift x uncomments
//do not store comments when storing into a linked list

//char *array holds a constant string and cannot be modified. only read
//char array[] can be modified

//when parsing


//void tokenizeID(char *, int, struct labels);
//int tokenizeID(char *codeLine, int index, char *strArr[]);





=======
//Holds the labels
>>>>>>> my-temporary-work
    typedef struct labels{
        char identifier[12]; //this will hold one identifier, max length 11
    }label;

//Linked List
    typedef struct Source{
        char line_comment[80];
        char line_nocomment[80];
<<<<<<< HEAD
        int labelType; // if label = VarFlag, then Variable in , label = 1
=======
>>>>>>> my-temporary-work
        struct Source *next;
    }Node;

//PROTOTYPES
Node *newNode(char *comment, char *nocomment);
void insertNode(Node** hptr, Node** tptr, Node *newnodeptr);
void printList(Node *h);
<<<<<<< HEAD
void searchprint(char* target, Node *hptr);

int main(int argc, char *argv[])
{

    Node *head, *tail;
    head = tail = NULL;




//    char *varArrPtr, **flowArrPtr; //pointer to the a string of characters

    //make sure to free the varArrPtr[i] when printing to file.
    //store them using ie varArrPtr[i] = "some_identifier"
//    varArrPtr = malloc(sizeof(char*)*100); //the array is going to hold 100 var labels
//    flowArrPtr = malloc(sizeof(char*)*100); //array holds 100 hold 100 flow control labels

=======
void deleteAll(Node** hptr);
void tokenizeID(char *line, label idlab[], int * indexaddress);
void searchprint(char* target, Node *hptr, FILE *outfileptr);

int main(int argc, char *argv[])
{
    Node *head, *tail;
    head = tail = NULL;
>>>>>>> my-temporary-work
    FILE *infileptr; //pointer to the the input file
    FILE *outfileptr; //pointer to the output file
    //ARG CHECKING
    if(argc != numOfArgs){
        printf("Enter [./executable] [flag: -v,-b,-f][inputfilename] [outputfilename]\n");
        fflush(stdout);
        exit(1);}
    //FLAG CHECKING
    if (strcmp(argv[Flag],"-b") == 0 || strcmp(argv[Flag],"-v") == 0 ||strcmp(argv[Flag],"-f") == 0 ){
        printf("Good job. Correct flag\n");}
    else{
        printf("Please enter a proper flag.\n");
        fflush(stdout);
        exit(1);}

//    //Stores the name of the file

//     IN CASE I WANTED TO ASK FOR JUST THE FILE NAMES
//    char *ip;
//    char *op;
//    ip = (char*)malloc (sizeof(strlen(argv[InFileArg])+5));
//    op = (char*)malloc(sizeof(strlen(argv[OutFileArg])+5));
//    strcpy(ip, argv[InFileArg]);
//    strcpy(op, argv[OutFileArg]);
//    strcpy(ip, "<file extension>";
//    strcpy(op, "<file extension>";


    //ERROR CHECKING FOR OPENING FILES
    if((infileptr = (FILE*)(fopen(argv[InFileArg],"r")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[InFileArg] /*"test.mal"*/);
        fflush(stdout);
        int errnum;
        errnum = errno;
        fprintf(stderr, "Value of errno:%d\n", errno);
        fflush(stdout);
        perror("Error printed by perror.");
        fflush(stdout);
        //printf(stderr,"Error opening file:%s\n", strerror(errnum));
        exit(1);}
    if((outfileptr = (FILE*)(fopen(argv[OutFileArg],"w")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[OutFileArg] /*"newfile.txt"*/);
        fflush(stdout);
        int errnum;
        errnum = errno;
        fprintf(stderr, "Value of errno:%d\n", errno);
        perror("Error printed by perror.");
        //printf(stderr,"Error opening file:%s\n", strerror(errnum));
        exit(1);}

    /////////////////////////////////////////////////////////


    ////////////////////////

    //DATA FIELDS
    char fileLine[81];
    label varLab[100], flowLab[100];                                     // Stores all the identifier
    int section = DataArea;                                             //used to identify which section (.data or .text) to look for identifiers
    int varIndex = 0;
    int flowIndex = 0;
<<<<<<< HEAD


=======
>>>>>>> my-temporary-work

    while(fgets(fileLine,sizeof(fileLine),infileptr)){                  //  loops through each line; each line is stored in fileLine

        if(strstr(fileLine,".text")!= NULL){                             //strstr checks if .text is in the file line. it will be null if there is no match.
            section = TextArea;}
        if (section == DataArea){
<<<<<<< HEAD
            printf("Line %d in data area\n",counter);

            //TOKENIZER//////////////////////////////////////////////////////////////////////////////////////////////
            char *token;
            token = strtok(fileLine," \t ,");                           //grabs the first word of the line
            if(strchr(token, ':')!= NULL){                               //checks the if it contains :
                char *token2;
                token2 = strtok(token, ":");                            //removes the semicolon
                //printf("token is %s\n", token2);
                char temp2[12];
                strncpy(temp2,token2,11);                               //converts string pointer to array of chars
                temp2[11] = '\0';                                       //last char is going to be a null terminated one.
                strcpy(varLab[varIndex].identifier, temp2);
                //printf("this is varlab %s\n", varLab[varIndex].identifier);
                varIndex++;
            }
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////



=======
            tokenizeID(fileLine, varLab, &varIndex);                     //TOKENIZER for Data variables- stores them into an array
>>>>>>> my-temporary-work
        }
//      Section does two things: 1. Puts all Control Flow Labels into its struct array. 2. Stores Original Code, and Non-Commented Code into an array.
        else if (section == TextArea){
<<<<<<< HEAD
            //read the characters in the characters in that string, cut out the comment
            //store the
            printf("Line %d text area\n",counter);
            //CAPTURE LINES OF CODE IN TEXT AREA WITHOUT THE COMMENTS




            char temp[81];

            strncpy(temp,fileLine,79);
            temp[81] = '\0';

            //printf("%s\n%s\n", temp,fileLine);
            char *comtoken;
            char *nocomment;
            if(fileLine[0]=='#'){                                       //Filters lines that start with a comment
                printf("COMMENT ALERT!\n");
                continue;
            }


                comtoken = strtok(fileLine, "#");
                nocomment = comtoken;


            //TOKENIZER////////////////////////////////////////////
            char *token;
            token = strtok(fileLine," \t ,");                           //grabs the first word of the line
            if(strchr(token, ':')!= NULL){                               //checks the if it contains :
                char *token2;
                token2 = strtok(token, ":");                            //removes the semicolon
                //printf("token is %s\n", token2);
                char temp2[12];
                strncpy(temp2,token2,11);                               //converts string pointer to array of chars
                temp2[11] = '\0';                                       //last char is going to be a null terminated one.
                strcpy(flowLab[flowIndex].identifier, temp2);
                //printf("this is flowLab %s\n", flowLab[flowIndex].identifier);
                flowIndex++;
            }//if
            /////////////////////////////////////////////////////////////////////////
=======
            //in this case, I was suggested to use const rather than use a bunch of temp values. Will be updated after project.
            char wholecomment[80];
            char *nocomment;
            char temp[80];
            char *comtoken;
            char tempid[81];
            char idtoken[81];
            char* temp32;


            strcpy(wholecomment,fileLine);                              //stores it in its own array//file line gets modified in the tokenizer
            strcpy(temp, fileLine);
            strcpy(idtoken, fileLine);
            temp32 = strtok(idtoken, " \t");                           //used to ignore any identifiers like .globl or .text
            strcpy(tempid, temp32);


            if(temp[0]=='#' ){                                          //Filters lines that start with a comment
                printf("COMMENT SKIPPED!\n");
                continue;}
            //requires tokenized version of temp because \n and white space
>>>>>>> my-temporary-work

            if(tempid[0] == '.'){                                    //Filters out Control Flow used in identifiers
               printf("IDENTIFIER SKIPPED.\n");
               continue;}

<<<<<<< HEAD
                                       //gets the section before the #, stores it into nocomment
            //printf("%cSourceCode: %s\n",nocomment[0], nocomment);
            //STORE THE FILELINE & NOCOMMENT LINE INTO INSERTFUNCTION TO NODE LIST.
            Node *nodeptr = newNode(temp, nocomment);
            insertNode(&head, &tail, nodeptr);
            printf("this is no comment: %s\n",nocomment);


=======
>>>>>>> my-temporary-work

            comtoken = strtok(temp, "#");
            nocomment = comtoken;                                       //Stores Non-Commented Code into variable
            tokenizeID(fileLine, flowLab, &flowIndex);                  //TOKENIZER - for flow characters; stores flow control chars in array
            Node *nodeptr = newNode(wholecomment, nocomment);           //STORE THE FILELINE & NOCOMMENT LINE INTO INSERTFUNCTION TO NODE LIST.
            insertNode(&head, &tail, nodeptr);

<<<<<<< HEAD

        } //end of text area

        counter++;
=======
        } //end of text area
>>>>>>> my-temporary-work
    }//end of whie loop

//////DEBUGGING: PRINTS OUT ALL IDENTIFIERS
    int i;
    for (i = 0; i < varIndex;i++)
<<<<<<< HEAD
        printf("This is the element %d: %s\n", i, varLab[i].identifier);
    for (i = 0; i < flowIndex;i++)
        printf("This is the element %d: %s\n", i, flowLab[i].identifier);



    for (i = 0; i < varIndex;i++){
        printf("Variable Label -%s-\n",varLab[i].identifier);
        searchprint(varLab[i].identifier, head);
    }

    printf("\n\n\n");

    for (i = 0; i < flowIndex;i++){

        printf("Control Flow Label -%s-\n",flowLab[i].identifier);
        searchprint(flowLab[i].identifier, head);
    }


    //printList(head);

    ////////////////////////////
    /*
    Comparison function:
    Create a Node Structure that holds two lines, line_nocomment, and line_withcomment
    Loop through size of the label struct array until end. Run each element into a search function.
    Search function takes in the head pointer and the member of the label struct array elemnt.
    Compares if whether identifier is found in line_nocomment, if true, prints line_wholeline; else return;

    */

    /*
    PROGRAM NEEDS A INSERT FUNCTION TO ADD IN FILELINE AND NO COMMENT LINE


    */



    ////////////////////////////////









=======
        printf("Variable Labels- element %d: %s\n", i, varLab[i].identifier);
    for (i = 0; i < flowIndex;i++)
        printf("Control Flow- element %d: %s\n", i, flowLab[i].identifier);
///////////////////////FLAG OPTIONS//////////////////////////////////// Could have used a Case Statement
    //BOTH
    if(strcmp(argv[Flag],"-b")==0){
    for (i = 0; i < varIndex;i++){
        fprintf(outfileptr,"Variable Label -%s-\n",varLab[i].identifier);
        searchprint(varLab[i].identifier, head, outfileptr);}
    printf("\n\n");
    for (i = 0; i < flowIndex;i++){
        fprintf(outfileptr, "Control Flow Label -%s-\n",flowLab[i].identifier);
        searchprint(flowLab[i].identifier, head, outfileptr);}
    }
    //JUST VARIABLES
    if(strcmp(argv[Flag],"-v")==0){
        for (i = 0; i < varIndex;i++){
        fprintf(outfileptr,"Variable Label -%s-\n",varLab[i].identifier);
        searchprint(varLab[i].identifier, head, outfileptr);}
    }
    //JUST CONTROL FLOW
    if(strcmp(argv[Flag],"-f")==0){
    for (i = 0; i < flowIndex;i++){
        fprintf(outfileptr, "Control Flow Label -%s-\n",flowLab[i].identifier);
        searchprint(flowLab[i].identifier, head, outfileptr);}
    }
    //LINKED LIST DEBUGGER//////////////////////////////////////////////////
    //printList(head);
>>>>>>> my-temporary-work

    //Closes both files and deallocates all memory
    if(fclose(infileptr) == EOF){
        int errnum;
        errnum = errno;
        fprintf(stderr, "Value of errno:%d\n", errno);
        fflush(stdout);
        perror("Error printed by perror.");
        fflush(stdout);
        //fprintf(stderr,"Error closing file:%s\n", strerror(errnum));
        fflush(stdout);
        printf("Error in closing input file.");
        fflush(stdout);}
    if(fclose(outfileptr) == EOF){
        int errnum;
        errnum = errno;
        fprintf(stderr, "Value of errno:%d\n", errno);
        fflush(stdout);
        perror("Error printed by perror.");
        fflush(stdout);
        //fprintf(stderr,"Error closing file:%s\n", strerror(errnum));
        printf("Error in closing output file.");
        fflush(stdout);}
    deleteAll(&head);                                   //removes all nodes
    printList(head);                                    //Debugging tool; Checks that all lines are copied correctly into the linked list
//    free(ip);                                           //Deallocates memory from file pointer names
//    free(op);
    return 0;
}

//FUNCTION: Stores all identifier labels into corresponding struct array
//PARAM: Passes the source code line, the struct array storing the label, and the pointer to the index for that array.
//NOTE: The raw code is below everything
void tokenizeID(char *line, label idlab[], int * indexaddress){
    char *token;
    token = strtok(line," \t ,");                           //grabs the first word of the line
    if(strchr(token, ':')!= NULL){                               //checks the if it contains :
        char *token2;
        token2 = strtok(token, ":");                            //removes the semicolon
        char temp2[12];
        strncpy(temp2,token2,11);                               //converts string pointer to array of chars
        temp2[11] = '\0';                                       //last char is going to be a null terminated one.
        strcpy(idlab[(*indexaddress)].identifier, temp2);
        (*indexaddress)++;}
} //END OF TOKENIZE

//FUNCTION: Creates a new node that contains source code of label; Text stored in the new Node is going to be after .text
//PARAM: Stores Original line, and line without comments
Node *newNode(char *comment, char *nocomment){
    Node* newNode = (Node*) malloc(sizeof(Node)); //allocates memory for new node
    strcpy(newNode->line_comment, comment);
    strcpy(newNode->line_nocomment, nocomment);
    newNode->next = NULL;
    return newNode;
}

//FUNCTION: Stores the source code into linked list, inserts new code at end
//PARAM: Head node pointer, tail pointer, new node pointer
void insertNode(Node** hptr, Node** tptr, Node *newnodeptr){
    Node * curr = *hptr;
    if(*hptr == NULL){
        newnodeptr->next = *hptr;
        *hptr = newnodeptr;
        *tptr = newnodeptr;
        return;}//if
    else{
        curr = *hptr;
        while (curr!=NULL){
            if (*hptr == *tptr){
                *tptr = newnodeptr;
                (*hptr)->next = newnodeptr;
                fflush(stdout);
                return;}
            else if(curr == *tptr){
                (*tptr)->next = newnodeptr;
                *tptr = newnodeptr;
                fflush(stdout);
                return;}
            curr = curr->next;
        }//while
    }//else
}//insert funct


//FUNCTION: USED FOR DEBUGGING. Checks prints out Original Source Code and Source Code without Comments, line by line.
//PARAM: Head pointer to the linked list
void printList(Node *h){
    Node *curr = h;
    if (curr == NULL){
        printf("List is empty.\n");
        fflush(stdout);}
    else{
        printf("The list is:\n");
        int i = 0;
        while (curr!= NULL){
            printf("Line with comment %d: %s\n", i, curr->line_comment);
            fflush(stdout);
            printf("Line wout comment %d: %s\n", i, curr->line_nocomment);
            fflush(stdout);
            curr = curr->next;
            i++;}
            }//else
} //end of print


//FUNCTION: passes the member of the array, checks the nocomment line, and prints out the source code
//PARAM: Passes the identifier in an array, the head pointer to the linked list
void searchprint(char* target, Node *hptr, FILE *outfileptr){
    Node *curr = hptr;
    if(curr == NULL){
        printf("No list.\n");
        return;}
    else{
        while(curr!= NULL){
            char *token;
            char templine[81];
            strncpy(templine,curr->line_nocomment,80);
            templine[80] = '\0';
            token = strtok(templine, " \t,");
            while(token != NULL){
                token = strtok(NULL, " \t,");
                if(token !=NULL && strcmp(token,target) == 0){
                    //printf("MATCH-%s-: %s\n",target,curr->line_comment);
                    fprintf(outfileptr,"%s",curr->line_comment);
                    break;}
            }//inner-while
            curr = curr->next;
        }//outer-while
        return;
    }//else
    return;
}

//FUNCTION: Used for clearing out all stored memory in LL when program is done.
//PARAM: PASSES HEAD NODE POINTER
void deleteAll(Node** hptr){
    Node * curr = *hptr;
    Node * next;
    if(*hptr == NULL){
        printf("Nothing in list.\n");
        return;}
    while(curr != NULL){
    next = curr->next;
    free(curr);
    curr = next;}

    *hptr = NULL;
}


//RAW code for tokenizer
/*
//            CONTROL FLOW VARIABLES
//            char *token;
//            token = strtok(fileLine," \t ,");                           //grabs the first word of the line
//            if(strchr(token, ':')!= NULL){                               //checks the if it contains :
//                char *token2;
//                token2 = strtok(token, ":");                            //removes the semicolon
//                //printf("token is %s\n", token2);
//                char temp2[12];
//                strncpy(temp2,token2,11);                               //converts string pointer to array of chars
//                temp2[11] = '\0';                                       //last char is going to be a null terminated one.
//                strcpy(flowLab[flowIndex].identifier, temp2);
//                //printf("this is flowLab %s\n", flowLab[flowIndex].identifier);
//                flowIndex++;
//            }//if

//             DATA VARIABLES
//
//            char *token;
//            token = strtok(fileLine," \t ,");                           //grabs the first word of the line
//            if(strchr(token, ':')!= NULL){                               //checks the if it contains :
//                char *token2;
//                token2 = strtok(token, ":");                            //removes the semicolon
//                //printf("token is %s\n", token2);
//                char temp2[12];
//                strncpy(temp2,token2,11);                               //converts string pointer to array of chars
//                temp2[11] = '\0';                                       //last char is going to be a null terminated one.
//                strcpy(varLab[varIndex].identifier, temp2);
//                //printf("this is varlab %s\n", varLab[varIndex].identifier);
//                varIndex++;
//            }

Note to self
//char *array holds a constant string and cannot be modified. only read
//char array[] can be modified

<<<<<<< HEAD
//function that creates a new node that contains source code of label
//passes indicator flag and whole source code line
//all text stored in the new Node is going to be after .text
//i may not need the idflag
Node *newNode(char *comment, char *nocomment){
    Node* newNode = (Node*) malloc(sizeof(Node)); //allocates memory for new node
    strcpy(newNode->line_comment, comment);
    strcpy(newNode->line_nocomment, nocomment);
    newNode->next = NULL;
    printf("New Node created. Whole Line: %s\n", newNode->line_comment );
    return newNode;
}

void insertNode(Node** hptr, Node** tptr, Node *newnodeptr){
    Node * curr = *hptr;
    if(*hptr == NULL){
        newnodeptr->next = *hptr;
        *hptr = newnodeptr;
        *tptr = newnodeptr;
        printf("First Node created. Whole Line:\n%s\n", (*hptr)->line_comment );
        fflush(stdout);
        return;
    }//if

    else{
        curr = *hptr;
        while (curr!=NULL){
            if (*hptr == *tptr){
                *tptr = newnodeptr;
                (*hptr)->next = newnodeptr;
                //printf("Second Node created.\n");
                fflush(stdout);
                return;
            }
            else if(curr == *tptr){
                (*tptr)->next = newnodeptr;
                *tptr = newnodeptr;
                //printf("Inserted at End.\n");
                fflush(stdout);
                return;
            }
            curr = curr->next;
        }//while
    }//else
}//insert funct

void printList(Node *h){
    Node *curr = h;
    if (curr == NULL){
        printf("List is empty.\n");
        fflush(stdout);}
    else{
        printf("The list is:\n");
        int i = 0;
        while (curr!= NULL){
            printf("Line %d: %s\n", i, curr->line_comment);
            fflush(stdout);
            curr = curr->next;
            i++;}
            }//else
} //end of print


//passes the member of the array, checks the nocomment line, and prints out the source code
void searchprint(char* target, Node *hptr){
    Node *curr = hptr;
    if(curr == NULL){
        printf("No list.\n");
        return;
    }
    else{
        while(curr!= NULL){
            if(strstr(curr->line_nocomment,target)!=NULL){          //THERES A MATCH
                printf("%s: %s\n",target,curr->line_comment);}
            curr = curr->next;
        }//while
        return;
    }//else
    return;

}

void deleteAll(Node** hptr){

}
//insert into linked list (create linked list).
=======
*/

>>>>>>> my-temporary-work

