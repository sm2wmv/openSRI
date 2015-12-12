#include <stdio.h>

#include "LPC17xx.h"
#include "lpc17xx_i2c.h"
#include "lpc_types.h"
#include "audio.h"
#include "ctrl.h"
#include "board.h"
#include "settings.h"
#include "setting_structs.h"

void audio_init(void) {
  //Set default AF input source as the configured for CW, later changed when CAT data etc received
  audio_radio_afin_source(settings_get_af_input_source_cw(SETTING_AUDIO_ROUTE_RX));
}

void audio_radio_afin_source(uint8_t source) {
/*  if (source_main == SETTING_AUDIO_AF_INPUT_SORUCE_LOW) {
    ctrl_radio_main_input_source_low();
  }
  else if (source_main == SETTING_AUDIO_AF_INPUT_SORUCE_HIGH) {
    ctrl_radio_main_input_source_high();
  }

  if (source_sub == SETTING_AUDIO_AF_INPUT_SORUCE_LOW) {
    ctrl_radio_sub_input_source_low();
  }
  else if (source_sub == SETTING_AUDIO_AF_INPUT_SORUCE_HIGH) {
    ctrl_radio_sub_input_source_high();
  }*/
}
