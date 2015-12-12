#include <cr_section_macros.h>
#include <stdio.h>

#include <string.h>
#include <stdarg.h>

#include "LPC17xx.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_uart.h"
#include "main.h"
#include "lpc_types.h"
#include "init.h"
#include "board.h"
#include "timer.h"
#include "ctrl.h"
#include "cat_interface.h"
#include "lcd.h"
#include "qei.h"
#include "settings.h"
#include "cw_ctrl.h"
#include "comm_interface.h"
#include "computer_interface.h"
#include "commands.h"
#include "version.h"
#include "misc.h"
#include "event_queue.h"
#include "eeprom_m24.h"
#include "event_handler.h"
#include "audio.h"
#include "sc16is7x0.h"
#include "winkey.h"

volatile uint32_t timer0_counter = 0;
volatile uint32_t timer1_counter = 0;
volatile uint32_t ms_delay_counter = 0;
volatile uint32_t us10_delay_counter = 0;

static uint16_t counter_event_timer = 0;

//static uint8_t lcd_data_line1[16];
//static uint8_t lcd_data_line2[16];

volatile struct_flags flags;

volatile uint8_t flag_read_buttons = 0;

void delay_ms(uint32_t time) {
  ms_delay_counter = 0;

  while(ms_delay_counter < time);
}

void delay_10us(uint32_t time) {
  us10_delay_counter = 0;

  while (us10_delay_counter < time);
}

void main_eeprom_write_in_progress(void) {
  eeprom_m24_write_block(0,0,NULL);
}

void main_eeprom_write_done(void) {
  PRINTF("EEPROM: WRITE DONE\n");

  //Send the message back to the software telling the user that
  //the EEPROM write has been done
  if (event_queue_check_id(EEPROM_EVENT_TYPE_WRITE) == 0)
    comm_interface_add_tx_message(SRI_CMD_EEPROM_SAVE,0,0);
}

/*! Add a message to the event queue which will be run at the correct time
 *  \param func A function pointer to the function we want to run
 *  \param offset the time in ms when we want our function to be run
 *  \param id Which type of event this is
 *  \param priority The priority type */
void event_add_message(void (*func), uint16_t offset, uint8_t id, uint8_t priority) {
  EVENT_MESSAGE event;

  if (event_in_queue() == 0)
    counter_event_timer = 0;

  event.func = func;
  event.time_target = counter_event_timer + offset;
  event.id = id;
  event.priority = priority;

  event_queue_add(event);

  //PRINTF("ADDED TO QUEUE\n");
}

/*! \brief Run the first function in the event queue */
void event_run(void) {
  if (event_in_queue()) {
    EVENT_MESSAGE event = event_queue_get();

    //PRINTF("EVENT RUN\n");

    //Drop the message from the event QUEUE
    event_queue_drop();

    //Run the function in the event queue
    event.func();
  }
}

void main_load_settings(void) {
  //Load the settings from the EEPROM
  settings_load_from_eeprom();

  #ifndef CAT_PORT_DEBUG
    cat_interface_init(settings_get_cat_baudrate(), settings_get_cat_stopbits(), settings_get_cat_parity(), settings_get_cat_flow_control(), settings_get_cat_jumper_cts_rts());
  #endif
}

/*******************************************************************************
**   Main Function  main()
*******************************************************************************/
int main (void) {
  SystemCoreClockUpdate();

  //Initialize all I/Os
  init_io();

  //Init the I2C bus running 400kHz
  I2C_Init(LPC_I2C0,400000);
  I2C_Cmd(LPC_I2C0, ENABLE);

  init_uart3();

  #ifdef WK_PORT_DEBUG
    init_uart2(115200);
  #else
    init_uart2(1200); //Init to 1200 baud on the WinKey port
  #endif

  #ifdef CAT_PORT_DEBUG
    cat_interface_init_computer_uart(115200,0,0,0,0);
  #endif

  //Initialize and enable timer 0 to run with 1ms intervals
  init_timer(0 , 0);
  init_timer(1 , 0);

  comm_interface_init(computer_interface_uart_rx, computer_interface_uart_tx, computer_interface_uart_poll_rx);

  ctrl_led_pwr_on();

  /* Initialize stuff to their default states */
  ctrl_mic_relay_clr();
  ctrl_ptt_amp_clr();
  ctrl_pcm2912_mic_preamp_off();
  ctrl_pcm2912_mic_mute_on();

  ctrl_i2c_io_exp1_set();
  ctrl_i2c_io_exp2_set();
  ctrl_i2c_io_exp3_set();
  ctrl_i2c_io_exp4_set();

  enable_timer(0);
  enable_timer(1);

  delay_ms(100);

  init_qei();
  lcd_init();
  event_queue_init();

  main_load_settings();

  ctrl_backlight_init(settings_get_backlight_rgb_red(), settings_get_backlight_rgb_green(), settings_get_backlight_rgb_blue());

  sc16is7x0_init();

  //status.curr_button_state = ctrl_buttons_get_status();
  flags.various = 0;

  status_set_vfoA_mode(STATUS_RADIO_MODE_CW);
  status_set_vfoB_mode(STATUS_RADIO_MODE_CW);

  delay_ms(500);

  lcd_put_string(LCD_LINE1,(uint8_t *)"  Smart  Radio  \0");
  lcd_put_string(LCD_LINE2,(uint8_t *)" Interface v1.0 \0");

  delay_ms(1500);
  winkey_reset();

  lcd_clear();
  lcd_put_string(LCD_LINE1,(uint8_t *)"   Created by   \0");
  lcd_put_string(LCD_LINE2,(uint8_t *)" SM2WMV  (SJ2W) \0");

  winkey_init();

  delay_ms(1500);

  lcd_clear();

  uint8_t str[17];

  sprintf(str, "CW Speed: %i WPM\0",status_get_winkey_pot_speed());

  lcd_put_string(LCD_LINE1,str);
  lcd_put_string(LCD_LINE2,(uint8_t *)"Mode: CW\0");

  PRINTF("SRI interface started\n\r");

  int16_t qei_temp;

  while ( 1 ) {
    qei_temp = qei_get_counter_change();

    if (qei_temp != 0) {
      if (qei_temp > 0)
        winkey_inc_speed();
      else
        winkey_dec_speed();
    }

    comm_interface_parse_rx_buffer();
    comm_interface_poll_rx_queue();
    comm_interface_poll_tx_queue();

    event_handler_execute();

    #ifndef CAT_PORT_DEBUG
      cat_interface_execute();
    #endif

    computer_interface_execute();
    winkey_execute();

    //Read the button states
    if (flag_read_buttons != 0) {
      //status.curr_button_state = ctrl_buttons_get_status();
      flag_read_buttons = 0;
    }

    if (flags.various & (1<<FLAG_RUN_EVENT_QUEUE)) {
      event_run();
      flags.various &= ~(1<<FLAG_RUN_EVENT_QUEUE);
    }
  }
}

/*! \brief Gets called with 1 ms intervals */
void main_timer0_tick(void) {
  comm_interface_1ms_tick();

  if (event_in_queue()) {
    if (counter_event_timer >= (event_queue_get()).time_target) {
      if (event_queue_get().priority == EVENT_PRIORITY_LEVEL_MAINLOOP)
        flags.various |= (1<<FLAG_RUN_EVENT_QUEUE);
      else if (event_queue_get().priority == EVENT_PRIORITY_LEVEL_REALTIME) {
        event_run();
      }
    }
  }

  //If the value equals the half of it's range then
  //we remove that amount from all target times in the event
  //queue and set the counter to 0 again
  if (counter_event_timer >= 32767) {
    event_queue_wrap(32767);

    counter_event_timer = 0;
  }

  //Blink the green LED on the board for debug purposes
  if ((timer0_counter % 500) == 0) {
    if (LPC_GPIO4->FIOPIN & BOARD_LED_GREEN) {
      LPC_GPIO4->FIOCLR = BOARD_LED_GREEN;
    }
    else {
      LPC_GPIO4->FIOSET = BOARD_LED_GREEN;
    }
  }

  if ((timer0_counter % 1000) == 0) {
    flag_read_buttons = 1;
  }

  //sc16is7x0_1ms_tick();
  computer_interface_1ms_tick();
  cat_interface_1ms_tick();
  winkey_1ms_tick();
  event_handler_1ms_tick();

  counter_event_timer++;
  ms_delay_counter++;
  timer0_counter++;
}

/*! \brief Gets called with 10 us intervals */
void main_timer1_tick(void) {
  event_handler_10us_tick();

  timer1_counter++;
  us10_delay_counter++;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
