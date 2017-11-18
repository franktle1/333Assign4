#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numOfArgs 4
#define Flag 1
#define InFileArg 2
#define OutFileArg 3
#define VarFlag 1
#define FlowFlag 2
#define NotVarFlowFlag 3
#define TextArea 1
#define DataArea -1


//KNOWN PROBLEMS: DOES NOT READ COMMENTS, READS LINE AND PRINTS LINE OF IDENTIFIER, BUT ONLY FOR THE ONES IT READS AND NOT ACTUAL LINE
//DOES NOT PARS=


//continues skip the current iteration and goes to the next iteration
//France Le
//FL193361
//LAB: Wed 4:15

//ctrlshift c comments
//ctrlshift x uncomments
//do not store comments when storing into a linked list

//char *array holds a constant string and cannot be modified. only read
//char array[] can be modified

    typedef struct labels{
        char identifier[12]; //this will hold one identifier, max length 11
        //struct node *listptr; //this will to a linked list that stores all the source code containing the identifier after
    }label;

//Linked List
    typedef struct Source{
        char line_comment[80];
        char line_nocomment[80];
        int labelType; // if label = VarFlag, then Variable in , label = 1
        struct Source *next;
    }Node;

//PROTOTYPES
Node *newNode(char *comment, char *nocomment);
void insertNode(Node** hptr, Node** tptr, Node *newnodeptr);
void printList(Node *h);
void deleteAll(Node** hptr);
//void searchprint(char* target, Node *hptr);
void searchprint(char* target, Node *hptr, FILE *outfileptr);

int main(int argc, char *argv[])
{

    Node *head, *tail;
    head = tail = NULL;
    FILE *infileptr; //pointer to the the input file
    FILE *outfileptr; //pointer to the output file

    //need to use stderr
    if(argc != numOfArgs){
        printf("Enter [./executable] [flag: -v,-b,-f][inputfilename] [outputfilename]");
        fflush(stdout);
        exit(1);
    }

    char *ip;
    char *op;
    //adds .mal to file name
    ip = (char*)malloc (sizeof(strlen(argv[InFileArg] +5)));
    op = (char*)malloc(sizeof(strlen(argv[OutFileArg]+5)));
    strcpy(ip, argv[InFileArg]);
    strcpy(op, argv[OutFileArg]);
    strcat(ip,".mal");
    strcat(op, ".txt");
//argv[1] has the flag
//argv[2] has the input
//argv[3] has the output file name



//  change file name to ip when switching back to command line args
    if((infileptr = (FILE*)(fopen(ip,"r")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[InFileArg] /*"test.mal"*/);
        fflush(stdout);
        exit(1);
    }

//  change newfile.txt back to op
    if((outfileptr = (FILE*)(fopen(op,"w")))==NULL){
        printf("Could not open %s file. Closing program.\n", argv[OutFileArg] /*"newfile.txt"*/);
        fflush(stdout);
        exit(1);
    }

    char fileLine[81];
    label varLab[100], flowLab[100];
    int section = DataArea;
    int counter = 1;
    int varIndex = 0;
    int flowIndex = 0;



    while(fgets(fileLine,sizeof(fileLine),infileptr)){                  //  loops through each line; each line is stored in fileLine

        if(strstr(fileLine,".text")!= NULL){                             //strstr checks if .text is in the file line. it will be null if there is no match.
            section = TextArea;
            counter = 1;}
        if (section == DataArea){
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



        }
        else if (section == TextArea){
            //read the characters in the characters in that string, cut out the comment
            //store the
            printf("Line %d text area\n",counter);
            //CAPTURE LINES OF CODE IN TEXT AREA WITHOUT THE COMMENTS


            //printf("FileLine: %s\n", fileLine);
            char wholecomment[80];
            char temp[80];
            char *comtoken;
            char *nocomment;

            strcpy(wholecomment,fileLine); //stores it in its own array//file line gets modified in the tokenizer
            strcpy(temp, fileLine);

            if(temp[0]=='#' ){                                       //Filters lines that start with a comment
                printf("COMMENT ALERT!\n");
                continue;
            }
            else if(strstr(temp, "globl")!= NULL){
               printf("GLOBL COMMAND SKIPPED.");
               continue;}
            else{

            comtoken = strtok(temp, "#");
            nocomment = comtoken;


            printf("this is fileline - %s\n", fileLine);
            //TOKENIZER////////////////////////////////////////////Modifies fileLine
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






                                       //gets the section before the #, stores it into nocomment
            //printf("%cSourceCode: %s\n",nocomment[0], nocomment);
            //STORE THE FILELINE & NOCOMMENT LINE INTO INSERTFUNCTION TO NODE LIST.
            Node *nodeptr = newNode(wholecomment, nocomment);
            insertNode(&head, &tail, nodeptr);
 //           printf("this is no comment: %s\n",nocomment);
            }//else




        } //end of text area

        counter++;
    }//end of whie loop
    //have to test if infileptr leaves

    int i;
    for (i = 0; i < varIndex;i++)
        printf("This is the element %d: %s\n", i, varLab[i].identifier);
    for (i = 0; i < flowIndex;i++)
        printf("This is the element %d: %s\n", i, flowLab[i].identifier);


//THIS PRINTS TO FILE

    if(strcmp(argv[Flag],"-b")==0){
    for (i = 0; i < varIndex;i++){
        fprintf(outfileptr,"Variable Label -%s-\n",varLab[i].identifier);
        searchprint(varLab[i].identifier, head, outfileptr);}
    printf("\n\n");
    for (i = 0; i < flowIndex;i++){

        fprintf(outfileptr, "Control Flow Label -%s-\n",flowLab[i].identifier);
        searchprint(flowLab[i].identifier, head, outfileptr);}
    }

    if(strcmp(argv[Flag],"-v")==0){
        for (i = 0; i < varIndex;i++){
        fprintf(outfileptr,"Variable Label -%s-\n",varLab[i].identifier);
        searchprint(varLab[i].identifier, head, outfileptr);}
    }

    if(strcmp(argv[Flag],"-f")==0){
    for (i = 0; i < flowIndex;i++){
        fprintf(outfileptr, "Control Flow Label -%s-\n",flowLab[i].identifier);
        searchprint(flowLab[i].identifier, head, outfileptr);}
    }




    //LINKED LIST DEBUGGER//////////////////////////////////////////////////
    //printList(head);




    //closes files
    if(fclose(infileptr) == EOF){
        printf("Error in closing input file.");
        fflush(stdout);
    }

    if(fclose(outfileptr) == EOF){
        printf("Error in closing output file.");
        fflush(stdout);
    }

    deleteAll(&head);
    printList(head);
    free(ip);
    free(op);
    return 0;
}

//Purpose is grab the first word
//
//void tokenizeID(char *codeLine, int index, struct labels idlab[]){
//    char *token;
//            token = strtok(codeLine," \t ,"); //grabs the first word of the line
//            if(strchr(token, ':')!= NULL){                               //checks the if it contains :
//                char *token2;
//                token2 = strtok(token, ":"); //removes the semicolon
//                char temp2[12];
//                strncpy(temp2,token2,sizeof(temp2 -1 )); //turns a string pointer to an array of chars
//                temp2[11] = '\0'; //last char is going to be a null terminated one.
//                strcpy(idlab[index],identifier, temp2);
//                printf("this is varlab %s\n", idlab[index].identifier);
//                varIndex++;
//            }
//    return;
//}



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
            printf("Line with comment %d: %s\n", i, curr->line_comment);
            fflush(stdout);
            printf("Line wout comment %d: %s\n", i, curr->line_nocomment);
            fflush(stdout);
            curr = curr->next;
            i++;}
            }//else
} //end of print


//passes the member of the array, checks the nocomment line, and prints out the source code
void searchprint(char* target, Node *hptr, FILE *outfileptr){
    Node *curr = hptr;
    if(curr == NULL){
        printf("No list.\n");
        return;
    }
    else{
        while(curr!= NULL){
            char *token;
            char templine[81];
            strncpy(templine,curr->line_nocomment,80);
            templine[80] = '\0';
            token = strtok(templine, " \t,");
            while(token != NULL){
                token = strtok(NULL, " \t,");
                if(token !=NULL && strstr(token,target)!=NULL){
                    //printf("MATCH-%s-: %s\n",target,curr->line_comment);
                    fprintf(outfileptr,"%s\n",curr->line_comment);
                    break;
                }
            }
//            if(strstr(curr->line_nocomment,target)!=NULL){          //THERES A MATCH
//                printf("%s: %s\n",target,curr->line_comment);}
            curr = curr->next;
        }//while
        return;
    }//else
    return;

}

void deleteAll(Node** hptr){
    Node * curr = *hptr;
    Node * next;

    if(*hptr == NULL){
        printf("Nothing in list.\n");
        return;
    }
    while(curr != NULL){
    next = curr->next;
    free(curr);
    curr = next;
    }
    *hptr = NULL;
}
//insert into linked list (create linked list).

