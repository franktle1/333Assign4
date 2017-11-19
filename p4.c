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

//France Le
//FL193361
//LAB: Wed 4:15

//Holds the labels
    typedef struct labels{
        char identifier[12]; //this will hold one identifier, max length 11
    }label;

//Linked List
    typedef struct Source{
        char line_comment[80];
        char line_nocomment[80];
        struct Source *next;
    }Node;

//PROTOTYPES
Node *newNode(char *comment, char *nocomment);
void insertNode(Node** hptr, Node** tptr, Node *newnodeptr);
void printList(Node *h);
void deleteAll(Node** hptr);
void tokenizeID(char *line, label idlab[], int * indexaddress);
void searchprint(char* target, Node *hptr, FILE *outfileptr);

int main(int argc, char *argv[])
{
    Node *head, *tail;
    head = tail = NULL;
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
        //fprintf(stderr,"Error opening file:%s\n", strerror(errnum));
        exit(1);}
    if((outfileptr = (FILE*)(fopen(argv[OutFileArg],"w")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[OutFileArg] /*"newfile.txt"*/);
        fflush(stdout);
        int errnum;
        errnum = errno;
        fprintf(stderr, "Value of errno:%d\n", errno);
        perror("Error printed by perror.");
        //fprintf(stderr,"Error opening file:%s\n", strerror(errnum));
        exit(1);}

    /////////////////////////////////////////////////////////


    ////////////////////////

    //DATA FIELDS
    char fileLine[81];
    label varLab[100], flowLab[100];                                     // Stores all the identifier
    int section = DataArea;                                             //used to identify which section (.data or .text) to look for identifiers
    int varIndex = 0;
    int flowIndex = 0;

    while(fgets(fileLine,sizeof(fileLine),infileptr)){                  //  loops through each line; each line is stored in fileLine

        if(strstr(fileLine,".text")!= NULL){                             //strstr checks if .text is in the file line. it will be null if there is no match.
            section = TextArea;}
        if (section == DataArea){
            tokenizeID(fileLine, varLab, &varIndex);                     //TOKENIZER for Data variables- stores them into an array
        }
//      Section does two things: 1. Puts all Control Flow Labels into its struct array. 2. Stores Original Code, and Non-Commented Code into an array.
        else if (section == TextArea){

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

            if(tempid[0] == '.'){                                    //Filters out Control Flow used in identifiers
               printf("IDENTIFIER SKIPPED.\n");
               continue;}


            comtoken = strtok(temp, "#");
            nocomment = comtoken;                                       //Stores Non-Commented Code into variable
            tokenizeID(fileLine, flowLab, &flowIndex);                  //TOKENIZER - for flow characters; stores flow control chars in array
            Node *nodeptr = newNode(wholecomment, nocomment);           //STORE THE FILELINE & NOCOMMENT LINE INTO INSERTFUNCTION TO NODE LIST.
            insertNode(&head, &tail, nodeptr);

        } //end of text area
    }//end of whie loop

//////DEBUGGING: PRINTS OUT ALL IDENTIFIERS
    int i;
    for (i = 0; i < varIndex;i++)
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

    //Closes both files and deallocates all memory
    if(fclose(infileptr) == EOF){
        int errnum;
        errnum = errno;
        fprintf(stderr, "Value of errno:%d\n", errno);
        fflush(stdout);
        perror("Error printed by perror.");
        fflush(stdout);
        fprintf(stderr,"Error closing file:%s\n", strerror(errnum));
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
        fprintf(stderr,"Error closing file:%s\n", strerror(errnum));
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

*/


