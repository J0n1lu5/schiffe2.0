#ifndef ATTACK_H
#define ATTACK_H

#include <stm32f0xx.h>
#include <stdbool.h>


void pewpew (uint8_t x,uint8_t y);
void ranndom_attack(uint8_t *grid_opponent);
bool check_shot (uint8_t *grid_opponent,uint8_t x, uint8_t y);
void smart_shot (uint8_t *grid_opponent,uint8_t *x,uint8_t *y);

#endif
