#include <stdio.h>

int main() {
    int i=0;

    while(1){
        if(scanf("%d",&i)){
            break;
        }else{
            printf("Invalid input\n");
            while(getchar()!='\n');
        }
    }
    printf("You entered: %d\n",i);



    return 0;
}
