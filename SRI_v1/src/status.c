#include <stdio.h>
#include <string.h>

#include "status.h"
#include "comm_interface.h"
#include "commands.h"
#include "computer_interface.h"
#include "lcd.h"
#include "misc.h"

struct_status status;

// Sends status data to the computer
void status_update_to_computer(uint8_t *data, uint16_t offset, uint8_t length) {
  if (computer_interface_connection_status())
    comm_interface_add_tx_struct_message(SRI_CMD_SEND_STATUS, length, offset, data);
}

void status_set_vfoA_mode(uint8_t mode) {
  status.radio.vfoA_mode = mode;

  STATUS_UPDATE_TO_COMPUTER(status.radio.vfoA_mode);
}

void status_set_vfoB_mode(uint8_t mode) {
  status.radio.vfoB_mode = mode;

  STATUS_UPDATE_TO_COMPUTER(status.radio.vfoB_mode);
}

uint8_t status_get_vfoA_mode(void) {
  return(status.radio.vfoA_mode);
}

uint8_t status_get_vfoB_mode(void) {
  return(status.radio.vfoB_mode);
}

void status_update_from_computer(uint8_t *data, uint16_t offset, uint8_t length) {
  uint8_t *ptr = (uint8_t *)&status;

  for (uint8_t i=0;i<length;i++)
    *(ptr+offset+i) = data[i];
}

void status_execute_update(void) {
  STATUS_UPDATE_TO_COMPUTER(status);
}


void status_set_vfoA_freq(uint32_t freq) {
  status.radio.vfoA_freq = freq;

  STATUS_UPDATE_TO_COMPUTER(status.radio.vfoA_freq);
}

void status_set_vfoB_freq(uint32_t freq) {
  status.radio.vfoB_freq = freq;

  STATUS_UPDATE_TO_COMPUTER(status.radio.vfoA_freq);
}

void status_set_vfoAB_txrx_state(uint8_t state) {
  status.radio.vfoAB_tx_rx_state = state;

  STATUS_UPDATE_TO_COMPUTER(status.radio.vfoAB_tx_rx_state);
}

uint32_t status_get_vfoA_freq(void) {
  return(status.radio.vfoA_freq);
}

uint32_t status_get_vfoB_freq(void) {
  return(status.radio.vfoB_freq);
}

uint8_t status_get_vfoAB_txrx_state(void) {
  return(status.radio.vfoAB_tx_rx_state);
}

void status_set_ptt_input_state_clr(uint8_t bit_nr) {
  status.ptt.ptt_input_state &= ~(1<<bit_nr);

  STATUS_UPDATE_TO_COMPUTER(status.ptt.ptt_input_state);
}

void status_set_ptt_input_state_set(uint8_t bit_nr) {
  status.ptt.ptt_input_state |= (1<<bit_nr);

  STATUS_UPDATE_TO_COMPUTER(status.ptt.ptt_input_state);
}

void status_set_ptt_input_state(uint8_t state) {
  status.ptt.ptt_input_state = state;

  STATUS_UPDATE_TO_COMPUTER(status.ptt.ptt_input_state);
}

uint8_t status_get_ptt_input_state(uint8_t bit_nr) {
  return((status.ptt.ptt_input_state & (1<<bit_nr))>>bit_nr);
}

void status_set_winkey_pot_speed(uint8_t speed) {
  status.winkey.pot_speed = speed;

  uint8_t str[17];
  sprintf(str,"CW Speed: %i WPM",speed);

  lcd_goto_xy(0,0);
  lcd_put_string(LCD_LINE1, str);

  STATUS_UPDATE_TO_COMPUTER(status.winkey.pot_speed);
}

uint8_t status_get_winkey_pot_speed() {
  return(status.winkey.pot_speed);
}

void status_set_winkey_transmitted_character(uint8_t c) {
  if (computer_interface_connection_status()) {
    uint8_t data[2];
    data[0] = SRI_SUB_CMD_WINKEY_CHARS_SENT;
    data[1] = c;

    comm_interface_add_tx_message(SRI_CMD_WINKEY, 2, data);
  }
}
