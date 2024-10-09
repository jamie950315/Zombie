#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void draw(int zombieX, int zombieY, int player0X, int player0Y, int player1X, int player1Y, int SIZE){
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

void moveZombie(int *zombieX, int *zombieY, int SIZE) {
    int direction = rand() % 4;
    
    switch (direction) {
        case 0:if (*zombieY>0)(*zombieY)--;break;
        case 1:if (*zombieY<SIZE-1)(*zombieY)++;break;
        case 2:if (*zombieX>0)(*zombieX)--;break;
        case 3:if (*zombieX<SIZE-1)(*zombieX)++;break;
    }
}

void end(int*SIZE,char*move,int*mode,int*leave,int*score,int*hiScore,int*player0X,int*player0Y,int*zombieX,int*zombieY){
    printf("\n");
    printf("## Game Over! ##\n");
    printf("Your score: %d\n", *score);
    printf("High Score: %d\n", *hiScore);
    printf("Continue? (y/n/m): ");
    scanf(" %c", &*move);
    while(*move != 'y' && *move != 'n'&& *move != 'm') {
        printf("Enter a valid option: ");
        scanf(" %c", &*move);
    }
    if(*move=='n')*leave=1;
    else if(*move=='m')*mode=0;
    else if(*move=='y'){
        *score=0;
        *player0X=0;
        *player0Y=0;
        *zombieX=rand()%*SIZE;
        *zombieY=rand()%*SIZE;
    }
}
void endual(int*SIZE,char*move,int*mode,int*leave,int*winScore,int*p0score,int*p1score,int*player0X,int*player0Y,int*player1X,int*player1Y,int*zombieX,int*zombieY){
	system("cls");
	if(*p0score==*winScore)printf("P0 Wins!\n");
	else if(*p1score==*winScore)printf("P1 Wins!\n");
	else{
    	printf("## Game Over! ##\n");
    	printf("P0 Score: %d\n", *p0score);
    	printf("P1 Score: %d\n", *p1score);
	}
    printf("Continue? (y/n/m): ");
    scanf(" %c", &*move);
    while(*move != 'y' && *move != 'n' && *move != 'm') {
    printf("Enter a valid option: ");
    	scanf(" %c", &*move);
    }
    if(*move=='n')*leave=1;
    else if(*move=='m')*mode=0;
    else if(*move=='y'){
    	*p0score=0;
    	*p1score=0;
    	*player0X=0;
    	*player0Y=0;
    	*player1X=*SIZE-1;
    	*player1Y=*SIZE-1;
    	*zombieX=rand()%*SIZE;
    	*zombieY=rand()%*SIZE;
    }
}

int main(void){
    int mode=0;
    int hiScore=0;
while(mode ==0){
    int score = 0;
    int zombieX, zombieY;
    int player0X=0, player0Y=0;
    int player1X=100, player1Y=100;
    char move;    
    int p0score=0;
    int p1score=0;
    int winScore=0;
    int leave=0;
    int SIZE=3;

    time_t lastTime=time(NULL);
    const int zombieDelay=1;
    
	system("cls");
    printf("######################\n");
    printf("### Hit the zombie ###\n");
    printf("####### 1  Play ######\n");
    printf("####### 2  Dual ######\n");
    printf("####### 3  Size ######\n");
    printf("####### 4  Exit ######\n");
    printf("######################\n");
    scanf(" %d", &mode);
    while(mode!=1&&mode!=2&&mode!=3&&mode!=4&&mode!=5) {
        printf("Enter a valid option: ");
        scanf(" %d", &mode);
    }
    if(mode==3){
        system("cls");
        printf("Enter the size of the board: ");
        scanf(" %d",&SIZE);
        printf("\nApply to which mode? (1/2):");
        scanf(" %d",&mode);
        while(mode!=1&&mode!=2) {
        printf("Enter a valid option: ");
        scanf(" %d", &mode);
    }
    }else if(mode==4){
        return 0;
    }else if(mode==5){
        system("cls");
        printf("######################\n");
        printf("### Hit the zombie ###\n");
        printf("###  NTUST PROJECT ###\n");
        printf("######################\n");
        printf("#####	CREDIT	 #####\n");
        printf("##### Jamie Chen #####\n");
        printf("#####  OCT.2024  #####\n");
        printf("######################\n");
        printf("\n");
        printf("Press any key to menu:\n");
        scanf(" %c",&move);
        mode=0;
    }    
    if(mode==2){
        printf("Enter win score: ");
        scanf(" %d",&winScore);
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
    if(mode==1){
        draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
        printf("Score: %d\n", score);
    }
    while(mode==1){
        
        if(kbhit()){
            
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
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY);
                	if(leave==1)return 0;
                }
                break;
            case 'q':
                end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY);
                if(leave==1)return 0;
                break;
            }

            draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
            printf("Score: %d\n", score);
        }        
        time_t currentTime = time(NULL);
        if (difftime(currentTime, lastTime) >= zombieDelay) {
            moveZombie(&zombieX, &zombieY, SIZE);
            lastTime = currentTime;
            draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
            printf("Score: %d\n", score);
        }
    }

    while(mode==2){
        draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
        printf("P0 Score: %d\n", p0score);
        printf("P1 Score: %d\n", p1score);
        if(p0score==winScore||p1score==winScore){
        	endual(&SIZE,&move,&mode,&leave,&winScore,&p0score,&p1score,&player0X,&player0Y,&player1X,&player1Y,&zombieX,&zombieY);
        	if(leave==1)return 0;
		}
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
                endual(&SIZE,&move,&mode,&leave,&winScore,&p0score,&p1score,&player0X,&player0Y,&player1X,&player1Y,&zombieX,&zombieY);
        		if(leave==1)return 0;
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
                endual(&SIZE,&move,&mode,&leave,&winScore,&p0score,&p1score,&player0X,&player0Y,&player1X,&player1Y,&zombieX,&zombieY);
        	if(leave==1)return 0;
                break;
        }
    }
}
    return 0;
}





