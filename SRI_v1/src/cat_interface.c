#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "LPC17xx.h"
#include "lpc_types.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "board.h"
#include "cat_interface.h"
#include "setting_structs.h"
#include "settings.h"
#include "misc.h"
#include "status.h"
#include "main.h"

#define CAT_DATA_DEBUG
//#define CAT_COMM_DEBUG

struct_cat_interface cat_interface;

uint16_t counter_cat_interface_tick = 0;
uint16_t counter_cat_interface_poll_tick = 0;

uint8_t *cat_radio_rx_buffer_ptr;
uint8_t cat_radio_rx_buffer_pos = 0;

void cat_interface_init_radio_uart(uint32_t baudrate, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t jumper_cts_rts) {
  UART_DeInit(LPC_UART1);

  // UART Configuration structure variable
  UART_CFG_Type UARTConfigStruct;
  // UART FIFO configuration Struct variable
  UART_FIFO_CFG_Type UARTFIFOConfigStruct;
  // Pin configuration for UART1
  PINSEL_CFG_Type PinCfg;

  //******** Init UART towards the radio ********
  PinCfg.Funcnum = 1;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 15;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 16;
  PINSEL_ConfigPin(&PinCfg);

  UART_ConfigStructInit(&UARTConfigStruct);

  UARTConfigStruct.Baud_rate = baudrate;

  if (stopbits == SETTING_CAT_STOPBITS_TWO)
    UARTConfigStruct.Stopbits = UART_STOPBIT_2;
  else
    UARTConfigStruct.Stopbits = UART_STOPBIT_1;

  if (parity == SETTING_CAT_PARITY_EVEN)
    UARTConfigStruct.Parity = UART_PARITY_EVEN;
  else if (parity == SETTING_CAT_PARITY_ODD)
    UARTConfigStruct.Parity = UART_PARITY_ODD;
  else
    UARTConfigStruct.Parity = UART_PARITY_NONE;

  cat_interface.jumper_cts_rts = jumper_cts_rts;

  // Initialize UART1 peripheral with given to corresponding parameter
  UART_Init(LPC_UART1, &UARTConfigStruct);

  /* Initialize FIFOConfigStruct to default state:
   *        - FIFO_DMAMode = DISABLE
   *        - FIFO_Level = UART_FIFO_TRGLEV0
   *        - FIFO_ResetRxBuf = ENABLE
   *        - FIFO_ResetTxBuf = ENABLE
   *        - FIFO_State = ENABLE
   */
  UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

  // Initialize FIFO for UART1 peripheral
  UART_FIFOConfig(LPC_UART1, &UARTFIFOConfigStruct);


  // Enable UART Transmit
  UART_TxCmd(LPC_UART1, ENABLE);
}

void cat_interface_init_computer_uart(uint32_t baudrate, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t jumper_cts_rts) {
  UART_DeInit(LPC_UART0);

  // UART Configuration structure variable
  UART_CFG_Type UARTConfigStruct;
  // UART FIFO configuration Struct variable
  UART_FIFO_CFG_Type UARTFIFOConfigStruct;
  // Pin configuration for UART1
  PINSEL_CFG_Type PinCfg;

  //******** Init UART towards the computer ********
  PinCfg.Funcnum = 1;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Pinnum = 2;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 3;
  PINSEL_ConfigPin(&PinCfg);

  UART_ConfigStructInit(&UARTConfigStruct);

  UARTConfigStruct.Baud_rate = baudrate;

  if (stopbits == SETTING_CAT_STOPBITS_TWO)
    UARTConfigStruct.Stopbits = UART_STOPBIT_2;
  else
    UARTConfigStruct.Stopbits = UART_STOPBIT_1;

  if (parity == SETTING_CAT_PARITY_EVEN)
    UARTConfigStruct.Parity = UART_PARITY_EVEN;
  else if (parity == SETTING_CAT_PARITY_ODD)
    UARTConfigStruct.Parity = UART_PARITY_ODD;
  else
    UARTConfigStruct.Parity = UART_PARITY_NONE;

  cat_interface.jumper_cts_rts = jumper_cts_rts;

  // Initialize UART0 peripheral with given to corresponding parameter
  UART_Init(LPC_UART0, &UARTConfigStruct);

  /* Initialize FIFOConfigStruct to default state:
   *        - FIFO_DMAMode = DISABLE
   *        - FIFO_Level = UART_FIFO_TRGLEV0
   *        - FIFO_ResetRxBuf = ENABLE
   *        - FIFO_ResetTxBuf = ENABLE
   *        - FIFO_State = ENABLE
   */
  UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

  // Initialize FIFO for UART0 peripheral
  UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);

  // Enable UART Transmit
  UART_TxCmd(LPC_UART0, ENABLE);
}

void cat_interface_init(uint32_t baudrate, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t jumper_cts_rts) {
  cat_interface_init_computer_uart(baudrate, stopbits, parity, flow_control, jumper_cts_rts);
  cat_interface_init_radio_uart(baudrate, stopbits, parity, flow_control, jumper_cts_rts);

#ifdef CAT_COMM_DEBUG
  PRINTF("CAT: COMM_DEBUG >> BAUDRATE %i\n",baudrate);
  PRINTF("CAT: COMM_DEBUG >> STOPBITS %i\n",stopbits);
#endif

  cat_interface.poll_interval = settings_get_cat_poll_rate();
  cat_interface.retrieve_mode = settings_get_cat_retrieve_type();
  cat_interface.radio_model = settings_get_radio_model();
  cat_interface.flags = 0;

  cat_radio_rx_buffer_ptr = (uint8_t *)&(cat_interface.radio_rx_buffer);
  counter_cat_interface_poll_tick = 0;
  cat_radio_rx_buffer_pos = 0;
}

void cat_interface_send_radio_request(void) {
  if (cat_interface.radio_model == RADIO_MODEL_YAESU_FT950) {
    cat_interface_uart_radio_tx_buf(3,(uint8_t *)"FA;");

    //Point to the beginning of the buffer
    cat_radio_rx_buffer_ptr = (uint8_t *)&(cat_interface.radio_rx_buffer);
    cat_radio_rx_buffer_pos = 0;
  }
}

uint8_t cat_interface_parse_buffer(uint8_t *buffer, uint8_t length) {
  #ifdef CAT_DATA_DEBUG
    PRINTF("LENGTH: %i\n",length);
  #endif

  if (length != 27)
    return(0);

  uint32_t freq_vfoA = 0;

  freq_vfoA =  (buffer[5]-48)  * 10000000;
  freq_vfoA += (buffer[6]-48)  * 1000000;
  freq_vfoA += (buffer[7]-48)  * 100000;
  freq_vfoA += (buffer[8]-48)  * 10000;
  freq_vfoA += (buffer[9]-48)  * 1000;
  freq_vfoA += (buffer[10]-48) * 100;
  freq_vfoA += (buffer[11]-48) * 10;
  freq_vfoA += (buffer[12]-48);

  status_set_vfoA_freq(freq_vfoA);

  return(1);
}

void cat_interface_execute(void) {
  uint32_t rx_len = 0;

  if (cat_interface.flags & (1<<CAT_INTERFACE_FLAG_POLL_RADIO)) {
    cat_interface_send_radio_request();

    cat_interface.flags &= ~(1<<CAT_INTERFACE_FLAG_POLL_RADIO);
  }

  if ((counter_cat_interface_tick % 10) == 0) {
    rx_len = cat_interface_uart_poll_radio_rx(cat_radio_rx_buffer_ptr,CAT_INTERFACE_RX_BUFFER_LENGTH-cat_radio_rx_buffer_pos);

    if (rx_len > 0) {
      //Parse the received data to see if it is valid data, if so it returns 1 and we allow normal transmission again
      if (cat_interface_parse_buffer(cat_interface.radio_rx_buffer,cat_radio_rx_buffer_pos+rx_len)) {
        cat_radio_rx_buffer_pos = 0;
        cat_radio_rx_buffer_ptr = cat_interface.radio_rx_buffer;
      }
      else { //If not, we need to parse again
        cat_radio_rx_buffer_pos += rx_len;
        cat_radio_rx_buffer_ptr += rx_len;

        if (cat_radio_rx_buffer_pos >= CAT_INTERFACE_RX_BUFFER_LENGTH) {
          cat_radio_rx_buffer_pos = 0;
          cat_radio_rx_buffer_ptr = (uint8_t *)&(cat_interface.radio_rx_buffer);
        }
      }
    }
  }
}

uint32_t cat_interface_uart_poll_radio_rx(uint8_t *buffer, uint16_t length) {
  return(UART_Receive(LPC_UART1, buffer, length, NONE_BLOCKING));
}

void cat_interface_uart_radio_tx_buf(uint8_t length, uint8_t *data) {
  UART_Send(LPC_UART1, data, length, BLOCKING);
}

void cat_interface_uart_radio_tx(uint8_t data) {
  UART_SendByte(LPC_UART1,data);
}

uint32_t cat_interface_uart_poll_computer_rx(uint8_t *buffer, uint16_t length) {
  return(UART_Receive(LPC_UART0, buffer, length, NONE_BLOCKING));
}

void cat_interface_uart_computer_tx_buf(uint8_t length, uint8_t *data) {
  UART_Send(LPC_UART0, data, length, BLOCKING);
}

void cat_interface_uart_computer_tx(uint8_t data) {
  UART_SendByte(LPC_UART0,data);
}

void cat_interface_1ms_tick(void) {
  if (cat_interface.retrieve_mode == SETTINGS_CAT_RETRIEVE_POLLING) {
    if (counter_cat_interface_poll_tick > 1000) {
      PRINTF("POLL RADIO\n");
      cat_interface.flags |= (1<<CAT_INTERFACE_FLAG_POLL_RADIO);

      counter_cat_interface_poll_tick = 0;
    }

    counter_cat_interface_poll_tick++;
  }

  counter_cat_interface_tick++;
}
