#include<stdio.h>

int calc(int mode){
    ++mode;
    return mode;

}

int main(void){

    int mode=0;
    mode=calc(mode);
    printf("%d\n",mode);



    return 0;
}

