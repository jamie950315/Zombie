#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

void drawThree(int zombieX, int zombieY, int zombie1X, int zombie1Y, int zombie2X, int zombie2Y,int SIZE){
    system("cls");
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if(j==zombieX&&i==zombieY||j==zombie1X&&i==zombie1Y||j==zombie2X&&i==zombie2Y){
                printf("§ ");
            }else{
                printf(". ");
            }
        }
        printf("\n");
    }
}





void draw(int zombieX, int zombieY, int player0X, int player0Y, int player1X, int player1Y, int SIZE){
    system("cls");
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if(j==zombieX&&i==zombieY){
                if(j==player0X&&i==player0Y||j==player1X&&i==player1Y)printf("φ ");
                else printf("§ ");
            }else if(j==player0X&&i==player0Y&&j==player1X&&i==player1Y){
                printf("∞ ");
            }else if(j==player0X&&i==player0Y){
                printf("α ");
            }else if(j==player1X&&i==player1Y){
                printf("ß ");
            }else{
                printf(". ");
            }
        }
        printf("\n");
    }
}

void moveZombie(int *zombieX, int *zombieY, int SIZE) {
    int direction=rand()%4;
    
    switch (direction) {
        case 0:if (*zombieY>0)(*zombieY)--;break;
        case 1:if (*zombieY<SIZE-1)(*zombieY)++;break;
        case 2:if (*zombieX>0)(*zombieX)--;break;
        case 3:if (*zombieX<SIZE-1)(*zombieX)++;break;
    }
}

void end(int*SIZE,char*move,int*mode,int*leave,int*score,int*hiScore,int*player0X,int*player0Y,int*zombieX,int*zombieY,int*passedTime,time_t*t){
    printf("\n");
    printf("## Game Over! ##\n");
    printf("Your score: %d\n", *score);
    printf("High Score: %d\n", *hiScore);
    printf("Continue? (y/n/m): ");
    scanf(" %c", &*move);
    while(*move != 'y' && *move != 'n'&& *move != 'm') {
        printf("\nEnter a valid option: ");
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
        *passedTime=0;
        *t=time(NULL);
    }
}

void endual(int*SIZE,char*move,int*mode,int*leave,int*winScore,int*p0score,int*p1score,int*player0X,int*player0Y,int*player1X,int*player1Y,int*zombieX,int*zombieY){
	printf("\n");
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
    printf("\nEnter a valid option: ");
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

int enterInt(int enterInt){
    while(1){
        if(scanf("%d",&enterInt)){
            break;
        }else{
            printf("\nEnter a valid option: ");
            while(getchar()!='\n');
        }
    }
   return enterInt;
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
    char zombieMove='n';

    time_t lastTime=time(NULL);
    int zombieDelay=1;

    bool timer=false;
    time_t t=time(NULL);
    int countdown=60;
    int passedTime=0;

    int prevX=100;
    int prevY=100;


    int zombie1X,zombie1Y,zombie2X,zombie2Y,zombie3X,zombie3Y,zombie4X,zombie4Y;
    int prev1X=100;
    int prev1Y=100;
    int prev2X=100;
    int prev2Y=100;
    int prev3X=100;
    int prev3Y=100;
    int prev4X=100;
    int prev4Y=100;

    int run=false;


    
    
	system("cls");
    printf("######################\n");
    printf("### Hit the zombie ###\n");
    printf("####### 1  Play ######\n");
    printf("####### 2  Chase #####\n");
    printf("####### 3  Dual ######\n");
    printf("####### 4 Option #####\n");
    printf("####### 5  Exit ######\n");
    printf("######################\n");

    mode=enterInt(mode);
    while(mode!=1&&mode!=2&&mode!=3&&mode!=4&&mode!=5&&mode!=6) {
        printf("\nEnter a valid option: ");
        mode=enterInt(mode);
    }

    if(mode==4){
        hiScore=0;
        system("cls");
        printf("Enter the size of the board: ");
        SIZE=enterInt(SIZE);
        printf("Make zombie move? (y/n): ");
        scanf(" %c", &zombieMove);
        while(zombieMove!='y'&&zombieMove!='n') {
            printf("\nEnter a valid option: ");
            scanf(" %c", &zombieMove);
        }
        if(zombieMove=='y'){
            printf("Enter the delay sec of the zombie (>=1) :");
            zombieDelay=enterInt(zombieDelay);
            while(zombieDelay<1) {
                printf("\nEnter a >=1 interger: ");
                zombieDelay=enterInt(zombieDelay);
            }
        }
        printf("Enable timer? (y/n): ");
        scanf(" %c", &move);
        while(move!='y'&&move!='n'){
            printf("\nEnter a valid option: ");
            scanf(" %c", &move);
        }
        if(move=='y') timer=true;
        else if(move=='n') timer=false;
        if(timer){
            printf("Enter countdown time: ");
            countdown=enterInt(countdown);
        }
        printf("Apply to which mode? (2/3):");
        mode=enterInt(mode);
        while(mode!=2&&mode!=3) {
            printf("\nEnter a valid option: ");
            mode=enterInt(mode);
        }
    }else if(mode==5){
        return 0;
    }else if(mode==6){
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
    if(mode==3){
        printf("Enter win score: ");
        winScore=enterInt(winScore);
    }
    
    srand(time(NULL));
    zombieX=rand()%SIZE;
    zombieY=rand()%SIZE;
    if(mode==2){
        player1X=100;
        player1Y=100;
    }else if(mode==3){
        player1X=SIZE-1;
        player1Y=SIZE-1;
    }
    if(mode==2){
        draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
        printf("Score: %d\n", score);
        if(timer)printf("Time left: %d\n", countdown-passedTime);
        t=time(NULL);
    }
    while(mode==2){
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
                    while(prevX==zombieX&&prevY==zombieY){
                        zombieX=rand()%SIZE;
                        zombieY=rand()%SIZE;
                    }
                    prevX=zombieX;
                    prevY=zombieY;
                }else{
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                	if(leave==1)return 0;
                }
                break;
            case 'q':
                end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                if(leave==1)return 0;
                break;
            }

            draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
            printf("Score: %d\n", score);
            if(timer)printf("Time left: %d\n", countdown-passedTime);

        }    
        if(zombieMove=='y'){
            time_t currentTime = time(NULL);
            if (difftime(currentTime, lastTime) >= zombieDelay) {
                moveZombie(&zombieX, &zombieY, SIZE);
                lastTime = currentTime;
                draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
                printf("Score: %d\n", score);
                if(timer)printf("Time left: %d\n", countdown-passedTime);

            }
        }
        if(timer){
            if(difftime(time(NULL),t)>=1){
                ++passedTime;
                if(passedTime>=countdown){
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                    if(leave==1)return 0;
                }
                t=time(NULL);
                draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
                printf("Score: %d\n", score);
                if(timer)printf("Time left: %d\n", countdown-passedTime);
            }
        }
    }
    if(mode==3){
        draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
        printf("P0 Score: %d\n", p0score);
        printf("P1 Score: %d\n", p1score);
        if(timer)printf("Time left: %d\n", countdown-passedTime);
        t=time(NULL);
    }
    while(mode==3){
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
                    ++p0score;
                    zombieX=rand()%SIZE;
                    zombieY=rand()%SIZE;
                    while(prevX==zombieX&&prevY==zombieY){
                        zombieX=rand()%SIZE;
                        zombieY=rand()%SIZE;
                    }
                    prevX=zombieX;
                    prevY=zombieY;
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
                    while(prevX==zombieX&&prevY==zombieY){
                        zombieX=rand()%SIZE;
                        zombieY=rand()%SIZE;
                    }
                    prevX=zombieX;
                    prevY=zombieY;
                }else{
                    ++p0score;                          
                }
                break;
            case 'p':
                endual(&SIZE,&move,&mode,&leave,&winScore,&p0score,&p1score,&player0X,&player0Y,&player1X,&player1Y,&zombieX,&zombieY);
        	if(leave==1)return 0;
                break;
            }
            if(p0score==winScore||p1score==winScore){
        	    endual(&SIZE,&move,&mode,&leave,&winScore,&p0score,&p1score,&player0X,&player0Y,&player1X,&player1Y,&zombieX,&zombieY);
        	    if(leave==1)return 0;
		    }
            draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
            printf("P0 Score: %d\n", p0score);
            printf("P1 Score: %d\n", p1score);
            if(timer)printf("Time left: %d\n", countdown-passedTime);

        }
        if(zombieMove=='y'){
            time_t currentTime = time(NULL);
            if (difftime(currentTime, lastTime) >= zombieDelay) {
                moveZombie(&zombieX, &zombieY, SIZE);
                lastTime = currentTime;
                draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
                printf("P0 Score: %d\n", p0score);
                printf("P1 Score: %d\n", p1score);
                if(timer)printf("Time left: %d\n", countdown-passedTime);

            }
        }
        if(timer){
            if(difftime(time(NULL),t)>=1){
                ++passedTime;
                if(passedTime>=countdown){
                    endual(&SIZE,&move,&mode,&leave,&winScore,&p0score,&p1score,&player0X,&player0Y,&player1X,&player1Y,&zombieX,&zombieY);
                    if(leave==1)return 0;
                }
                draw(zombieX, zombieY, player0X, player0Y, player1X, player1Y,SIZE);
                printf("P0 Score: %d\n", p0score);
                printf("P1 Score: %d\n", p1score);
                if(timer)printf("Time left: %d\n", countdown-passedTime);
                t=time(NULL);
            }
        }
        
    }



    if(mode==1){
        player0X=0;
        player0Y=SIZE;
        player1X=100;
        player1Y=100;
        zombieX=rand()%SIZE;
        zombieY=0;
        zombie1X=rand()%SIZE;
        zombie1Y=-1;
        zombie2X=rand()%SIZE;
        zombie2Y=-2;

        run=false;
        
        drawThree(zombieX,zombieY,zombie1X,zombie1Y,zombie2X,zombie2Y,SIZE);
        printf("Score: %d\n", score);
        if(timer)printf("Time left: %d\n", countdown-passedTime);
        t=time(NULL);
    }


    while(mode==1){

            if(kbhit()){
            move=getch();
            switch(move){
       
            case 's':
                if(1==zombieX&&player0Y-1==zombieY){
                    ++score;
                    zombieX=rand()%SIZE;
                    zombieY=0;
        
                    while(prevX==zombieX){
                        zombieX=rand()%SIZE;
                    }
                    prevX=zombieX;

                    zombie1Y++;
                    zombie2Y++;
                }else if((1==zombie1X&&player0Y-1==zombie1Y)){
                    ++score;
                    zombie1X=rand()%SIZE;
                    zombie1Y=0;
                    while(prev1X==zombie1X){
                        zombie1X=rand()%SIZE;
                    }
                    prev1X=zombie1X;

                    zombieY++;
                    zombie2Y++;

                }else if((1==zombie2X&&player0Y-1==zombie2Y)){
                    ++score;
                    zombie2X=rand()%SIZE;
                    zombie2Y=0;
                    while(prev2X==zombie2X){
                        zombie2X=rand()%SIZE;
                    }
                    prev2X=zombie2X;

                    zombieY++;
                    zombie1Y++;


                }
                
                
                
                
                else{
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                	if(leave==1)return 0;

                    player0X=0;
                    player0Y=SIZE;
                    player1X=100;
                    player1Y=100;
                    zombieX=rand()%SIZE;
                    zombieY=0;
                    zombie1X=rand()%SIZE;
                    zombie1Y=-1;
                    zombie2X=rand()%SIZE;
                    zombie2Y=-2;
                    run=false;
                    
                }
                break;
        
            case 'a':
                if(0==zombieX&&player0Y-1==zombieY){
                    ++score;
                    zombieX=rand()%SIZE;
                    zombieY=0;
        
                    while(prevX==zombieX){
                        zombieX=rand()%SIZE;
                    }
                    prevX=zombieX;
                    zombie1Y++;
                    zombie2Y++;
                }else if((0==zombie1X&&player0Y-1==zombie1Y)){
                    ++score;
                    zombie1X=rand()%SIZE;
                    zombie1Y=0;
                    while(prev1X==zombie1X){
                        zombie1X=rand()%SIZE;
                    }
                    prev1X=zombie1X;
                    zombieY++;
                    zombie2Y++;
                }else if((0==zombie2X&&player0Y-1==zombie2Y)){
                    ++score;
                    zombie2X=rand()%SIZE;
                    zombie2Y=0;
                    while(prev2X==zombie2X){
                        zombie2X=rand()%SIZE;
                    }
                    prev2X=zombie2X;

                    zombieY++;
                    zombie1Y++;
                }
        



                else{
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                	if(leave==1)return 0;

                    player0X=0;
                    player0Y=SIZE;
                    player1X=100;
                    player1Y=100;
                    zombieX=rand()%SIZE;
                    zombieY=0;
                    zombie1X=rand()%SIZE;
                    zombie1Y=-1;
                    zombie2X=rand()%SIZE;
                    zombie2Y=-2;
                    run=false;
                }
                break;
            case 'd':
                if(2==zombieX&&player0Y-1==zombieY){
                    ++score;
                    zombieX=rand()%SIZE;
                    zombieY=0;
        
                    while(prevX==zombieX){
                        zombieX=rand()%SIZE;
                    }
                    prevX=zombieX;
                    zombie1Y++;
                    zombie2Y++;
                }else if((2==zombie1X&&player0Y-1==zombie1Y)){
                    ++score;
                    zombie1X=rand()%SIZE;
                    zombie1Y=0;
                    while(prev1X==zombie1X){
                        zombie1X=rand()%SIZE;
                    }
                    prev1X=zombie1X;
                    zombieY++;
                    zombie2Y++;
                }else if((2==zombie2X&&player0Y-1==zombie2Y)){
                    ++score;
                    zombie2X=rand()%SIZE;
                    zombie2Y=0;
                    while(prev2X==zombie2X){
                        zombie2X=rand()%SIZE;
                    }
                    prev2X=zombie2X;

                    zombieY++;
                    zombie1Y++;
                }
                
                
                
                
                else{
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                	if(leave==1)return 0;

                    player0X=0;
                    player0Y=SIZE;
                    player1X=100;
                    player1Y=100;
                    zombieX=rand()%SIZE;
                    zombieY=0;
                    zombie1X=rand()%SIZE;
                    zombie1Y=-1;
                    zombie2X=rand()%SIZE;
                    zombie2Y=-2;
                    run=false;
                }
                break;
        /*
            case 'f':
                if(player0X==zombieX&&player0Y==zombieY){
                    ++score;
                    zombieX=rand()%SIZE;
                    zombieY=0;
        
                    while(prevX==zombieX){
                        zombieX=rand()%SIZE;
                    }
                    prevX=zombieX;
        
                }else{
                    //if(score>hiScore)hiScore=score;
                    //end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                	//if(leave==1)return 0;
                }
                break;
        */
            case 'q':
                end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                if(leave==1)return 0;
                break;
            }

            drawThree(zombieX,zombieY,zombie1X,zombie1Y,zombie2X,zombie2Y,SIZE);
            printf("Score: %d\n", score);
            if(timer)printf("Time left: %d\n", countdown-passedTime);

        }    
        if(!run){
            time_t currentTime = time(NULL);
            if (difftime(currentTime, lastTime) >= 1) {
                
                zombieY++;
                if(zombieY==SIZE){
                    zombieX=rand()%SIZE;
                    zombieY=0;
                    while(prevX==zombieX){
                        zombieX=rand()%SIZE;
                    }
                    prevX=zombieX;
                    run=true;
                }

                zombie1Y++;
                if(zombie1Y==SIZE){
                    zombie1X=rand()%SIZE;
                    zombie1Y=0;
                    while(prev1X==zombie1X){
                        zombie1X=rand()%SIZE;
                    }
                    prev1X=zombie1X;
                }

                zombie2Y++;
                if(zombie2Y==SIZE){
                    zombie2X=rand()%SIZE;
                    zombie2Y=0;
                    while(prev2X==zombie2X){
                        zombie2X=rand()%SIZE;
                    }
                    prev2X=zombie2X;
                    
                }

                

                //moveZombie(&zombieX, &zombieY, SIZE);
                lastTime = currentTime;
                drawThree(zombieX,zombieY,zombie1X,zombie1Y,zombie2X,zombie2Y,SIZE);
                printf("Score: %d\n", score);
                if(timer)printf("Time left: %d\n", countdown-passedTime);

            }
        
        }
        
        if(timer){
            if(difftime(time(NULL),t)>=1){
                ++passedTime;
                if(passedTime>=countdown){
                    if(score>hiScore)hiScore=score;
                    end(&SIZE,&move,&mode,&leave,&score,&hiScore,&player0X,&player0Y,&zombieX,&zombieY,&passedTime,&t);
                    if(leave==1)return 0;
                }
                t=time(NULL);
                drawThree(zombieX,zombieY,zombie1X,zombie1Y,zombie2X,zombie2Y,SIZE);
                printf("Score: %d\n", score);
                if(timer)printf("Time left: %d\n", countdown-passedTime);
            }
        }



    }


}
    return 0;
}





