#include "attack.h"

#include <stm32f0xx.h>
#include <stdbool.h>
#include <stdlib.h>

#define FIELD_SZ 10

void random_attack(uint8_t *enemy_grid,uint8_t *last_shot,uint8_t seed){
    srand(seed);
    uint8_t x = rand()%10;
    uint8_t y = rand()%10;
    //if (shot_check(enemy_grid,x,y))
    pewpew(x,y);
    enemy_grid[y*10+x]=1;
    last_shot[0]=x;
    last_shot[1]=y;
}

uint8_t shot_check (const uint8_t *enemy_grid,uint8_t x, uint8_t y){
    //check if we shot at that coordinate already
    if(enemy_grid[y*FIELD_SZ+x]!=0) {
        int c=1;
        return 1;
    }
    return 0;
}

void smart_shot (uint8_t *enemy_grid,uint8_t *x,uint8_t *y){
    //check bounderies
    uint8_t r=5;

    if (*x==0){
        if (*y==0){
            r=rand()%2;
            if (r==0) *x=*x+1;
            if (r==1) *y=*y+1;
        }
        if (*y==FIELD_SZ){
            r=rand()%2;
            if (r==0) *x=*x+1;
            if (r==1) *y=*y-1;
        }
        else{
            r=rand()%3;
            if (r==0) *x=*x+1;
            if (r==1) *y=*y-1;
            if (r==2) *y=*y+1;
        }
    }
    else if(*x==FIELD_SZ){
        if (*y==0){
            r=rand()%2;
            if (r==0) *x=*x-1;
            if (r==1) *y=*y+1;
        }
        if (*y==FIELD_SZ){
            r=rand()%2;
            if (r==0) *x=*x-1;
            if (r==1) *y=*y-1;
        }
        else{
            r=rand()%3;
            if (r==0) *x=*x-1;
            if (r==1) *y=*y-1;
            if (r==2) *y=*y+1;
        }
    }
    else{
        if (*y==0){
            r=rand()%3;
            if (r==0) *x=*x-1;
            if (r==1) *y=*y+1;
        }
        if (*y==FIELD_SZ){
            r=rand()%3;
            if (r==0) *x=*x-1;
            if (r==1) *y=*y-1;
        }
        else{
            r=rand()%4;
            if (r==0) *x=*x-1;
            if (r==1) *y=*y-1;
            if (r==2) *y=*y+1;
    }
    }

}

void pewpew (uint8_t x,uint8_t y){
    printf("BOOM%d%d\n",x,y);
}