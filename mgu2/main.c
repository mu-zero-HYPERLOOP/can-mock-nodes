/**
 * @author      : kistenklaus (karlsasssie@gmail.com)
 * @created     : 16/02/2024
 * @filename    : main
 */
#include "can.h"
#include "canzero.h"
#include "time_util.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  can_start();

  uint32_t last_transition = 0;

  while (1) {
    mgu_state state = canzero_get_state();
    mgu_command command = canzero_get_command();
    mgu_state next_state = state;

    sdc_status sdc_status = sdc_status_OPEN;
    float temperature = 0;

    switch (state) {
    case mgu_state_INIT:
      if (time_now_ms() > 1000) {
        next_state = mgu_state_IDLE;
      }
      break;
    case mgu_state_IDLE:
      switch (command) {
      case mgu_command_PRECHARGE:
        next_state = mgu_state_PRECHARGE;
        break;
      default:
        break;
      }
      break;
    case mgu_state_PRECHARGE:
      sdc_status = sdc_status_CLOSED;
      if (time_now_ms() - last_transition > 1000) {
        next_state = mgu_state_READY;
      }
      switch(command) {
      case mgu_command_DISCONNECT:
        next_state = mgu_state_IDLE;
        break;
      default:
        break;
      }
      break;
    case mgu_state_READY:
      sdc_status = sdc_status_CLOSED;
      switch (command) {
      case mgu_command_DISCONNECT:
        next_state = mgu_state_IDLE;
        break;
      case mgu_command_START:
        next_state = mgu_state_START;
        break;
      default:
        break;
      }
      break;
    case mgu_state_START:
      temperature = 100;
      sdc_status = sdc_status_CLOSED;
      if (time_now_ms() - last_transition > 500) {
        next_state = mgu_state_CONTROL;
      }
      switch (command) {
      case mgu_command_DISCONNECT:
        next_state = mgu_state_IDLE;
        break;
      case mgu_command_STOP:
        next_state = mgu_state_STOP;
      default:
        break;
      }
      break;
    case mgu_state_CONTROL:
      temperature = 100;
      sdc_status = sdc_status_CLOSED;
      switch ( command) {
      case mgu_command_DISCONNECT:
        next_state = mgu_state_IDLE;
        break;
      case mgu_command_STOP:
        next_state = mgu_state_STOP;
        break;
      default:
        break;
      }
      break;
    case mgu_state_STOP:
      temperature = 100;
      sdc_status = sdc_status_CLOSED;
      if (time_now_ms() - last_transition > 500) {
        next_state = mgu_state_READY;
      }
      switch(command) {
      case mgu_command_DISCONNECT:
        next_state = mgu_state_IDLE;
        break;
      default:
        break;
      }
      break;
    }

    if (state != next_state) {
      last_transition = time_now_ms();
      canzero_set_state(next_state);
    }
    canzero_set_sdc_status(sdc_status);
    canzero_set_magnet_temperature_port(temperature);
    canzero_set_magnet_temperature_starboard(temperature);
  }
  return 0;
}
