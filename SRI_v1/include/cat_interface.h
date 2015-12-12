#ifndef __CAT_INTERFACE_H
#define __CAT_INTERFACE_H

#define CAT_INTERFACE_RX_BUFFER_LENGTH  128
#define CAT_INTERFACE_TX_BUFFER_LENGTH  20

//! Timeout limit for the RADIO TX IN PROGRESS (10x ms, so 50 = 500ms)
#define CAT_INTERFACE_RADIO_TX_IN_PROGRESS_TIMEOUT 50
//! Timeout limit for the RADIO TX IN PROGRESS (10x ms, so 50 = 500ms)
#define CAT_INTERFACE_COMPUTER_TX_IN_PROGRESS_TIMEOUT 50

//! Flag that we should poll the radio
#define CAT_INTERFACE_FLAG_POLL_RADIO                  0
//! Flag to indicate that the computer is currently sending
#define CAT_INTERFACE_FLAG_COMPUTER_TX_IN_PROGRESS     1
//! Flag that the radio is currently sending
#define CAT_INTERFACE_FLAG_RADIO_TX_IN_PROGRESS        2

typedef struct {
  uint8_t jumper_cts_rts;
  uint8_t radio_rx_buffer[CAT_INTERFACE_RX_BUFFER_LENGTH];
  //! The radio TX buffer
  uint8_t radio_tx_buffer[CAT_INTERFACE_TX_BUFFER_LENGTH];
  //! The computer RX buffer
  uint8_t computer_rx_buffer[CAT_INTERFACE_RX_BUFFER_LENGTH];
  //! The radio TX buffer
  uint8_t computer_tx_buffer[CAT_INTERFACE_TX_BUFFER_LENGTH];
  //! The CAT poll interval, in ms/10, so 30 -> 300ms
  uint8_t poll_interval;
  //! The CAT poll/monitor mode
  uint8_t retrieve_mode;
  //! Flag to poll the radio
  uint8_t flags;
  //! The radio model
  uint8_t radio_model;
} struct_cat_interface;

void cat_interface_init(uint32_t baudrate, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t jumper_cts_rts);
void cat_interface_init_computer_uart(uint32_t baudrate, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t jumper_cts_rts);
void cat_interface_init_radio_uart(uint32_t baudrate, uint8_t stopbits, uint8_t parity, uint8_t flow_control, uint8_t jumper_cts_rts);

uint8_t cat_interface_parse_buffer(uint8_t *buffer, uint8_t length);
void cat_interface_execute(void);

uint32_t cat_interface_uart_poll_radio_rx(uint8_t *buffer, uint16_t length);
void cat_interface_uart_radio_tx_buf(uint8_t length, uint8_t *data);
void cat_interface_uart_radio_tx(uint8_t data);

uint32_t cat_interface_uart_poll_computer_rx(uint8_t *buffer, uint16_t length);
void cat_interface_uart_computer_tx_buf(uint8_t length, uint8_t *data);
void cat_interface_uart_computer_tx(uint8_t data);

void cat_interface_1ms_tick(void);

#endif /* end __CAT_INTERFACE_H */

/****************************************************************************
**                            End Of File
*****************************************************************************/
