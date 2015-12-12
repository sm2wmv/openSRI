#ifndef __SETTING_STRUCTS_H
#define __SETTING_STRUCTS_H

#ifdef __LPC17XX__
#include <stdio.h>
#include "lpc17xx.h"
#endif

#ifndef __LPC17XX__
  #define uint8_t  quint8
  #define uint16_t quint16
  #define uint32_t qint32
  #define uint64_t qint64
#endif

/*********** START RADIO SETTINGS ***********/

//! No parity
#define SETTING_CAT_PARITY_NONE   0
//! Even parity
#define SETTING_CAT_PARITY_EVEN   1
//! Odd parity
#define SETTING_CAT_PARITY_ODD    2

//! 1 stop bit
#define SETTING_CAT_STOPBITS_ONE  0
//! Two stop bits
#define SETTING_CAT_STOPBITS_TWO  1

//! No flow control
#define SETTING_CAT_FLOW_CONTROL_NONE 0

//! Jumper RTS and CTS on the CAT
#define SETTING_CAT_JUMPER_RTS_CTS    1

//! How do we handle to retrieve CAT data, by polling
#define SETTINGS_CAT_RETRIEVE_POLLING 0
//! How do we handle to retrieve CAT data, by monitoring
#define SETTINGS_CAT_RETRIEVE_MONITOR 1

/************** RADIO DEFINES ***************/
#define RADIO_MODEL_ELECRAFT_K3           0
#define RADIO_MODEL_ICOM                  1
#define RADIO_MODEL_KENWOOD               2
#define RADIO_MODEL_YAESU_FT1000MKV       3
#define RADIO_MODEL_YAESU_FT950           4

typedef struct __attribute__ ((aligned(1))) {
  //! The radio model type, see defines
  uint8_t   radio_model;
  //! CAT interface enabled
  uint8_t   cat_interface_enabled;
  //! CAT interface baudrate
  uint32_t  cat_baudrate;
  //! CAT interface number of stop bits
  uint8_t   cat_stopbits;
  //! CAT interface parity
  uint8_t   cat_parity;
  //! CAT interface C-IV address (if ICOM)
  uint8_t   cat_icom_civ;
  //! CAT interface flow control enabled
  uint8_t   cat_flow_control;
  //! CAT interface, jumper CAT port RTS and CTS
  uint8_t   cat_jumper_rts_cts;
  //! CAT interface retrieve status, polling or monitoring
  uint8_t   cat_retrieve_type;
  //! CAT interface polling rate (in 10*ms, so 100 means 1000 ms)
  uint8_t   cat_poll_rate;
} struct_radio_settings;

/*********** END RADIO SETTINGS ***********/


/*********** START PTT SETTINGS ***********/

//! Bit to enable PTT input via the Footswitch
#define SETTING_PTT_INPUT_FOOTSWITCH    0
//! Bit to enable PTT input via the Winkey ports RTS
#define SETTING_PTT_INPUT_WK_RTS        1
//! Bit to enable PTT input via the Winkey ports DTR
#define SETTING_PTT_INPUT_WK_DTR        2
//! Bit to enable PTT input via the FSK/CW port RTS
#define SETTING_PTT_INPUT_FSKCW_RTS     3
//! Bit to enable PTT input via VOX sense input
#define SETTING_PTT_INPUT_VOX_SENSE     4
//! Bit to enable PTT input via VOX sense input
#define SETTING_PTT_INPUT_WK            5

//! Enable PTT output on PTT1
#define SETTING_PTT_OUTPUT_PTT1         0
//! Enable PTT output on PTT2
#define SETTING_PTT_OUTPUT_PTT2         1
//! Enable PTT output on PTT1 and 2
#define SETTING_PTT_OUTPUT_PTT1_2       2
//! Enable PTT output, DISABLED
#define SETTING_PTT_OUTPUT_DISABLED     3


typedef struct __attribute__ ((aligned(1))) {
  //! PTT input enable information, see defines
  uint8_t ptt_input_enabled;
  //! The polarity of the PTT input, 1 = inverted, 0 = non-inverted
  uint8_t ptt_input_invert;
  //! Delay time between PTT input activated and radio PTT output
  uint8_t radio_pre_delay;  //in 10th of ms, so 10 means 100ms
  //! Delay time between PTT input released and radio PTT output
  uint8_t radio_post_delay;
  //! Delay time between PTT input activated and amplifier PTT output
  uint8_t amp_pre_delay;
  //! Delay time between PTT input released and radio PTT output
  uint8_t amp_post_delay;
  //! Delay time between PTT input activated and inhibit output change
  uint8_t inhibit_pre_delay;
  //! Delay time between PTT input released and inhibit output change
  uint8_t inhibit_post_delay;
  //! Delay time between PTT input activated and antenna lock output
  uint8_t antenna_pre_delay;
  //! Delay time between PTT input released and antenna lock output
  uint8_t antenna_post_delay;
  //! The PTT input(s) enabled in digital modes
  uint8_t radio_digital_ptt;
  //! The PTT input(s) enabled in CW modes
  uint8_t radio_cw_ptt;
  //! The PTT input(s) enabled in Phone modes
  uint8_t radio_phone_ptt;
  //! Amplifier PTT output status
  uint8_t amplifier_enabled;
  //! Inhibit output status
  uint8_t inhibit_enabled;
  //! Inhibit output is inverted
  uint8_t inhibit_inverted;
} struct_ptt_settings;

/*********** END PTT SETTINGS ***********/

/*********** START AUDIO SETTINGS ***********/

#define SETTING_AUDIO_AF_INPUT_SORUCE_LOW   0
#define SETTING_AUDIO_AF_INPUT_SORUCE_HIGH  1


#define SETTING_AUDIO_ROUTE_OFFSET_COUNT  5

//! Offset for audio routing when in RX
#define SETTING_AUDIO_ROUTE_RX          0
//! Offset for audio routing when footswitch activated PTT
#define SETTING_AUDIO_ROUTE_FOOTSWITCH  1
//! Offset for audio routing when computer activated PTT
#define SETTING_AUDIO_ROUTE_COMPUTER    2
//! Offset for audio routing when Winkey activated PTT
#define SETTING_AUDIO_ROUTE_WINKEY      3
//! Offset for audio routing when VOX activated PTT
#define SETTING_AUDIO_ROUTE_VOX         4

//! Mic route option, direct from mic to radio
#define SETTING_AUDIO_MIC_ROUTE_DIRECT  0
//! Mic route option, throught the sound card
#define SETTING_AUDIO_MIC_ROUTE_SC      1

typedef struct __attribute__ ((aligned(1))) {
  //! AF in routing in CW mode
  uint8_t af_input_source_cw[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! AF in routing in Phone mode
  uint8_t af_input_source_phone[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! AF in routing in Digital mode
  uint8_t af_input_source_digital[SETTING_AUDIO_ROUTE_OFFSET_COUNT];

  //! Mic routing in phone mode, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t mic_path[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! Computer generated path, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t computer_generated_path_phone[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! Computer generated path, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t computer_generated_path_digital[SETTING_AUDIO_ROUTE_OFFSET_COUNT];

  //! Mic mute option, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t mic_mute[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! Mic preamp option, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t mic_preamp[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! Line out mute option, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t line_out_mute_phone[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
  //! Line out mute option, see SETTING_AUDIO_ROUTE_XXX for offset information
  uint8_t line_out_mute_digital[SETTING_AUDIO_ROUTE_OFFSET_COUNT];
} struct_audio_settings;

/*********** END AUDIO SETTINGS ***********/

/*********** START CW SETTINGS ***********/

//! Bit is set if CW input source Winkey is enabled
#define SETTING_CW_INPUT_SOURCE_WINKEY      0
//! Bit is set if CW input source Winkey DTR is enabled
#define SETTING_CW_INPUT_SOURCE_WINKEY_DTR  1
//! Bit is set if CW input source Winkey RTS is enabled
#define SETTING_CW_INPUT_SOURCE_WINKEY_RTS  2
//! Bit is set if CW input source USB DTR is enabled
#define SETTING_CW_INPUT_SOURCE_USB_DTR     3

typedef struct __attribute__ ((aligned(1))) {
  uint8_t input_source;
} struct_cw_settings;

/*********** END CW SETTINGS ***********/

/*********** START MISC SETTINGS ***********/
typedef struct __attribute__ ((aligned(1))) {
  //! The color for the display backlight, RGB Red
  uint8_t display_rgb_red;
  //! The color for the display backlight, RGB Green
  uint8_t display_rgb_green;
  //! The color for the display backlight, RGB Blue
  uint8_t display_rgb_blue;
} struct_misc_settings;

/*********** END MISC SETTINGS ***********/

/*********** START Winkey SETTINGS ***********/

#define WINKEY_MAXMSG 0

typedef struct __attribute__ ((aligned(1))) {
  uint8_t magic;
  uint8_t modereg;
  uint8_t oprrate;
  uint8_t stconst;
  uint8_t weight;
  uint8_t lead_time;
  uint8_t tail_time;
  uint8_t minwpm;
  uint8_t wpmrange;
  uint8_t xtnd;
  uint8_t kcomp;
  uint8_t farnswpm;
  uint8_t sampadj;
  uint8_t ratio;
  uint8_t pincfg;
  uint8_t def_speed;  //Own addition, not standard winkey
} struct_winkey_settings;

/*********** END Winkey SETTINGS ***********/

typedef struct __attribute__ ((aligned(1))) {
  struct_radio_settings   radio;
  struct_ptt_settings     ptt;
  struct_audio_settings   audio;
  struct_cw_settings      cw;
  struct_misc_settings    misc;
  struct_winkey_settings  winkey;
} struct_settings;

/*********** START CW Messages ***********/
//The max length of a message is 50 chars plus the null termination
#define CW_MESSAGE_MAX_LENGTH 50+1

typedef struct __attribute__ ((aligned(1))) {
  uint8_t str[8][CW_MESSAGE_MAX_LENGTH];
} struct_cw_messages;

/*********** END CW Messages ***********/

#endif /* end __SETTING_STRUCTS_H */

/****************************************************************************
** End Of File
*****************************************************************************/
