#include "event_handler.h"
#include "main.h"
#include "misc.h"
#include "settings.h"
#include "sequencer.h"
#include "ctrl.h"

static volatile uint16_t counter_event_10us = 0;
static volatile uint16_t counter_event_1ms = 0;

volatile struct_event_status event_status;

uint8_t event_handler_get_ptt_status(void) {
  return(event_status.curr_ptt_input);
}

void event_handler_ptt_radio_activate(void) {
  PRINTF("EVENT_HANDLER: RADIO PTT ACTIVE\n\r");

  if (status_get_vfoA_mode_type() == STATUS_RADIO_MODE_TYPE_CW) {
    if ((settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1) || (settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_1_set();
    }

    if ((settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_2) || (settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_2_set();
    }

    if (settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_DISABLED) {
      ctrl_radio_ptt_1_clr(); //Make sure the output is off
      ctrl_radio_ptt_2_clr(); //Make sure the output is off
    }
  }
  else if (status_get_vfoA_mode_type() == STATUS_RADIO_MODE_TYPE_PHONE) {
    if ((settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1) || (settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_1_set();
    }

    if ((settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_2) || (settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_2_set();
    }

    if (settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_DISABLED) {
      ctrl_radio_ptt_1_clr(); //Make sure the output is off
      ctrl_radio_ptt_2_clr(); //Make sure the output is off
    }
  }
  else if (status_get_vfoA_mode_type() == STATUS_RADIO_MODE_TYPE_DIGITAL) {
    if ((settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1) || (settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_1_set();
    }

    if ((settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_2) || (settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_2_set();
    }

    if (settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_DISABLED) {
      ctrl_radio_ptt_1_clr(); //Make sure the output is off
      ctrl_radio_ptt_2_clr(); //Make sure the output is off
    }
  }
}

void event_handler_ptt_radio_deactivate(void) {
  PRINTF("EVENT_HANDLER: RADIO PTT DEACTIVE\n\r");

  if (status_get_vfoA_mode_type() == STATUS_RADIO_MODE_TYPE_CW) {
    if ((settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1) || (settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_1_clr();
    }

    if ((settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_2) || (settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_2_clr();
    }

    if (settings_get_radio_cw_ptt() == SETTINGS_PTT_RADIO_OUTPUT_DISABLED) {
      ctrl_radio_ptt_1_clr(); //Make sure the output is off
      ctrl_radio_ptt_2_clr(); //Make sure the output is off
    }
  }
  else if (status_get_vfoA_mode_type() == STATUS_RADIO_MODE_TYPE_PHONE) {
    if ((settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1) || (settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_1_clr();
    }

    if ((settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_2) || (settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_2_clr();
    }

    if (settings_get_radio_phone_ptt() == SETTINGS_PTT_RADIO_OUTPUT_DISABLED) {
      ctrl_radio_ptt_1_clr(); //Make sure the output is off
      ctrl_radio_ptt_2_clr(); //Make sure the output is off
    }
  }
  else if (status_get_vfoA_mode_type() == STATUS_RADIO_MODE_TYPE_DIGITAL) {
    if ((settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1) || (settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_1_clr();
    }

    if ((settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_2) || (settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_1_2)) {
      ctrl_radio_ptt_2_clr();
    }

    if (settings_get_radio_digital_ptt() == SETTINGS_PTT_RADIO_OUTPUT_DISABLED) {
      ctrl_radio_ptt_1_clr(); //Make sure the output is off
      ctrl_radio_ptt_2_clr(); //Make sure the output is off
    }
  }
}

void event_handler_ptt_amp_activate(void) {
  PRINTF("EVENT_HANDLER: AMP PTT ACTIVE\n\r");
  if (settings_get_amplifier_enabled()) {
    ctrl_ptt_amp_set();
  }
}

void event_handler_ptt_amp_deactivate(void) {
  PRINTF("EVENT_HANDLER: AMP PTT DEACTIVE\n\r");

  ctrl_ptt_amp_clr();
}

void event_handler_ptt_inhibit_activate(void) {
  if (settings_get_inhibit_enabled()) {
    PRINTF("EVENT_HANDLER: INHIBIT PTT ACTIVE\n\r");
    if (settings_get_inhibit_inverted())
      ctrl_radio_inhibit_clr();
    else
      ctrl_radio_inhibit_set();
  }
  else
    ctrl_radio_inhibit_clr(); //CLR is the default state
}

void event_handler_ptt_inhibit_deactivate(void) {
  if (settings_get_inhibit_enabled()) {
    PRINTF("EVENT_HANDLER: INHIBIT PTT DEACTIVE\n\r");

    if (settings_get_inhibit_inverted())
      ctrl_radio_inhibit_set();
    else
      ctrl_radio_inhibit_clr();
  }
  else
    ctrl_radio_inhibit_clr(); //CLR is the default state
}

void event_handler_ptt_ant_activate(void) {
  PRINTF("EVENT_HANDLER: ANT PTT ACTIVE\n\r");
  ctrl_ant_set();
}

void event_handler_ptt_ant_deactivate(void) {
  PRINTF("EVENT_HANDLER: ANT PTT DEACTIVE\n\r");
  ctrl_ant_clr();
}

void event_handler_execute_ptt_change(uint8_t prev_state, uint8_t curr_state) {
  if ((prev_state == 0) && (curr_state != 0)) { //Activate the sequencer
    PRINTF("EVENT_HANDLER_PTT_CHANGE: ACTIVATE\n\r");
    sequencer_activate();
  }
  else if ((prev_state != 0) && (curr_state == 0)) { //Deactivate sequencer
    PRINTF("EVENT_HANDLER_PTT_CHANGE: DEACTIVATE\n\r");
    sequencer_deactivate();
  }
  else {
    //Do nothing
    PRINTF("EVENT_HANDLER_PTT_CHANGE: DO NOTHING\n\r");
  }
}

void event_handler_cw_execute(void) {
  if (settings_get_cw_input_source() & (1<<SETTING_CW_INPUT_SOURCE_WINKEY)) {
    event_status.temp_cw_input = ((LPC_GPIO1->FIOPIN & (1<<31)) >> 31);

    if (event_status.temp_cw_input)
      event_status.curr_cw_input |= (1<<SETTING_CW_INPUT_SOURCE_WINKEY);
    else
      event_status.curr_cw_input &= ~(1<<SETTING_CW_INPUT_SOURCE_WINKEY);
  }

  if (settings_get_cw_input_source() & (1<<SETTING_CW_INPUT_SOURCE_WINKEY_DTR)) {
    event_status.temp_cw_input = ((LPC_GPIO1->FIOPIN & (1<<17)) >> 17);

    if (event_status.temp_cw_input)
      event_status.curr_cw_input &= ~(1<<SETTING_CW_INPUT_SOURCE_WINKEY_DTR);
    else
      event_status.curr_cw_input |= (1<<SETTING_CW_INPUT_SOURCE_WINKEY_DTR);
  }

  if (settings_get_cw_input_source() & (1<<SETTING_CW_INPUT_SOURCE_WINKEY_RTS)) {
    event_status.temp_cw_input = ((LPC_GPIO1->FIOPIN & (1<<16)) >> 16);

    if (event_status.temp_cw_input)
      event_status.curr_cw_input &= ~(1<<SETTING_CW_INPUT_SOURCE_WINKEY_RTS);
    else
      event_status.curr_cw_input |= (1<<SETTING_CW_INPUT_SOURCE_WINKEY_RTS);
  }

  if (settings_get_cw_input_source() & (1<<SETTING_CW_INPUT_SOURCE_USB_DTR)) {
    event_status.temp_cw_input = ((LPC_GPIO2->FIOPIN & (1<<11)) >> 11);

    if (event_status.temp_cw_input)
      event_status.curr_cw_input &= ~(1<<SETTING_CW_INPUT_SOURCE_USB_DTR);
    else
      event_status.curr_cw_input |= (1<<SETTING_CW_INPUT_SOURCE_USB_DTR);
  }

  //Check if the CW input status has changed
  if (event_status.curr_cw_input != event_status.prev_cw_input) {
    if (event_status.curr_cw_input) {
      //ctrl_led_cw_on();
      ctrl_radio_cw_set();
    }
    else {
      //ctrl_led_cw_off();
      ctrl_radio_cw_clr();
    }

    event_status.prev_cw_input = event_status.curr_cw_input;
  }
}

void event_handler_execute(void) {
  if (event_status.flags & (1<<EVENT_HANDLER_CHECK_PTT_INPUTS)) {
    if (settings_get_ptt_input_enabled() & (1<<SETTING_PTT_INPUT_FOOTSWITCH)) {
      event_status.temp_ptt_input = ((LPC_GPIO3->FIOPIN & (1<<26)) >> 26);

      if (event_status.temp_ptt_input)
        event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_FOOTSWITCH);
      else
        event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_FOOTSWITCH);
    }

    if (settings_get_ptt_input_enabled() & (1<<SETTING_PTT_INPUT_WK)) {
      event_status.temp_ptt_input = ((LPC_GPIO1->FIOPIN & (1<<19)) >> 19);

      if (event_status.temp_ptt_input) {
        event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_WK);
      }
      else
        event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_WK);
    }

    if (settings_get_ptt_input_enabled() & (1<<SETTING_PTT_INPUT_FSKCW_RTS)) {
      event_status.temp_ptt_input = ((LPC_GPIO2->FIOPIN & (1<<13)) >> 13);

      if (settings_get_ptt_input_invert() & (1<<SETTING_PTT_INPUT_FSKCW_RTS)) {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_FSKCW_RTS);
        else
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_FSKCW_RTS);
      }
      else {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_FSKCW_RTS);
        else
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_FSKCW_RTS);
      }
    }

    if (settings_get_ptt_input_enabled() & (1<<SETTING_PTT_INPUT_WK_RTS)) {
      event_status.temp_ptt_input = ((LPC_GPIO1->FIOPIN & (1<<16)) >> 16);

      if (settings_get_ptt_input_invert() & (1<<SETTING_PTT_INPUT_WK_RTS)) {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_WK_RTS);
        else
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_WK_RTS);
      }
      else {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_WK_RTS);
        else
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_WK_RTS);
      }
    }

    if (settings_get_ptt_input_enabled() & (1<<SETTING_PTT_INPUT_WK_DTR)) {
      event_status.temp_ptt_input = ((LPC_GPIO1->FIOPIN & (1<<17)) >> 17);

      if (settings_get_ptt_input_invert() & (1<<SETTING_PTT_INPUT_WK_DTR)) {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_WK_DTR);
        else
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_WK_DTR);
      }
      else {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_WK_DTR);
        else
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_WK_DTR);
      }
    }

    if (settings_get_ptt_input_enabled() & (1<<SETTING_PTT_INPUT_VOX_SENSE)) {
      event_status.temp_ptt_input = 0;//((LPC_GPIO1->FIOPIN & (1<<17)) >> 17);

      if (settings_get_ptt_input_invert() & (1<<SETTING_PTT_INPUT_VOX_SENSE)) {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_VOX_SENSE);
        else
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_VOX_SENSE);
      }
      else {
        if (event_status.temp_ptt_input)
          event_status.curr_ptt_input &= ~(1<<STATUS_PTT_INPUT_VOX_SENSE);
        else
          event_status.curr_ptt_input |= (1<<STATUS_PTT_INPUT_VOX_SENSE);
      }
    }

    if (event_status.curr_ptt_input != event_status.prev_ptt_input) {
      //Execute the PTT sequencing etc
      event_handler_execute_ptt_change(event_status.prev_ptt_input,event_status.curr_ptt_input);

      //Update the PTT status to the computer
      status_set_ptt_input_state(event_status.curr_ptt_input);

      event_status.prev_ptt_input = event_status.curr_ptt_input;
    }

    event_status.flags &= ~(1<<EVENT_HANDLER_CHECK_PTT_INPUTS);
  }

  //Set the CW led
  if (event_status.curr_cw_input != event_status.cw_led_status) {
    if (event_status.curr_cw_input)
      ctrl_led_cw_on();
    else
      ctrl_led_cw_off();

    event_status.cw_led_status = event_status.curr_cw_input;
  }
}

void event_handler_1ms_tick(void) {
  counter_event_1ms++;
}

void event_handler_10us_tick(void) {
  if ((counter_event_10us % EVENT_HANDLER_POLL_PTT_STATUS_INTERVAL) == 0) {
    event_status.flags |= (1<<EVENT_HANDLER_CHECK_PTT_INPUTS);
  }

  //Check the CW input status every 100 us
  if ((counter_event_10us % 10) == 0) {
    event_handler_cw_execute();
  }

  counter_event_10us++;
}
