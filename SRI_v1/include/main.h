#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>

#define FLAG_RUN_EVENT_QUEUE  0

//! The interval between each PING is sent from both computer and SRI interface
#define SRI_PING_INTERVAL     1000

//! The timeout limit to know we have lost connection to the computer
#define SRI_PING_TIMEOUT_LIMIT     5000

//! The size of the RX FIFO of the UART
#define UART_RX_FIFO_SIZE 16
//! The size of the TX FIFO of the UART
#define UART_TX_FIFO_SIZE 16

typedef struct {
  uint8_t various;
} struct_flags;

#define BUTTON_ENCODER_INDEX  0
#define BUTTON1_INDEX         1
#define BUTTON2_INDEX         2
#define BUTTON3_INDEX         3

void main_eeprom_write_in_progress(void);
void main_eeprom_write_done(void);

void event_add_message(void (*func), uint16_t offset, uint8_t id, uint8_t priority);

void main_timer0_tick(void);
void main_timer1_tick(void);

void delay_ms(uint32_t time);
void delay_10us(uint32_t time);

#endif
