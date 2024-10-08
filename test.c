#include <stdio.h>

void calc(int *i, int *j){
    *i+=2;
    *j+=3;
}

int main(void){
    int i=0;
    int j=5;
    calc(&i,&j);
    printf("%d %d\n",i,j);
}
