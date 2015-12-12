#ifndef __BOARD_H
#define __BOARD_H

/* BOARD hardware v1.0
 * -------------------
 *
 * PORT 0
 * ------
 * P0_00 -> Output - Winkey TXD
 * P0_01 -> Input  - Winkey RXD
 * P0_02 -> Output - FT4232 CAT RXD
 * P0_03 -> Input  - FT4232 CAT TXD
 * P0_04 -> Input  - AUX header JP10 pin 4
 * P0_05 -> Input  - AUX header JP10 pin 3
 * P0_06 -> Input  - AUX header JP10 pin 2
 * P0_07 -> Output - LCD RS
 * P0_08 -> Output - LCD RW
 * P0_09 -> Output - LCD Enable
 * P0_10 -> Output - FT4232 Winkey RXD
 * P0_11 -> Input  - FT4232 Winkey TXD
 * P0_15 -> Output - CAT TXD
 * P0_16 -> Input  - CAT RXD
 * P0_17 -> Output - CAT RTS
 * P0_18 -> Input  - CAT CTS
 * P0_19 -> Output - Radio PTT1
 * P0_20 -> Output - Radio PTT2
 * P0_21 -> Output - Radio FSK
 * P0_22 -> Output - Radio CW
 * P0_23 -> Input  - AUX header JP4 pin 5
 * P0_24 -> Input  - AUX header JP4 pin 7
 * P0_25 -> Input  - DB9 AUX 6
 * P0_26 -> Input  - AUX DVK 2
 * P0_27 -> Output - I2C SDA
 * P0_28 -> Output - I2C SCL
 * P0_29 -> I/O    - USB DP
 * P0_30 -> I/O    - USB DM
 *
 * PORT 1
 * ------
 * P1_00 -> Input  - FT4232 CAT RTS
 * P1_01 -> Output - FT4232 CAT CTS
 * P1_04 -> Input  - DB9 AUX 0
 * P1_08 -> Input  - DB9 AUX 1
 * P1_09 -> Input  - DB9 AUX 2
 * P1_10 -> Input  - DB9 AUX 3
 * P1_14 -> Input  - DB9 AUX 4
 * P1_15 -> Input  - DB9 AUX 5
 * P1_16 -> Input  - FT4232 WK RTS
 * P1_17 -> Input  - FT4232 WK DTR
 * P1_18 -> Input  - Front I/O expander interrupt
 * P1_19 -> Input  - Winkey PTT
 * P1_20 -> Input  - Front ENCODER PHA
 * P1_21 -> Input  - AUX DVK 1
 * P1_22 -> Input  - Front ENCODER button
 * P1_23 -> Input  - Front ENCODER PHB
 * P1_24 -> Input  - FT4232 Spare DTR
 * P1_25 -> Input  - FT4232 Spare RTS
 * P1_26 -> Output - Front Backlight PWM
 * P1_27 ->
 * P1_28 -> Input  - AUX header JP5 pin 2
 * P1_29 -> Input  - AUX header JP5 pin 3
 * P1_30 -> Input  - USB power sense
 * P1_31 -> Input  - Winkey KEY
 *
 * PORT 2
 * ------
 * P2_00 -> Output - Front LCD DB0
 * P2_01 -> Output - Front LCD DB1
 * P2_02 -> Output - Front LCD DB2
 * P2_03 -> Output - Front LCD DB3
 * P2_04 -> Output - Front LCD DB4
 * P2_05 -> Output - Front LCD DB5
 * P2_06 -> Output - Front LCD DB6
 * P2_07 -> Output - Front LCD DB7
 * P2_08 ->
 * P2_09 -> USB Connect
 * P2_10 ->
 * P2_11 -> Input  - FT4232 FSKCW CW
 * P2_12 -> Input  - FT4232 FSKCW FSK
 * P2_13 -> Input  - FT4232 FSKCW PTT
 *
 * PORT 3
 * ------
 * P3_25 -> Output - PTT AMP
 * P3_26 -> Input  - Footswitch
 *
 * PORT 4
 * ------
 * P4_28 -> Output - Board LED Green
 * P4_29 -> Output - Board LED Red
 */

/* I2C addresses */
#define IO_EXP1_ADDR    0x40
#define IO_EXP2_ADDR    0x42
#define IO_EXP3_ADDR    0x44
#define IO_EXP4_ADDR    0x46

#define LDS8160_ADDR    0x22

/* PORT 0 */
#define RADIO_PTT_1_PIN           (1<<19)
#define RADIO_PTT_2_PIN           (1<<20)
#define RADIO_FSK_PIN             (1<<21)
#define RADIO_CW_PIN              (1<<22)
#define DB9_AUX6_PIN              (1<<25)
#define LCD_RS_PIN                (1<<7)
#define LCD_RW_PIN                (1<<8)
#define LCD_E_PIN                 (1<<9)

/* PORT 1 */
#define DB9_AUX0_PIN              (1<<4)  //ANT PIN
#define DB9_AUX1_PIN              (1<<8)
#define DB9_AUX2_PIN              (1<<9)
#define DB9_AUX3_PIN              (1<<10)
#define DB9_AUX4_PIN              (1<<14)
#define DB9_AUX5_PIN              (1<<15)
#define WINKEY_PTT_PIN            (1<<19)
#define WINKEY_KEY_PIN            (1<<31)

/* PORT 2 */
#define LCD_DB0_PIN               (1<<0)
#define LCD_DB1_PIN               (1<<1)
#define LCD_DB2_PIN               (1<<2)
#define LCD_DB3_PIN               (1<<3)
#define LCD_DB4_PIN               (1<<4)
#define LCD_DB5_PIN               (1<<5)
#define LCD_DB6_PIN               (1<<6)
#define LCD_DB7_PIN               (1<<7)

/* PORT 3 */
#define PTT_AMP_PIN               (1<<25)
#define FOOTSW_PIN                (1<<26)


/* PORT 4 */
#define BOARD_LED_GREEN       (1<<28)
#define BOARD_LED_RED         (1<<29)

#endif /* end __BOARD_H */

/****************************************************************************
**                            End Of File
*****************************************************************************/
