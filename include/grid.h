#ifndef GRID_H
#define GRID_H

#include <stm32f0xx.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void build_grid_stupid (uint8_t *grid_player);
void generate_grid(uint8_t *grid_player);
uint16_t place_ship(uint8_t *grid_player, uint8_t length);
bool is_valid_position(uint8_t *grid_player, uint8_t x, uint8_t y, uint8_t length, bool vertical);
void print_grid(const uint8_t *grid_player);
void grid_checksum (const uint8_t *grid_player,char *checksum);
uint8_t check_shot(const char *received_string,const uint8_t *grid_player, uint8_t *enemy_shot_map);
void init_shotmap(const uint8_t *grid_player,uint8_t *enemy_shot_map);
#endif
