//#######################################
//#######################################
//#######################################
//#######################################
//############TODOLIST###################
//        dual player
//        zombie movement
//        zombie speed
//        zombie number
//        zombie size
//        zombie score
//        zombie gameover
//        zombie continue
//        zombie exit
//        zombie menu
//        zombie restart
//        zombie pause
//        zombie sound
//        zombie music
//        zombie image
//        zombie animation
//        zombie level
//        zombie difficulty
//        zombie time
//        zombie save
//        zombie load
//        zombie setting
//        zombie help
//        zombie about




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int SIZE=3;


void draw(int zombieX, int zombieY, int player0X, int player0Y, int player1X, int player1Y){
    system("cls");
    
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if(j==zombieX&&i==zombieY){
                if(j==player0X&&i==player0Y||j==player1X&&i==player1Y)printf("X ");
                else printf("Z ");
            }else if(j==player0X&&i==player0Y&&j==player1X&&i==player1Y){
                printf("P ");
            }else if(j==player0X&&i==player0Y){
                printf("0 ");
            }else if(j==player1X&&i==player1Y){
                printf("1 ");
            }else{
                printf(". ");
            }
        }
        printf("\n");
    }
}


int main(void){
    int score = 0;
    int zombieX, zombieY;
    int player0X=0, player0Y=0;
    int player1X=100, player1Y=100;
    int select=0;
    char move;
    //bool gameover=false;
    int mode=1;
    int p0score=0;
    int p1score=0;

    printf("######################\n");
    printf("### Hit the zombie ###\n");
    printf("####### 1  Play ######\n");
    printf("####### 2  Dual ######\n");
    printf("####### 3  Size ######\n");
    printf("####### 4  Exit ######\n");
    printf("######################\n");
    scanf(" %d", &select);
    while(select != 1 && select != 2 && select != 3 && select != 4) {
        printf("Enter a valid option: ");
        scanf(" %d", &select);
    }
    if(select == 3) {
        system("cls");
        printf("Enter the size of the board: ");
        scanf(" %d", &SIZE);
        printf("\nApply to which mode? (1/2):");
        scanf(" %d", &mode);
    } else if(select == 4) {
        return 0;
    } else if(select == 2) {
        mode=2;
        
    } else if(select == 1) {    
        mode=1;

    }
    srand(time(NULL));

    zombieX=rand()%SIZE;
    zombieY=rand()%SIZE;

    if(mode==1){
        player1X=100;
        player1Y=100;
    }else if(mode==2){
        player1X=SIZE-1;
        player1Y=SIZE-1;
    }


    while(mode==1){
        draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y);
        printf("Score: %d\n", score);
        move=getch();
        
        
        switch(move){
            case 'w':
                if(player0Y>0)player0Y--;
                break;
            case 's':
                if(player0Y<SIZE-1)player0Y++;
                break;
            case 'a':
                if(player0X>0)player0X--;
                break;
            case 'd':
                if(player0X<SIZE-1)player0X++;
                break;
            case 'f':
                if(player0X==zombieX&&player0Y==zombieY){
                    ++score;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                }else{
                    printf("Game Over! Your score: %d\n", score);
                    printf("Continue? (y/n): ");
                    scanf(" %c", &move);
                    while(move != 'y' && move != 'n') {
                        printf("Enter a valid option: ");
                        scanf(" %c", &move);
                    }
                    if(move=='n')return 0;
                    else if(move=='y'){
                        score=0;
                        player0X=0;
                        player0Y=0;
                        zombieX=rand()%SIZE;
                        zombieY=rand()%SIZE;
                    }
                }
                break;
            case 'q':
                printf("Game Over! Your score: %d\n", score);
                printf("Continue? (y/n): ");
                scanf(" %c", &move);
                while(move != 'y' && move != 'n') {
                    printf("Enter a valid option: ");
                    scanf(" %c", &move);
                }
                if(move=='n')return 0;
                else if(move=='y'){
                    score=0;
                    player0X=0;
                    player0Y=0;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                }
                break;
            
        }

    }


    while(mode==2){
        
        draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y);
        printf("P0 Score: %d\n", p0score);
        printf("P1 Score: %d\n", p1score);
        move=getch();
        
        
        switch(move){
            case 'w':
                if(player0Y>0)player0Y--;
                break;
            case 's':
                if(player0Y<SIZE-1)player0Y++;
                break;
            case 'a':
                if(player0X>0)player0X--;
                break;
            case 'd':
                if(player0X<SIZE-1)player0X++;
                break;
            case 'f':
                if(player0X==zombieX&&player0Y==zombieY){
                    ++p0score;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                }else{
                    ++p1score;                          
                }
                break;
            case 'q':
                system("cls");
                printf("Game Over!\n");
                printf("P0 Score: %d\n", p0score);
                printf("P1 Score: %d\n", p1score);
                printf("Continue? (y/n): ");
                scanf(" %c", &move);
                while(move != 'y' && move != 'n') {
                    printf("Enter a valid option: ");
                    scanf(" %c", &move);
                }
                if(move=='n')return 0;
                else if(move=='y'){
                    p0score=0;
                    p1score=0;
                    player0X=0;
                    player0Y=0;
                    player1X=2;
                    player1Y=2;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                }
                break;
            case 'o':
                if(player1Y>0)player1Y--;
                break;
            case 'l':
                if(player1Y<SIZE-1)player1Y++;
                break;
            case 'k':
                if(player1X>0)player1X--;
                break;
            case ';':
                if(player1X<SIZE-1)player1X++;
                break;
            case 'j':
                if(player1X==zombieX&&player1Y==zombieY){
                    ++p1score;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                }else{
                    ++p0score;                          
                }
                break;
            case 'p':
                system("cls");
                printf("Game Over!\n");
                printf("P0 Score: %d\n", p0score);
                printf("P1 Score: %d\n", p1score);
                printf("Continue? (y/n): ");
                scanf(" %c", &move);
                while(move != 'y' && move != 'n') {
                    printf("Enter a valid option: ");
                    scanf(" %c", &move);
                }
                if(move=='n')return 0;
                else if(move=='y'){
                    p0score=0;
                    p1score=0;
                    player0X=0;
                    player0Y=0;
                    player1X=2;
                    player1Y=2;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                }
                break;
        }

    }



    return 0;
}





