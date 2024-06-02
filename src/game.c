#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32f091xc.h"

uint8_t check_message(const char *received) {
    if (strncmp(received, "START", 5) == 0) {
        //printf("Start message received\n");
        // Startnachricht verarbeiten
        return 1;
    } else if (strncmp(received, "CS", 2) == 0) {
        //printf("Checksum message received: %s\n", received);
        // Spielfeldchecksummen-Nachricht verarbeiten
        return 2;
    } else if (strncmp(received, "BOOM", 4) == 0) {
        //printf("Shot message received: %s\n", received);
        // Schussnachricht verarbeiten
        return 3;
    } else if (received[0] == 'W' || received[0] == 'T') {
        //printf("Shot report received: %s\n", received);
        // Schussbericht verarbeiten
        return 4;
    } else if (strncmp(received, "SF", 2) == 0) {
        printf("Field message received: %s\n", received);
        // Spielfeldnachricht verarbeiten
        return 5;
    } else {
        //printf("Unknown message format: %s\n", received);
        // Unbekanntes Nachrichtenformat verarbeiten
        return 6;
    }
}

uint8_t check_loss (const uint8_t *enemy_shot_map) {
    for (int i=0;i<sizeof(enemy_shot_map);i++) {
        if (enemy_shot_map[i]!=0) return 0;
    }
    return 1;
}

uint8_t check_win (const uint8_t *enemy_grid) {
    uint8_t count=0;
    for (uint8_t i=0;i<sizeof(enemy_grid);i++) {
        if (enemy_grid[i]==2) count++;
    }
    if (count==30) return 1;
    return 0;
}