#include <stm32f0xx.h>
#include "mci_clock.h"
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "attack.h"


#define DEBUG

// This is a simple macro to print debug messages of DEBUG is defined
#ifdef DEBUG
  #define LOG( msg... ) printf( msg );
#else
  #define LOG( msg... ) ;
#endif

// Select the Baudrate for the UART
#define BAUDRATE 9600


// For supporting printf function we override the _write function to redirect the output to UART
int _write( int handle, char* data, int size ) {
    int count = size;
    while( count-- ) {
        while( !( USART2->ISR & USART_ISR_TXE ) ) {};
        USART2->TDR = *data++;
    }
    return size;
}


void init() {
    // Configure the system clock to 48MHz
    EPL_SystemClock_Config();

    // Enable peripheral  GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Enable peripheral  USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Configure PA2 as USART2_TX using alternate function 1
    GPIOA->MODER |= GPIO_MODER_MODER2_1;
    GPIOA->AFR[0] |= 0b0001 << (4*2);


    // Configure PA3 as USART2_RX using alternate function 1
    GPIOA->MODER |= GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= 0b0001 << (4*3);

    // Configure the UART Baude rate Register
    USART2->BRR = (APB_FREQ / BAUDRATE);
    // Enable the UART using the CR1 register
    USART2->CR1 |= ( USART_CR1_RE | USART_CR1_TE | USART_CR1_UE );
}




int main(void){

init();

    char received_string[20]={0};
    uint8_t enemy_grid[10*10]={0};
    uint8_t grid_player[10*10]={0};
    uint8_t enemy_shot_map [10*10]={0};
    char checksum[10]={'0'};
    uint8_t state =0;
    uint8_t i=0;
    uint8_t last_shot[2]={0};
    uint8_t seed=0;

    for(;;){
        seed++;

        //receive message
        if (USART2->ISR & USART_ISR_RXNE){
            char received_char = USART2->RDR;
            received_string[i] = received_char;
            i++;
            if (received_char == '\n'){
                //LOG("%s",received_string);
                state=check_message(received_string);
                memset(received_string, 0, sizeof(received_string));
                i=0;

            }
        }



        if (received_string[0]=='0') state=2;
        //prozess start message as player 2
        if (state==1) {
            build_grid_stupid(grid_player);
            init_shotmap(grid_player,enemy_shot_map);
            //memset(checksum, '0', sizeof(checksum));
            grid_checksum(grid_player,checksum);

            state=0;
            //memset(received_string, 0, sizeof(received_string));
        //send startmessage as player2
        }else if (state==2){
            printf("START52113578\n");
            state=0;
            //memset(received_string, 0, sizeof(received_string));
        //prozess enemy shot
        }else if (state==3){
            if(check_shot(received_string,grid_player,enemy_shot_map)==1) {
                printf("T\n");
            }else {
                printf("W\n");
            }
            //check loss
            check_loss(enemy_shot_map);
            if (seed==99) {
                asm("nop");
            }
            random_attack(enemy_grid,last_shot,seed);
            state=0;
            memset(received_string, 0, sizeof(received_string));
        }else if (state==4){
            if (received_string[0]=='T') {
                enemy_grid[last_shot[1]*10+last_shot[0]]=2;
                if (check_win(enemy_grid)==1) state=7;

            }
            state=0;
            memset(received_string, 0, sizeof(received_string));
        }else if (state==5) {
            state=0;
            memset(received_string, 0, sizeof(received_string));
        }

    }
}
