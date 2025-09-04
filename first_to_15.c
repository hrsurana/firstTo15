#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>


int pos[10] = { 0,0,0,0,0,0,0,0,0,0}; //Stores the players number choice
int playerno[10] = { 0,0,0,0,0,0,0,0,0,0}; //Stores the player number (1 or 2)
char boardchoice[10] = {'o','A','B','C','D','E','F','G','H','I'}; //Stores the position of the player of the board
int testarr[10]= { 0,0,0,0,0,0,0,0,0,0}; //Used to check if the user input is repeated
int testarrforcomp[10]= { 0,0,0,0,0,0,0,0,0,0}; // Used to ensure that the computer does not repeat a number or position

int choice,player, x, i,number, nochoice;
char numchar[20];

int pvp(); //Player vs Player function
int pvc(); //Player vs Computer function
int choosingletters(); //Function allows user to choose their position on the board
void theboard(); //Generates and updates the board, displaying the player number and the number they select (from 1-9)
void thepositionboard(); //Generates and updates the board displaying the players' positions on the board (A-I)
void checkcount(); //Checks whether the input number is repeated
int checkifsomeonewon(); //Checks if there is a winner
void picker(); //Computer generates numbers, in response to the player's moves
void winner(); //Checks if winning criteria is met and displays a message accordingly
void replacement(); //Takes the user inputs and replaces values in the respective arrays, given that certain conditions are met

int main() //Start/Display screen that executes a particular function depending on the user's choice
{
    char pc[50];
    printf(" ***  ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   **\n");
    printf("  * .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *\n");
    printf("* +                                                                                                 + *\n");
    printf(" *.         _+|+  S T      |.|+|.|+|.|+|.|+|  |||||||||||              |.|   ||||||||||||             .*\n");
    printf("* +          |+|           |+|.|+|.|+|.|+|.| |+.|     |.+|             |+|   |.+|      ||           + *\n");
    printf(" *.          +|+                 |+.|        |.+|     |+.|             |.|   |+.|                     .*\n");
    printf("* +          |+|                 |.+|        |+.|     |.+|             |+|   |.+|||||||||           + *\n");
    printf(" *.          +|+                 |+.|        |.+|     |+.|             |.|            |.+|            .*\n");
    printf("* +          |+|                 |.+|        |+.|     |.+|             |+|             |.|          + *\n");
    printf(" *.          +|+                 |+.|        |.+|     |+.|             |.|            |+|             .*\n");
    printf("* +          |+|                 |.+|         |||||||||||              |+|   |||||||||.|            + *\n");
    printf("*.          First                       To                                   Fifteen                  .*\n");
    printf("* +                                                                                                 + *\n");
    printf("  * .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *  +  *  .  *\n");
    printf(" ***  ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   ***   **\n\n\n");
    printf("\t 2|7|6\t\tWelcome to the first to 15 game! Choose your opponent!\n");
    printf("\t -|-|-\t\tPress 1 to play with another player.\n");
    printf("\t 9|5|1\t\tPress 2 to play with a bot.\n");
    printf("\t -|-|-\t\tOr Press 3 to exit the game.\n");
    printf("\t 4|3|8\n");
    scanf("%s",&pc);
    int cp = atoi(pc);
    while (cp!=1 && cp!=2&& cp!=3)
        {//If the user doesn't choose from the accepted options they're shown an error message
            printf("\n\t\t\tError! Invalid number!\n\t\t\tPress 1 to play with another player.\n\t\t\tPress 2 to play with a bot.\n\t\t\tOr Press 3 to exit the game.");
            scanf("%s",&pc);
            cp = atoi(pc);
        };
    switch (cp) //PvP or PvC function is executed depending on whether the user inputs 1 or 2 and quits if the user selects 3.
    {
        case 1:{pvp(); break;}
        case 2: {pvc(); break;}
        case 3: {printf("\n\t\t\tGoodbye! Have a nice day!"); break;}
    }
}

int pvp() /*Player set as '1' or '2' and both input a position followed by a number after which a series of checks are carried out
            which determine whether the input value can be accepted and whether or not there is a winner*/
{
    int player = 1;
    do
    {
        theboard();
        player = (player % 2) ? 1 : 2;
        printf("\nPlayer %d. The letters A,B,C,D,E,F,G,H,I show the positions on the board\n", player);
        nochoice= choosingletters();
        printf("\nNow, enter a number from 1-9, once entered by any player, you cannot use the same number.\n");
        scanf("%s", &numchar);
        int number = atoi(numchar);
        while (number!= 1 && number!= 2 && number!= 3 && number!= 4 && number!= 5 && number!= 6 && number!= 7 && number!= 8 &&number!= 9)
        {
            printf("\nInvalid number!");
            printf("\nGive me a valid number!\n");
            scanf("%s",&numchar);
            number = atoi(numchar);
        }
        checkcount();
        x=player;
        replacement();
        i = checkifsomeonewon();
        player++;
    }
    while (i ==  - 1);
    theboard();
    winner();
}

int pvc() /*Player set as 1 or 2, but player 2 in this case is the computer which generates a position and number in response
            to what Player 1 (the user) inputs. A series of checks are carried out to ensure that player 1 does not input
            invalid values, followed by a series of checks to see if there is a winner.*/
{
    int player = 1, i;
    char choice,number;
    do
    {
        theboard();
        player = (player % 2) ? 1 : 2;
        if (player==1)
        {
            printf("\nPlayer %d. The letters A,B,C,D,E,F,G,H,I show the positions on the board\n", player); // change to player 1
            nochoice= choosingletters();
            printf("\nNow, enter a number from 1-9, once entered by any player, you cannot use the same number.\n");
            scanf("%s", &numchar);
            int number = atoi(numchar);
            while (number!= 1 && number!= 2 && number!= 3 && number!= 4 && number!= 5 && number!= 6 && number!= 7 && number!= 8 &&number!= 9)
            {
                printf("\nInvalid number!");
                printf("\nGive me a valid number!");
                scanf("%s",&numchar);
                number = atoi(numchar);
            }
            checkcount();
            x=player;
            replacement();
            i = checkifsomeonewon();
            player++;
        }
        else if (player==2)
        {
            picker();
            i = checkifsomeonewon();
            player++;
        }
    }
    while (i == - 1);
    theboard();
    winner();
}

int checkifsomeonewon()

{
    int z=1;
    switch (z)
    {
        case 1:
            if (playerno[1]== playerno[2]&& playerno[2]== playerno[3] && playerno[1]== playerno[3])
            {
                if (pos[1]+ pos[2]+pos[3]== 15)
                {return 1; break;}
                else {}
            }
        case 2:
            if (playerno[4]== playerno[5]&& playerno[5]== playerno[6] && playerno[4]== playerno[6])
            {
                if (pos[4]+ pos[5]+pos[6]== 15)
                {return 1; break;}
                else {}
            }
        case 3:
            if (playerno[7]== playerno[8]&& playerno[8]== playerno[9] && playerno[9]== playerno[7])
            {
                if (pos[7]+ pos[8]+pos[9]== 15)
                {return 1; break;}
                else {}
            }
        case 4:
            if (playerno[1]== playerno[4]&& playerno[7]== playerno[4] && playerno[1]== playerno[7])
            {
                if (pos[1]+ pos[4]+pos[7]== 15)
                {return 1; break;}
                else {}
            }
        case 5:
            if (playerno[2]== playerno[5]&& playerno[5]== playerno[8] && playerno[2]== playerno[8])
            {
                if (pos[2]+ pos[5]+pos[8]== 15)
                {return 1; break;}
                else {}
            }
        case 6:
            if (playerno[3]== playerno[6]&& playerno[6]== playerno[9] && playerno[9]== playerno[3])
            {
                if (pos[3]+ pos[9]+pos[6]== 15)
                {return 1; break;}
                else {}
            }
        case 7:
            if (playerno[1]== playerno[5]&& playerno[5]== playerno[9] && playerno[1]== playerno[9])
            {
                if (pos[1]+ pos[5]+pos[9]== 15)
                {return 1; break;}
                else {}
            }
        case 8:
            if (playerno[3]== playerno[5]&& playerno[5]== playerno[7] && playerno[7]== playerno[3])
            {
                if (pos[3]+ pos[5]+pos[7]== 15)
                {return 1; break;}
                else{}
            }
        case 9:
            if (pos[1] != 0 && pos[2] != 0 && pos[3] != 0 && pos[4] != 0 && pos[5] != 0 && pos[6] != 0 && pos[7]!= 0 && pos[8] != 0 && pos[9] != 0)
            {return 0; break;}
        default:
            {return -1; break;}
    }
}

void theboard()
{
    system("cls"); //This is used to clear the screen before every time the board is updated

    thepositionboard ();
    printf("\n This board shows the player and the number that they chose.\n");
    printf("          |          |     \n");
    printf(" p(%d): %d  | p(%d): %d  | p(%d): %d \n", playerno[1], pos[1],playerno[2], pos[2], playerno[3], pos[3]);
    printf("__________|__________|_________\n");
    printf("          |          |     \n");
    printf(" p(%d): %d  | p(%d): %d  | p(%d): %d \n", playerno[4],pos[4],playerno[5], pos[5],playerno[6], pos[6]);
    printf("__________|__________|_________\n");
    printf("          |          |     \n");
    printf(" p(%d): %d  | p(%d): %d  | p(%d): %d \n", playerno[7], pos[7], playerno[8], pos[8], playerno[9], pos[9]);
    printf("          |          |     \n\n");
}

void thepositionboard()
{
    char choice;
    printf("The First to 15 game\n\n");
    printf("Player 1  -  Player 2\n\n");
    printf("These letters show your position on the board. Once a letter is taken, it should not be chosen again. \n");
    printf("          |          |     \n");
    printf("    %c     |     %c    |     %c\n",boardchoice[1],boardchoice[2],boardchoice[3]);
    printf("__________|__________|_________\n");
    printf("          |          |     \n");
    printf("    %c     |     %c    |     %c \n", boardchoice[4],boardchoice[5],boardchoice[6]);
    printf("__________|__________|_________\n");
    printf("          |          |     \n");
    printf("    %c     |     %c    |     %c   \n", boardchoice[7],boardchoice[8],boardchoice[9]);
    printf("          |          |     \n");
}

void checkcount()
{
    while (1)
    {
        int number = atoi(numchar);
        if (testarr[1] == 0 && number==1)
        {
            testarr[1]=number;
            testarrforcomp[1]=number; break;
        }
        else if (testarr[2]==0 && number==2)
        {
            testarr[2]=number;
            testarrforcomp[2]=number; break;
        }
        else if (testarr[3]==0 && number==3)
        {
            testarr[3]=number;
            testarrforcomp[3]=number;break;
        }
        else if (testarr[4]==0 && number== 4)
        {
            testarr[4]=number;
            testarrforcomp[4]=number;break;
        }
        else if (testarr[5]==0 && number==5)
        {
            testarr[5]=number;
            testarrforcomp[5]=number;break;
        }
        else if (testarr[6]==0 && number==6)
        {
            testarr[6]=number;
            testarrforcomp[6]=number;break;
        }
        else if (testarr[7]==0 && number==7)
        {
            testarr[7]=number;
            testarrforcomp[7]=number; break;
        }
        else if (testarr[8]==0 && number==8)
        {
            testarr[8]=number;
            testarrforcomp[8]=number; break;
        }
        else if (testarr[9]==0 && number==9)
        {
            testarr[9]=number;
            testarrforcomp[9]=number; break;
        }
        else
        {
            printf("Invalid move!! Warning!! You can only use numbers from 1-9 and only if they haven't been taken.\n");
            printf("Please choose another number\n");
            scanf("%s", &numchar);
        }
    }
}


void picker()
{
    while (1)
    {
        srand(time(NULL)); //srand provides a seed based off which random numbers are generated
        nochoice = (rand()%9)+1; //'nochoice; contains a random number between 1 to 9 to indicate the computer's posiiton
        if (boardchoice[nochoice]!='-')
        {
            boardchoice[nochoice]='-';
            break;
        }
        else{}
    }
    while (1)
    {
        srand(time(NULL));
        number = (rand()%9)+1; /*'number' (as used earlier to store the number the user inputs) stores a randomly generated number from 1-9
                              after which, given that the number is not repeated, it is stored in the respective arrays to be updated in the board.*/
        if (testarrforcomp[1] == 0 && number==1)
        {
            testarrforcomp[1]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[1]=number;
            break;
        }
        else if (testarrforcomp[2]==0 && number==2)
        {
            testarrforcomp[2]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[2]=number; break;
        }
        else if (testarrforcomp[3]==0 && number==3)
        {
            testarrforcomp[3]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[3]=number; break;
        }
        else if (testarrforcomp[4]==0 && number==4)
        {
            testarrforcomp[4]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[4]=number; break;
        }
        else if (testarrforcomp[5]==0 && number==5)
        {
            testarrforcomp[5]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[5]=number; break;
        }
        else if (testarrforcomp[6]==0 && number==6)
        {
            testarrforcomp[6]=number;
            pos[nochoice]=number;
            playerno[nochoice]=2;
            testarr[6]=number; break;
        }
        else if (testarrforcomp[7]==0 && number==7)
        {
            testarrforcomp[7]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[7]=number; break;
        }
        else if (testarrforcomp[8]==0 && number==8)
        {
            testarrforcomp[8]=number;
            pos[nochoice]=number;
            playerno[nochoice]=2;
            testarr[8]=number; break;
        }
        else if (testarrforcomp[9]==0 && number==9)
        {
            testarrforcomp[9]=number;
            pos[nochoice]=number;
            playerno[nochoice]= 2;
            testarr[9]=number;
            break;
        }
    }
}

int choosingletters()
{
    char choice[20];
    while (1)
    {
        printf("Please enter your position on the board\n");
        scanf("%s", &choice);
        if (boardchoice[1]=='A' && strcmp(choice, "A") == 0 || boardchoice[1]=='A' && strcmp(choice, "a") == 0)
        {
           return 1; break;
        }
        else if (boardchoice[2]=='B' &&strcmp(choice, "B") == 0 || boardchoice[2]=='B' &&strcmp(choice, "b") == 0)
        {
           return 2; break;
        }
        else if (boardchoice[3]=='C' &&strcmp(choice, "C") == 0 ||boardchoice[3]=='C' &&strcmp(choice, "c") == 0)
        {
            return 3; break;
        }
        else if (boardchoice[4]=='D' &&strcmp(choice, "D") == 0 ||boardchoice[4]=='D' &&strcmp(choice, "d") == 0)
        {
           return 4; break;
        }
        else if (boardchoice[5]=='E' &&strcmp(choice, "E") == 0 ||boardchoice[5]=='E' &&strcmp(choice, "e") == 0)
        {
           return 5; break;
        }
        else if (boardchoice[6]=='F' &&strcmp(choice, "F") == 0 ||boardchoice[6]=='F' &&strcmp(choice, "f") == 0)
        {
           return 6; break;
        }
        else if (boardchoice[7]=='G' &&strcmp(choice, "G") == 0 || boardchoice[7]=='G' &&strcmp(choice, "g") == 0)
        {
           return 7; break;
        }
        else if (boardchoice[8]=='H' &&strcmp(choice, "H") == 0 || boardchoice[8]=='H' &&strcmp(choice, "h") == 0)
        {
           return 8; break;
        }
        else if (boardchoice[9]=='I' &&strcmp(choice, "I") == 0 || boardchoice[9]=='I' &&strcmp(choice, "i") == 0)
        {
            return 9; break;
        }
        else
        {
            printf("\nInvalid position chosen");
            printf("\nPlease try again and choose a valid position\n");
        }
    }
}

void replacement()
{
    number = atoi(numchar);
    if (nochoice == 1 && pos[1] == 0)
        {
            pos[1] = number; playerno[1]= x;
            boardchoice[1]= '-';
        }
    else if (nochoice == 2 && pos[2] == 0)
        {
            pos[2] = number; playerno[2]= x;
            boardchoice[2]= '-';
        }
    else if (nochoice == 3 && pos[3] == 0 && playerno[3]==0)
        {
            pos[3] = number; playerno[3]= x;
            boardchoice[3]= '-';
        }
    else if (nochoice == 4 && pos[4] == 0)
        {
            pos[4] = number; playerno[4]= x;
            boardchoice[4]= '-';
        }
    else if (nochoice == 5 && pos[5] == 0)
        {
            pos[5] = number; playerno[5]= x;
            boardchoice[5]= '-';
        }
    else if (nochoice == 6 && pos[6] == 0)
        {
            pos[6] = number; playerno[6]= x;
            boardchoice[6]= '-';
        }
    else if (nochoice == 7 && pos[7] == 0)
        {
            pos[7] = number; playerno[7]= x;
            boardchoice[7]= '-';
        }
    else if (nochoice == 8 && pos[8] == 0)
        {
            pos[8] = number; playerno[8]= x;
            boardchoice[8]= '-';
        }
    else if (nochoice == 9 && pos[9] == 0)
        {
            pos[9] = number; playerno[9]= x;
            boardchoice[9]= '-';
        }
}
void winner()
{
    i=checkifsomeonewon();
    if (i == 1)
       {printf("==>\a Yay Player %d won!!!! CONGRATULATIONS!!! ",x); }
    else
       {printf("==>\a Oh no! Nobody won! It's a draw"); getch();}
}
