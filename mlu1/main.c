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

  float mock_airgap = 12;
  uint32_t prev_transition = 0;
  while (1) {
    float temperature = 0;

    // State Machine
    mlu_state state = canzero_get_state();
    mlu_state next_state = state;
    mlu_command command = canzero_get_command();
    sdc_status sdc_status = sdc_status_OPEN;

    switch (state) {
    case mlu_state_INIT:
      if (time_now_ms() > 2000) {
        next_state = mlu_state_IDLE;
      }
      break;
    case mlu_state_IDLE:
      mock_airgap = 12;
      switch (command) {
      case mlu_command_PRECHARGE:
        next_state = mlu_state_PRECHARGE;
        break;
      default:
        break;
      }
      break;
    case mlu_state_PRECHARGE:
      sdc_status = sdc_status_CLOSED;
      mock_airgap = 12;
      if (time_now_ms() - prev_transition > 1000) {
        next_state = mlu_state_READY;
      }
      switch (command) {
      case mlu_command_DISCONNECT:
        next_state = mlu_state_IDLE;
        break;
      default:
        break;
      }
      break;
    case mlu_state_READY:
      sdc_status = sdc_status_CLOSED;
      mock_airgap = 12;
      switch (command) {
      case mlu_command_START:
        next_state = mlu_state_START;
        break;
      case mlu_command_DISCONNECT:
        next_state = mlu_state_IDLE;
        break;
      default:
        break;
      }
      break;
    case mlu_state_START:
      sdc_status = sdc_status_CLOSED;
      temperature = 100;
      mock_airgap -= 0.003;
      if (mock_airgap <= 6) {
        next_state = mlu_state_CONTROL;
      }
      switch (command) {
      case mlu_command_DISCONNECT:
        next_state = mlu_state_IDLE;
        break;
      case mlu_command_STOP:
      case mlu_command_ABORT:
        next_state = mlu_state_STOP;
        break;
      default:
        break;
      }
      break;
    case mlu_state_CONTROL:
      sdc_status = sdc_status_CLOSED;
      temperature = 100;
      switch (command) {
      case mlu_command_DISCONNECT:
        next_state = mlu_state_IDLE;
        break;
      case mlu_command_STOP:
      case mlu_command_ABORT:
        next_state = mlu_state_STOP;
      default:
        break;
      }
      break;
    case mlu_state_STOP:
      sdc_status = sdc_status_CLOSED;
      temperature = 100;
      mock_airgap += 0.003;
      if (mock_airgap >= 12) {
        next_state = mlu_state_READY;
      }
      switch (command) {
      case mlu_command_DISCONNECT:
        next_state = mlu_state_IDLE;
        break;
      default:
        break;
      }
      break;
    }

    if (state != next_state) {
      prev_transition = time_now_ms();
      canzero_set_state(next_state);
    }
    canzero_set_sdc_status(sdc_status);
    canzero_set_magnet_temperature(temperature);
    canzero_set_air_gap(mock_airgap);

    canzero_update_continue(canzero_get_time());

    usleep(1000);
  }
  return 0;
}
