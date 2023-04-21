#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_VOTERS 100 // maximum number of voters supported

// initialize global vote counters
int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

// define a struct for voter information
struct voter {
    char name[50];
    int age;
    char username[50];
    char password[50];
    char voterid[11];
    char address[50];
};

// function prototypes
void registration();
void login();
void update();
void posi_vote();
void vote();
void displayresult();
char* generate_voterid();

// global array to store voter information
struct voter voters[MAX_VOTERS];
int num_voters = 0;

// function definitions

// This function allows a new voter to register and writes their information to a file.
void registration() {
    struct voter v; // create a new voter struct
    printf("\t\t\t\tWELCOME TO REGISTRATION\n");
    printf("PLEASE ENTER YOUR NAME\n");
    scanf("%s", v.name);
    printf("ENTER YOUR AGE\n");
    scanf("%d", &v.age);
    if (v.age < 18) {
        printf("Sorry, you must be 18 years or older to register to vote.\n");
        return;
    }
    printf("ENTER A USERNAME (NO SPECIAL CHARACTERS ALLOWED)\n");
    scanf("%s", v.username);
    printf("ENTER A PASSWORD\n");
    scanf("%s", v.password);
    printf("ENTER YOUR ADDRESS\n");
    scanf("%s", v.address);
    strcpy(v.voterid, generate_voterid());
    voters[num_voters] = v; // add the voter to the array
    num_voters++; // increment the number of registered voters
    printf("REGISTRATION SUCCESSFUL\nYOUR VOTER ID IS %s\nNOW PLEASE LOGIN\n", v.voterid);
    login();
}

// This function allows a registered voter to login and access voting options.
void login() {
    char username[50];
    char password[50];
    struct voter* v;
    printf("ENTER USERNAME\n");
    scanf("%s", username);
    printf("ENTER PASSWORD\n");
    scanf("%s", password);
    int i;
    for (i = 0; i < num_voters; i++) {
        v = &voters[i];
        if (strcmp(v->username, username) == 0 && strcmp(v->password, password) == 0) {
            printf("YOU HAVE SUCCESSFULLY LOGGED IN\n");
            printf("DO YOU WANT TO:\n");
            printf("1. GIVE VOTE\n");
            printf("2. DISPLAY POSITIONS FOR VOTING\n");
            printf("3. UPDATE PROFILE\n");
            printf("ENTER YOUR CHOICE\n");
            int choice;
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    if (strcmp(v->voterid, "") == 0) {
                        printf("Sorry, you have already voted and cannot vote again.\n");
                        return;
                    }
                    vote(v);
                    break;
                case 2:
                    posi_vote();
                    break;
                case 3:
                    update(v);
                    break;
                default:
                    printf("INVALID INPUT\n");
            }
            return;
        }
    }
    printf("INVALID USERNAME OR PASSWORD.\n");
}

// This function allows a voter to update their address information.
void update(struct voter* v) {
printf("ENTER YOUR NEW ADDRESS\n");
scanf("%s", v->address);
printf("ADDRESS UPDATED SUCCESSFULLY\n");
}

// This function displays the available positions for voting.
void posi_vote() {
printf("\t\t\t\tAVAILABLE POSITIONS\n");
printf("1. President\n");
printf("2. Vice President\n");
printf("3. Secretary\n");
printf("4. Treasurer\n");
}

// This function allows a registered voter to vote.
void vote(struct voter* v) {
if (strcmp(v->voterid, "") != 0) {
printf("Sorry, you have already voted and cannot vote again.\n");
return;
}
printf("PLEASE CHOOSE A CANDIDATE BY ENTERING THEIR POSITION NUMBER\n");
int choice;
scanf("%d", &choice);
switch (choice) {
case 1:
c1++;
break;
case 2:
c2++;
break;
case 3:
c3++;
break;
case 4:
c4++;
break;
default:
printf("INVALID INPUT\n");
return;
}
strcpy(v->voterid, "");
printf("THANK YOU FOR VOTING\n");
}

// This function generates a unique voter ID.
char* generate_voterid() {
    static char id[11]; // static variable to hold the voter ID
    const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i, r;
    srand(time(NULL)); // seed the random number generator with the current time
    for (i = 0; i < 10; i++) {
        r = rand() % (int)(sizeof(charset) - 1);
        id[i] = charset[r]; // select a random character from the character set
    }
    id[10] = '\0'; // null terminate the ID string
    return id;
}


// This function displays the voting results.
void displayresult() {
printf("\t\t\t\tVOTING RESULTS\n");
printf("President: %d\n", c1);
printf("Vice President: %d\n", c2);
printf("Secretary: %d\n", c3);
printf("Treasurer: %d\n", c4);
}

// main function
int main() {
printf("\t\t\t\tWELCOME TO ELECTION SYSTEM\n");
int choice;
while (1) {
printf("\t\t\t\tMAIN MENU\n");
printf("1. REGISTER\n");
printf("2. LOGIN\n");
printf("3. DISPLAY VOTING RESULTS\n");
printf("4. EXIT\n");
printf("ENTER YOUR CHOICE\n");
scanf("%d", &choice);
switch (choice) {
case 1:
registration();
break;
case 2:
login();
break;
case 3:
displayresult();
break;
case 4:
printf("THANK YOU FOR USING ELECTION SYSTEM\n");
return 0;
default:
printf("INVALID INPUT\n");
}
}
return 0;
}







