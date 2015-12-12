#include <stdio.h>

#include "LPC17xx.h"
#include "lpc17xx_i2c.h"
#include "lpc_types.h"
#include "ctrl.h"
#include "board.h"


//#define CTRL_DEBUG

//Bit 2,3,4 are inputs
unsigned char io_exp1_out_status = 0xFF;

//Bit 6 is an input, we also set HUB reset and FT4232 reset as high
unsigned char io_exp2_out_status = (1<<6) | (1<<4) | (1<<5);

//Bit 6, 7 are inputs
unsigned char io_exp3_out_status = (1<<6) | (1<<7);

//Bit 5,6,7 are inputs
unsigned char io_exp4_out_status = 0xFF;//(1<<5) | (1<<6) | (1<<7);

uint8_t ctrl_i2c_io_exp1_get(void) {
	unsigned char ret;

	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP1_ADDR >> 1;
	transferMCfg.tx_data = NULL;
	transferMCfg.tx_length = 0;
	transferMCfg.rx_data = &ret;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

	return(ret);
}

uint8_t ctrl_i2c_io_exp3_get(void) {
	unsigned char ret;

	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP3_ADDR >> 1;
	transferMCfg.tx_data = NULL;
	transferMCfg.tx_length = 0;
	transferMCfg.rx_data = &ret;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

	return(ret);
}

uint8_t ctrl_i2c_io_exp4_get(void) {
	unsigned char ret;

	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP4_ADDR >> 1;
	transferMCfg.tx_data = NULL;
	transferMCfg.tx_length = 0;
	transferMCfg.rx_data = &ret;
	transferMCfg.rx_length = 1;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

	return(ret);
}

void ctrl_i2c_io_exp1_set(void) {
	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP1_ADDR >> 1;
	transferMCfg.tx_data = &io_exp1_out_status;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);
}

void ctrl_i2c_io_exp2_set(void) {
	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP2_ADDR >> 1;
	transferMCfg.tx_data = &io_exp2_out_status;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);
}

void ctrl_i2c_io_exp3_set(void) {
	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP3_ADDR >> 1;
	transferMCfg.tx_data = &io_exp3_out_status;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);
}

void ctrl_i2c_io_exp4_set(void) {
	I2C_M_SETUP_Type transferMCfg;
	transferMCfg.sl_addr7bit = IO_EXP4_ADDR >> 1;
	transferMCfg.tx_data = &io_exp4_out_status;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;

	I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);
}

void ctrl_ptt_amp_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: PTT AMP SET\n");
  #endif
  LPC_GPIO3->FIOSET = PTT_AMP_PIN;
}

void ctrl_ptt_amp_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: PTT AMP CLR\n");
  #endif

  LPC_GPIO3->FIOCLR = PTT_AMP_PIN;
}

void ctrl_radio_ptt_1_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO PTT 1 SET\n");
  #endif

  LPC_GPIO0->FIOSET = RADIO_PTT_1_PIN;
}

void ctrl_radio_ptt_1_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO PTT 1 CLR\n");
  #endif

  LPC_GPIO0->FIOCLR = RADIO_PTT_1_PIN;
}

void ctrl_radio_ptt_2_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO PTT 2 SET\n");
  #endif

  LPC_GPIO0->FIOSET = RADIO_PTT_2_PIN;
}

void ctrl_radio_ptt_2_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO PTT 2 CLR\n");
  #endif

  LPC_GPIO0->FIOCLR = RADIO_PTT_2_PIN;
}

void ctrl_radio_fsk_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO FSK SET\n");
  #endif

  LPC_GPIO0->FIOSET = RADIO_FSK_PIN;
}

void ctrl_radio_fsk_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO FSK CLR\n");
  #endif

  LPC_GPIO0->FIOCLR = RADIO_FSK_PIN;
}

void ctrl_radio_cw_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO CW SET\n");
  #endif

  LPC_GPIO0->FIOSET = RADIO_CW_PIN;
}

void ctrl_radio_cw_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO CW CLR\n");
  #endif

  LPC_GPIO0->FIOCLR = RADIO_CW_PIN;
}

void ctrl_radio_inhibit_set(void) {
  //TODO: Not supported yet in HW
}

void ctrl_radio_inhibit_clr(void) {
  //TODO: Not supported yet in HW
}

void ctrl_ant_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: ANT SET\n");
  #endif

  LPC_GPIO1->FIOSET = DB9_AUX0_PIN;
}

void ctrl_ant_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: ANT CLR\n");
  #endif

  LPC_GPIO1->FIOCLR = DB9_AUX0_PIN;
}

void ctrl_mic_relay_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: MIC RELAY SET\n");
  #endif

  io_exp3_out_status |= (1<<0);

  ctrl_i2c_io_exp3_set();
}

void ctrl_mic_relay_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: MIC RELAY CLR\n");
  #endif

  io_exp3_out_status &= ~(1<<0);

  ctrl_i2c_io_exp3_set();
}

/*! \brief Selects the low level audio input as input source for the main VFO */
void ctrl_radio_main_input_source_low(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO INPUT SOURCE LOW\n");
  #endif

  io_exp2_out_status |= (1<<0);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Selects the AF (high) level audio input as input source for the main VFO */
void ctrl_radio_main_input_source_high(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO INPUT SOURCE HIGH\n");
  #endif

  io_exp2_out_status &= ~(1<<0);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Selects the low level audio input as input source for the SUB VFO */
void ctrl_radio_sub_input_source_low(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO SUB INPUT SOURCE LOW\n");
  #endif

  io_exp2_out_status |= (1<<1);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Selects the AF (high) level audio input as input source for the SUB VFO */
void ctrl_radio_sub_input_source_high(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO SUB INPUT SOURCE LOW\n");
  #endif

  io_exp2_out_status &= ~(1<<1);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the radio AUX 1 output as high */
void ctrl_radio_aux1_out_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO AUX 1 OUT SET\n");
  #endif

  io_exp2_out_status |= (1<<2);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the radio AUX 1 output as low */
void ctrl_radio_aux1_out_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO AUX 1 OUT CLR\n");
  #endif

  io_exp2_out_status &= ~(1<<2);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the radio AUX 2 output as high */
void ctrl_radio_aux2_out_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO AUX 2 OUT SET\n");
  #endif

  io_exp2_out_status |= (1<<3);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the radio AUX 2 output as low */
void ctrl_radio_aux2_out_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: RADIO AUX 2 OUT CLR\n");
  #endif

  io_exp2_out_status &= ~(1<<3);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the FT4232 reset pin high */
void ctrl_ft4232_reset_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: FT4232 RESET SET\n");
  #endif

  io_exp2_out_status |= (1<<4);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the FT4232 reset pin low */
void ctrl_ft4232_reset_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: FT4232 RESET CLR\n");
  #endif

  io_exp2_out_status &= ~(1<<4);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the HUB reset pin high */
void ctrl_hub_reset_set(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: USB HUB RESET SET\n");
  #endif

  io_exp2_out_status |= (1<<5);

  ctrl_i2c_io_exp2_set();
}

/*! \brief Set the HUB reset pin low */
void ctrl_hub_reset_clr(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: USB HUB RESET CLR\n");
  #endif

  io_exp2_out_status &= ~(1<<5);

  ctrl_i2c_io_exp2_set();
}

void ctrl_pcm2912_mic_preamp_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: PCM2912 MIC PREAMP ON\n");
  #endif

  io_exp3_out_status |= (1<<4);

  ctrl_i2c_io_exp3_set();
}

void ctrl_pcm2912_mic_preamp_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: PCM2912 MIC PREAMP OFF\n");
  #endif

  io_exp3_out_status &= ~(1<<4);

  ctrl_i2c_io_exp3_set();
}

void ctrl_pcm2912_mic_mute_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: PCM2912 MIC MUTE ON\n");
  #endif

  io_exp3_out_status |= (1<<5);

  ctrl_i2c_io_exp3_set();
}

void ctrl_pcm2912_mic_mute_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: PCM2912 MIC MUTE OFF\n");
  #endif

  io_exp3_out_status &= ~(1<<5);

  ctrl_i2c_io_exp3_set();
}

void ctrl_led_fsk_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED FSK ON\n");
  #endif

  io_exp1_out_status &= ~(1<<6);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_fsk_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED FSK OFF\n");
  #endif

  io_exp1_out_status |= (1<<6);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_cw_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED CW ON\n");
  #endif

  io_exp1_out_status &= ~(1<<5);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_cw_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED CW OFF\n");
  #endif

  io_exp1_out_status |= (1<<5);
  ctrl_i2c_io_exp1_set();
}


void ctrl_led_pwr_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED PWR ON\n");
  #endif

  io_exp1_out_status &= ~(1<<1);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_pwr_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED PWR OFF\n");
  #endif

  io_exp1_out_status |= (1<<1);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_ptt_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED PTT ON\n");
  #endif

  io_exp1_out_status &= ~(1<<0);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_ptt_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED PTT OFF\n");
  #endif

  io_exp1_out_status |= (1<<0);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_inhibit_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED INHIBIT ON\n");
  #endif

  io_exp1_out_status &= ~(1<<7);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_inhibit_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED INHIBIT OFF\n");
  #endif

  io_exp1_out_status |= (1<<7);
  ctrl_i2c_io_exp1_set();
}

void ctrl_led_button1_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED BUTTON1 ON\n");
  #endif

  io_exp4_out_status &= ~(1<<0);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_button1_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED BUTTON1 OFF\n");
  #endif

  io_exp4_out_status |= (1<<0);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_button2_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED BUTTON2 ON\n");
  #endif

  io_exp4_out_status &= ~(1<<1);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_button2_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED BUTTON2 OFF\n");
  #endif

  io_exp4_out_status |= (1<<1);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_button3_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED BUTTON3 ON\n");
  #endif

  io_exp4_out_status &= ~(1<<2);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_button3_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED BUTTON3 OFF\n");
  #endif

  io_exp4_out_status |= (1<<2);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_aux_on(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED AUX ON\n");
  #endif

  io_exp4_out_status &= ~(1<<3);
  ctrl_i2c_io_exp4_set();
}

void ctrl_led_aux_off(void) {
  #ifdef CTRL_DEBUG
    PRINTF("CTRL: LED AUX OFF\n");
  #endif

  io_exp4_out_status |= (1<<3);
  ctrl_i2c_io_exp4_set();
}

uint8_t ctrl_buttons_get_status(void) {
  uint8_t val = ctrl_i2c_io_exp1_get() & 0x1C;
  uint32_t encoder_button = ((LPC_GPIO1->FIOPIN & (1<<22))>>22);

  //Shift down the result from the IO expander, add the state of the encoder button
  //and we want all other bits to be high since we will invert the result when returning it
  val = (val>>1) | (uint8_t)encoder_button | 0xF0;

  //Invert the result and return it
  return(~val);
}

uint8_t ctrl_conf_get_state(void);

void ctrl_backlight_init(uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t data[2];

  I2C_M_SETUP_Type transferMCfg;
  transferMCfg.sl_addr7bit = LDS8160_ADDR >> 1;
  transferMCfg.tx_data = data;
  transferMCfg.tx_length = 2;
  transferMCfg.rx_data = NULL;
  transferMCfg.rx_length = 0;
  transferMCfg.retransmissions_max = 3;

  data[0] = 0x1E;
  data[1] = 0x8A;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x00;
  data[1] = 0xA0;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x01;
  data[1] = 0xA0;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x02;
  data[1] = 0xA0;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x03;
  data[1] = 0x3F;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x04;
  data[1] = 0x00;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x05;
  data[1] = red;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x06;
  data[1] = green;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x07;
  data[1] = blue;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x49;
  data[1] = 0x00;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x4A;
  data[1] = 0x1C;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x4B;
  data[1] = 0x1F;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xA0;
  data[1] = 0x36;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xA2;
  data[1] = 0x48;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xA2;
  data[1] = 0x48;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xA4;
  data[1] = 0x48;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xC0;
  data[1] = 0x40;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xD4;
  data[1] = 0x04;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xD6;
  data[1] = 0x04;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xD8;
  data[1] = 0x04;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0xDA;
  data[1] = 0x04;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x1F;
  data[1] = 0x10;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  ctrl_backlight_set_rgb(red,green,blue);
}

void ctrl_backlight_set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t data[2];

  I2C_M_SETUP_Type transferMCfg;
  transferMCfg.sl_addr7bit = LDS8160_ADDR >> 1;
  transferMCfg.tx_data = data;
  transferMCfg.tx_length = 2;
  transferMCfg.rx_data = NULL;
  transferMCfg.rx_length = 0;
  transferMCfg.retransmissions_max = 3;

  data[0] = 0x05;
  data[1] = red;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x06;
  data[1] = green;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);

  data[0] = 0x07;
  data[1] = blue;
  I2C_MasterTransferData(LPC_I2C0, &transferMCfg, I2C_TRANSFER_POLLING);
}
