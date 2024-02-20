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

  uint32_t prev_state_transition = 0;
  while (1) {
    // SDC-Status
    sdc_status sdc_status =
        canzero_get_mlu1_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mlu2_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mlu3_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mlu4_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mlu5_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mlu6_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mgu1_sdc_status() == sdc_status_CLOSED &&
        canzero_get_mgu2_sdc_status() == sdc_status_CLOSED &&
        canzero_get_pdu12_sdc_status() == sdc_status_CLOSED &&
        canzero_get_pdu24_sdc_status() == sdc_status_CLOSED &&
        canzero_get_input_board_sdc_status() == sdc_status_CLOSED &&
        canzero_get_motor_sdc_status() == sdc_status_CLOSED;
    canzero_set_sdc_status(sdc_status);

    // Power estimation
    float power_estimation24 = 0;
    power_estimation24 += canzero_get_pdu12_power_estimation();
    power_estimation24 += canzero_get_pdu24_power_estimation();
    float power_estimation48 = 0;
    power_estimation48 += canzero_get_mlu1_power_estimation();
    power_estimation48 += canzero_get_mlu2_power_estimation();
    power_estimation48 += canzero_get_mlu3_power_estimation();
    power_estimation48 += canzero_get_mlu4_power_estimation();
    power_estimation48 += canzero_get_mlu5_power_estimation();
    power_estimation48 += canzero_get_mlu6_power_estimation();
    power_estimation48 += canzero_get_mgu1_power_estimation();
    power_estimation48 += canzero_get_mgu2_power_estimation();
    power_estimation48 += canzero_get_motor_power_estimation();
    canzero_set_power_estimation24(power_estimation24);
    canzero_set_power_estimation48(power_estimation48);
    canzero_set_power_estimation(power_estimation24 + power_estimation48);

    // State Machine!
    global_command command = canzero_get_command();
    global_state state = canzero_get_global_state();
    global_state next_state = state;
    switch (state) {
    case global_state_INIT:
      canzero_set_mgu_command(mgu_command_DISCONNECT);
      canzero_set_mlu_command(mlu_command_DISCONNECT);
      canzero_set_motor_command(motor_command_DISCONNECT);
      // ignore all commands!
      if (time_now_ms() > 3000) {
        next_state = global_state_IDLE;
        printf("Transition into INIT\n");
      }
      break;
    case global_state_IDLE:
      switch (command) {
      case global_command_PRECHARGE:
        next_state = global_state_PRECHARGE;
        break;
      default:
        break;
      }
      break;
    case global_state_DISCONNECTING:
      canzero_set_mgu_command(mgu_command_DISCONNECT);
      canzero_set_mlu_command(mlu_command_DISCONNECT);
      canzero_set_motor_command(motor_command_DISCONNECT);
      if (canzero_get_mlu1_state() == mlu_state_IDLE
          && canzero_get_mlu2_state() == mlu_state_IDLE
          && canzero_get_mlu3_state() == mlu_state_IDLE
          && canzero_get_mlu4_state() == mlu_state_IDLE
          && canzero_get_mlu5_state() == mlu_state_IDLE
          && canzero_get_mlu6_state() == mlu_state_IDLE
          && canzero_get_mgu1_state() == mgu_state_IDLE
          && canzero_get_mgu2_state() == mgu_state_IDLE
          && canzero_get_motor_state() == motor_state_IDLE
          ) {
        next_state = global_state_IDLE;
      }
      break;
    case global_state_PRECHARGE:
      canzero_set_mgu_command(mgu_command_PRECHARGE);
      canzero_set_mlu_command(mlu_command_PRECHARGE);
      canzero_set_motor_command(motor_command_PRECHARGE);
      if (canzero_get_mlu1_state() == mlu_state_READY &&
          canzero_get_mlu2_state() == mlu_state_READY &&
          canzero_get_mlu3_state() == mlu_state_READY &&
          canzero_get_mlu4_state() == mlu_state_READY &&
          canzero_get_mlu5_state() == mlu_state_READY &&
          canzero_get_mlu6_state() == mlu_state_READY &&
          canzero_get_mgu1_state() == mgu_state_READY &&
          canzero_get_mgu2_state() == mgu_state_READY &&
          canzero_get_motor_state() == motor_state_READY) {
        next_state = global_state_READY;
      }
      switch (command) {
      case global_command_DISCONNECT:
      case global_command_ABORT:
      case global_command_EMERGENCY:
        next_state = global_state_DISCONNECTING;
        break;
      default:
        break;
      }
      break;
    case global_state_READY:
      canzero_set_mlu_command(mlu_command_STOP);
      canzero_set_mgu_command(mgu_command_STOP);
      canzero_set_motor_command(motor_command_STOP);
      switch (command) {
      case global_command_DISCONNECT:
      case global_command_ABORT:
        next_state = global_state_DISCONNECTING;
        break;
      case global_command_START_LEVITATION:
        next_state = global_state_START_LEVITATION;
        break;
      case global_command_EMERGENCY:
        next_state = global_state_DISCONNECTING;
        break;
      default:
        break;
      }
      break;
    case global_state_START_LEVITATION:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_STOP);
      canzero_set_motor_command(motor_command_STOP);
      if (canzero_get_mlu1_state() == mlu_state_CONTROL &&
          canzero_get_mlu2_state() == mlu_state_CONTROL &&
          canzero_get_mlu3_state() == mlu_state_CONTROL &&
          canzero_get_mlu4_state() == mlu_state_CONTROL &&
          canzero_get_mlu5_state() == mlu_state_CONTROL &&
          canzero_get_mlu6_state() == mlu_state_CONTROL) {
        next_state = global_state_LEVITATION_STABLE;
      }
      switch (command) {
      case global_command_ABORT:
      case global_command_STOP_LEVITATION:
        next_state = global_state_STOP_LEVITATION;
        break;
      case global_command_EMERGENCY:
      case global_command_DISCONNECT:
        next_state = global_state_DISCONNECTING;
        break;
      default:
        break;
      }
      break;
    case global_state_LEVITATION_STABLE:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_STOP);
      canzero_set_motor_command(motor_command_STOP);
      next_state = global_state_START_GUIDANCE;
      break;
    case global_state_START_GUIDANCE:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_START);
      canzero_set_motor_command(motor_command_STOP);
      if (canzero_get_mgu1_state() == mgu_state_CONTROL &&
          canzero_get_mgu2_state() == mgu_state_CONTROL) {
        next_state = global_state_GUIDANCE_STABLE;
      }
      switch (command) {
      case global_command_STOP_LEVITATION:
      case global_command_ABORT:
        next_state = global_state_STOP_LEVITATION;
        break;
      case global_command_EMERGENCY:
      case global_command_DISCONNECT:
        next_state = global_state_DISCONNECTING;
        break;
      default:
        break;
      }
      break;
    case global_state_GUIDANCE_STABLE:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_START);
      canzero_set_motor_command(motor_command_STOP);
      switch (command) {
      case global_command_ABORT:
      case global_command_STOP_LEVITATION:
        next_state = global_state_STOP_LEVITATION;
        break;
      case global_command_EMERGENCY:
      case global_command_DISCONNECT:
        next_state = global_state_DISCONNECTING;
        break;
      case global_command_START_PROPULSION:
        next_state = global_state_ACCELERATION;
        break;
      default:
        break;
      }
      break;
    case global_state_ACCELERATION:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_START);
      canzero_set_motor_command(motor_command_ACCELERATE);
      if (canzero_get_motor_state() == motor_state_CONTROL) {
        next_state = global_state_CRUISING;
      }
      switch (command) {
      case global_command_DISCONNECT:
      case global_command_EMERGENCY:
        next_state = global_state_DISCONNECTING;
        break;
      case global_command_STOP_PROPULSION:
      case global_command_STOP_LEVITATION:
      case global_command_ABORT:
        next_state = global_state_DECELERATION;
        break;
      default:
        break;
      }
      break;
    case global_state_CRUISING:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_START);
      canzero_set_motor_command(motor_command_ACCELERATE);
      switch (command) {
      case global_command_DISCONNECT:
      case global_command_EMERGENCY:
        printf("CRUSING -> DISCONNECT\n");
        next_state = global_state_DISCONNECTING;
        break;
      case global_command_STOP_PROPULSION:
      case global_command_STOP_LEVITATION:
      case global_command_ABORT:
        printf("CRUSING -> DECELERATION\n");
        next_state = global_state_DECELERATION;
        break;
      default:
        break;
      }
      break;
    case global_state_DECELERATION:
      canzero_set_mlu_command(mlu_command_START);
      canzero_set_mgu_command(mgu_command_START);
      canzero_set_motor_command(motor_command_DECELERATE);
      if (canzero_get_motor_state() == motor_state_READY) {
        printf("DECELERATION -> GUIDANCE_STABLE\n");
        next_state = global_state_GUIDANCE_STABLE;
      }
      switch (command) {
      case global_command_DISCONNECT:
      case global_command_EMERGENCY:
        printf("DECELERATION EMCY\n");
        next_state = global_state_DISCONNECTING;
        break;
      default:
        break;
      }
      break;
    case global_state_STOP_LEVITATION:
      canzero_set_mlu_command(mlu_command_STOP);
      canzero_set_mgu_command(mgu_command_STOP);
      canzero_set_motor_command(motor_command_STOP);
      if (canzero_get_mlu1_state() == mlu_state_READY &&
          canzero_get_mlu2_state() == mlu_state_READY &&
          canzero_get_mlu3_state() == mlu_state_READY &&
          canzero_get_mlu4_state() == mlu_state_READY &&
          canzero_get_mlu5_state() == mlu_state_READY &&
          canzero_get_mlu6_state() == mlu_state_READY &&
          canzero_get_mgu1_state() == mgu_state_READY &&
          canzero_get_mgu2_state() == mgu_state_READY
          ) {
        next_state = global_state_READY;
      }
      switch (command) {
      case global_command_DISCONNECT:
      case global_command_EMERGENCY:
        next_state = global_state_DISCONNECTING;
        break;
      default:
        break;
      }
      break;
    }
    if (state != next_state) {
      prev_state_transition = time_now_ms();
      canzero_set_global_state(next_state);
    }

    usleep(100000);
  }
  return 0;
}
