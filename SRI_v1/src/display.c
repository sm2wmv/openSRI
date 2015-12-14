#include <stdio.h>
#include "lpc17xx.h"
#include "display.h"
#include "main.h"
#include "lcd.h"

void display_welcome_screen(void) {
  delay_ms(500);

  lcd_put_string(LCD_LINE1,(uint8_t *)"  Smart  Radio  \0");
  lcd_put_string(LCD_LINE2,(uint8_t *)" Interface v1.0 \0");

  delay_ms(1500);
  winkey_reset();

  lcd_clear();
  lcd_put_string(LCD_LINE1,(uint8_t *)"   Created by   \0");
  lcd_put_string(LCD_LINE2,(uint8_t *)" SM2WMV  (SJ2W) \0");

  delay_ms(1500);

  lcd_clear();
}

void display_update(void) {

}

void display_update_status(void) {

}
