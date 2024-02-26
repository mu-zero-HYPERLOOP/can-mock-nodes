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
  float velocity = 0;
  while (1) {
    float acceleration = 0;   

    motor_state state = canzero_get_state();
    motor_command command = canzero_get_command();
    motor_state next_state = state;

    sdc_status sdc_status = sdc_status_OPEN;

    switch (state) {
    case motor_state_INIT:
      if (time_now_ms() > 1000) {
        next_state = motor_state_IDLE;
      }
      break;
    case motor_state_IDLE:
      switch (command) {
      case motor_command_PRECHARGE:
        next_state = motor_state_PRECHARGE;
        break;
      default:
        break;
      }
      break;
    case motor_state_PRECHARGE:
      sdc_status = sdc_status_CLOSED;
      if (time_now_ms() - last_transition > 1000) {
        next_state = motor_state_READY;
        break;
      }
      switch (command) {
      case motor_command_DISCONNECT:
        next_state = motor_state_IDLE;
      default:
        break;
      }
      break;
    case motor_state_READY:
      sdc_status = sdc_status_CLOSED;
      switch (command) {
      case motor_command_DISCONNECT:
        next_state = motor_state_IDLE;
        break;
      case motor_command_ACCELERATE:
        next_state = motor_state_START;
        break;
      default:
        break;
      }
      break;
    case motor_state_START:
      sdc_status = sdc_status_CLOSED;
      acceleration = 1;
      if (velocity > 3) {
        next_state = motor_state_CONTROL;
      }
      switch (command) {
      case motor_command_DISCONNECT:
        next_state = motor_state_IDLE;
        break;
      case motor_command_DECELERATE:
        next_state = motor_state_STOP;
        break;
      default:
        break;
      }
      break;
    case motor_state_CONTROL:
      sdc_status = sdc_status_CLOSED;
      switch (command) {
      case motor_command_DECELERATE:
        next_state = motor_state_STOP;
        break;
      case motor_command_DISCONNECT:
        next_state = motor_state_IDLE;
        break;
      default:
        break;
      }
      break;
    case motor_state_STOP:
      sdc_status = sdc_status_CLOSED;
      acceleration = -1;
      if (velocity <= 0) {
        next_state = motor_state_READY;
      }
      switch (command) {
      case motor_command_DISCONNECT:
        next_state = motor_state_IDLE;
        break;
      default:
        break;
      }
    default:
      break;
    }

    if (state != next_state) {
      last_transition = time_now_ms();
      canzero_set_state(next_state);
    }

    velocity += acceleration;

    canzero_set_local_acceleration(acceleration);
    canzero_set_sdc_status(sdc_status);
    canzero_update_continue(canzero_get_time());

    usleep(1000);
  }

  return 0;
}
