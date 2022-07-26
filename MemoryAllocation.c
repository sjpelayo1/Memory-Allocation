/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
//declare methods and global variables
void optionOne();
void optionTwo();
void optionThree();
void optionFour();
int pm_size;
int remainingStorage;
int AlgorithmChoice;

//allocated block structure containing info
struct allBlock {       //"node containing info"
    int ID;
    int startAddress;
    int endAddress;
    struct allBlock *next;  //create reference to next node
}*head = NULL;      //pointer holds address of starting node;

typedef struct allBlock allocatedBlock;     // create block type


void optionOne() {

    
    printf("Please enter the size of the Physical Memory: ");       //prompt for size of memory 
    scanf("%d", &pm_size);
    remainingStorage = pm_size;
    head = (allocatedBlock *)malloc(sizeof(allocatedBlock));        //allocate storage for list
    printf("Please enter the hole-fitting algorithm you would like to use:");
    printf("(0 = first fit, 1 = best fit) : ");     //Prompt for AlgorithmChoice
    scanf("%d", &AlgorithmChoice);
    head -> ID = -1;
    head -> startAddress = 0;
    head -> endAddress = 0;
    head -> next = NULL;        //initialize head node

   return;
}

void printTable() {
    printf("------CURRENT TABLE-----\n");       
    printf("ID \t Start \t End\n");
    printf("-------------------------\n");
    allocatedBlock* currentBlock = head -> next;        //create current temp block and  have reference to next node
    while(currentBlock != NULL) {                       //while its not empty print everytihing 
        printf("%d\t", currentBlock -> ID);
        printf("%d\t", currentBlock -> startAddress);
        printf("%d\n", currentBlock -> endAddress);
        
        currentBlock = currentBlock -> next;        //reference to next node
    }
    return;
}



void optionTwo() {      
    int blockID;        //initiaize variables within method
    int blockSize;
    int beginningIndex;
    int endIndex;
    int availableSize;
    int oneAvailable = 0;
    int bestAvailable;
    int bestStart;
        if(AlgorithmChoice == 0) {      //first fit if algorithm choice is 0
            
            allocatedBlock* currentHead = head;     //create current temp node reference to head of list
            allocatedBlock* newHead;        //create temp head node
            printf("Enter Block ID:");
            scanf("%d", &blockID);
            printf("Enter the Size of the Block: ");        //prompt for block information
            scanf("%d", &blockSize);
            if(blockSize > remainingStorage) {
                printf("Block cannot be placed here, there is not enough memory remaining.");
                return;
            }
            
            newHead = (allocatedBlock *)malloc(sizeof(allocatedBlock));     //allocate memory
            newHead -> ID = blockID;
            if(head -> next == NULL) {
                newHead -> startAddress = head -> endAddress;
                newHead -> endAddress = newHead -> startAddress + blockSize;    //reference where new head will start with 
                newHead -> next = NULL;                                         //beginning address and  end address
                head -> next = newHead;
                remainingStorage -= blockSize;      //decrement remaining storage by the block size to update remaining storage after insertion
                return;
            }
            
            while(currentHead != NULL) {
                if(blockID == currentHead -> ID) {      //if block id is taken current temp insertion node cannot be inserted
                    printf("Cannot insert block. This ID is taken, please enter a new ID");
                    free(newHead);
                    return;
                }
                currentHead = currentHead -> next;      //reference it to next node
            }
            
            currentHead = head;         //reference to head node
            
            while(currentHead != NULL) {
                beginningIndex = currentHead -> endAddress;
                if(currentHead -> next != NULL) {
                    endIndex = currentHead -> startAddress;
                }       //with insertion create references to beginningIndex and endIndex for beginnign and end addeesses 
                else {
                    endIndex = pm_size;
                }
                availableSize = endIndex - beginningIndex;
                if(blockSize <=  availableSize) {
                    newHead -> startAddress = beginningIndex;
                    newHead -> endAddress = beginningIndex + blockSize;
                    newHead -> next = currentHead -> next;
                    currentHead -> next = newHead;
                    remainingStorage -= blockSize;      //remove block size from remaining storage after insertion
                    return;
                }
                currentHead = currentHead -> next;
            }
            printf("Error: There is no available hole.");
            free(newHead);
            return;
    }
    
            if(AlgorithmChoice == 1) {      //method for best fit AlgorithmChoice
                bestAvailable = pm_size;    //best available spot referenfes the physical memory size 
                allocatedBlock* currentHead = head;
                allocatedBlock* newHead;
                allocatedBlock* bestHead;       //create temp head nodes and best node and reference 
                printf("Please Enter the Block ID: ");
                scanf("%d", &blockID);
                printf("\n Please enter the Block Size: ");
                scanf("%d", &blockSize);                        //prompt for block information
                if(blockSize > remainingStorage) {
                    printf("\n Error: There is not enough storage for this block. Please try again. \n");
                    return;
                }
                newHead = (allocatedBlock *)malloc(sizeof(allocatedBlock));     //allocate memory for list
                newHead -> ID = blockID;        
                if(head -> next == NULL) {
                    newHead -> startAddress = head -> endAddress;
                    newHead -> endAddress = newHead -> startAddress + blockSize;
                    newHead -> next = NULL;
                    head -> next = newHead;         //create references to know where insertion address is and end address for new insertion 
                    remainingStorage -= blockSize;      //remove blockSize from remaining storage after insertion
                    return;
                }
                
                while(currentHead != NULL) {
                    if(blockID == currentHead -> ID) {
                        printf("Cannot insert block. This ID is taken, please enter a new ID");
                        free(newHead);
                        return;                         //if block id is taken
                    }
                    currentHead = currentHead ->next;
                }
                
                currentHead = head;             //reference temp currentHead node to head; 
                while(currentHead != NULL) {
                    beginningIndex = currentHead -> endAddress;
                    if(currentHead -> next != NULL) {
                        endIndex = currentHead -> next -> startAddress;
                    }
                    else {
                        endIndex = pm_size;
                    }
                    availableSize = endIndex - beginningIndex;     // calculate available space for block 
                    if(blockSize <= availableSize) {
                        oneAvailable = 1;
                        if(availableSize < bestAvailable) {    // if new spot is better then 
                            bestAvailable = availableSize;      //Becomes best now
                            bestStart = beginningIndex;
                            bestHead = currentHead;     //head is grabbed from temp node
                        }
                    }
                    currentHead = currentHead -> next;
                    }
                    if(oneAvailable == 0) {             //checks for available hole, if none display error
                        printf("Error: There is no hole available.");
                        free(newHead);
                        free(bestHead);     //clear the blocks 
                        return;
                    }
                    
                    newHead -> startAddress = bestStart;
                    newHead -> endAddress = newHead -> startAddress + blockSize;        //references for new temp insertions 
                    newHead -> next = bestHead -> next;
                    bestHead -> next = newHead;
                    remainingStorage -= blockSize;      //remove blockSize from remaining storage after insertion 
                
             
    return;
        }
}



void optionThree() {
    int blockID;
    int blockSize;
    allocatedBlock* currentHead = head;
    allocatedBlock* previous;
    printf("please Enter the Block ID: ");
    scanf("%d", &blockID);
    while((currentHead != NULL) && (blockID != currentHead -> ID)) {        //prompt for block id to be deleted
        previous = currentHead;
        currentHead = currentHead -> next;                  //previous is referenced to current and set to current next 
    }
    if(currentHead == NULL) {
        printf("Error: wrong ID number entered. Please Try Again.");        //no existing ID found 
        return;
    }
    previous -> next = currentHead -> next;
    blockSize = currentHead -> endAddress - currentHead -> startAddress;        //remove current head and create references for deletion 
    remainingStorage += blockSize;
    free(currentHead);
    return;
}

void optionFour() {
    allocatedBlock*  currentHead = head;        //initialize temp current head 
    int blockSize;
    int previousAddress = head -> endAddress;       //set previousAddressto end address of head
    while(currentHead != NULL) {                    //while current block is not emoty 
        blockSize = currentHead -> endAddress - currentHead -> startAddress;
        currentHead -> startAddress = previousAddress;                          //set references to 
        currentHead -> endAddress = currentHead -> startAddress +blockSize;     //remove gaps from memory 
        previousAddress = currentHead -> endAddress;
        currentHead = currentHead -> next;
    }
    return;
}

void optionFive() {
    allocatedBlock* head;
    if(head == NULL) {      //if block list is empty do nothing 
        return;
    }
    else {
        optionFive(head->next);     
    }
    free(head);         //recursivekly free memory until block is empty 
    return;
}

int main()
{
    
    int userSelection = 0;      //initialize user selection and boolean to false
    bool quit = false;          //boolean stays false until set true for quitting program 
    
    
    while( quit != true) {
        printf("------User Menu------\n");
        printf("1) Enter Parameters\n");
        printf("2) Allocate memory for block\n");
        printf("3) Deallocate memory for block\n");
        printf("4) Defragment memory\n");
        printf("5) Quit program\n");
        printf("Please enter your selection: ");
        scanf("%d", &userSelection);
        switch(userSelection) {
            case 1 : {      //first option to initialize Parameters
                optionOne();
                break;
            }
            case 2 : {
                optionTwo();        //second option adds a new block 
                printTable();       //print table to show new added block 
                break;
            }
            case 3 : {
                optionThree();      //delete a block 
                printTable();
                break;
            }
            case 4: {
                optionFour();       //defragment memory 
                printTable();
                break;
            }
            case 5: {
                optionFive();   //quit program and free memory 
                quit = true;        //set boolean to trye to exit program 
            }
            default: {
                printf("You have chosen an incorrect option. Please try again:");
                break;      //default incase wrong number is entered then prompts for another attempt
            }
        
        }
        
    }
    return 1;           //indicate success 
    
}



