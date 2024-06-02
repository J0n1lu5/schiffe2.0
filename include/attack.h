#ifndef ATTACK_H
#define ATTACK_H

#include <stm32f0xx.h>
#include <stdbool.h>
#include <stdlib.h>

void pewpew (uint8_t x,uint8_t y);
void random_attack(uint8_t *grid_opponent,uint8_t *last_shot);
uint8_t shot_check (const uint8_t *enemy_grid,uint8_t x, uint8_t y);
void smart_shot (uint8_t *grid_opponent,uint8_t *x,uint8_t *y);

#endif
