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

  canzero_set_lp_channel1_control( pdu_channel_control_OFF);
  canzero_set_lp_channel2_control( pdu_channel_control_OFF);
  canzero_set_lp_channel3_control( pdu_channel_control_OFF);
  canzero_set_lp_channel4_control( pdu_channel_control_OFF);
  canzero_set_lp_channel5_control( pdu_channel_control_OFF);
  canzero_set_lp_channel6_control( pdu_channel_control_OFF);
  canzero_set_lp_channel7_control( pdu_channel_control_OFF);
  canzero_set_lp_channel7_control( pdu_channel_control_OFF);
  canzero_set_lp_channel8_control( pdu_channel_control_OFF);
  canzero_set_lp_channel9_control( pdu_channel_control_OFF);
  canzero_set_lp_channel10_control(pdu_channel_control_OFF);
  canzero_set_lp_channel11_control(pdu_channel_control_OFF);
  canzero_set_lp_channel12_control(pdu_channel_control_OFF);
  canzero_set_hp_channel1_control( pdu_channel_control_OFF);
  canzero_set_hp_channel2_control( pdu_channel_control_OFF);
  canzero_set_hp_channel3_control( pdu_channel_control_OFF);
  canzero_set_hp_channel4_control( pdu_channel_control_OFF);

  while (1) {
    float x = ((float)rand()/(float)(RAND_MAX)) * 0.3 - 0.15;

    if (canzero_get_lp_channel1_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel1_status(pdu_channel_status_ON);
      canzero_set_lp_channel1_current(2 + x);
    }else {
      canzero_set_lp_channel1_status(pdu_channel_status_OFF);
      canzero_set_lp_channel1_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel2_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel2_status(pdu_channel_status_ON);
      canzero_set_lp_channel2_current(2+x);
    }else {
      canzero_set_lp_channel2_status(pdu_channel_status_OFF);
      canzero_set_lp_channel2_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel3_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel3_status(pdu_channel_status_ON);
      canzero_set_lp_channel3_current(2 + x);
    }else {
      canzero_set_lp_channel3_status(pdu_channel_status_OFF);
      canzero_set_lp_channel3_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel4_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel4_status(pdu_channel_status_ON);
      canzero_set_lp_channel4_current(2 + x);
    }else {
      canzero_set_lp_channel4_status(pdu_channel_status_OFF);
      canzero_set_lp_channel4_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel5_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel5_status(pdu_channel_status_ON);
      canzero_set_lp_channel5_current(2 + x);
    }else {
      canzero_set_lp_channel5_status(pdu_channel_status_OFF);
      canzero_set_lp_channel5_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel6_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel6_status(pdu_channel_status_ON);
      canzero_set_lp_channel6_current(2 + x);
    }else {
      canzero_set_lp_channel6_status(pdu_channel_status_OFF);
      canzero_set_lp_channel6_current(0.01 + x * 0.05);
 
    }
    if (canzero_get_lp_channel7_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel7_status(pdu_channel_status_ON);
      canzero_set_lp_channel7_current(2 + x);
    }else {
      canzero_set_lp_channel7_status(pdu_channel_status_OFF);
      canzero_set_lp_channel7_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel8_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel8_status(pdu_channel_status_ON);
      canzero_set_lp_channel8_current(2 + x);
    }else {
      canzero_set_lp_channel8_status(pdu_channel_status_OFF);
      canzero_set_lp_channel8_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel9_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel9_status(pdu_channel_status_ON);
      canzero_set_lp_channel9_current(2 + x);
    }else {
      canzero_set_lp_channel9_status(pdu_channel_status_OFF);
      canzero_set_lp_channel9_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel10_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel10_status(pdu_channel_status_ON);
      canzero_set_lp_channel10_current(2 +x);
    }else {
      canzero_set_lp_channel10_status(pdu_channel_status_OFF);
      canzero_set_lp_channel10_current(0.01 + x * 0.05);
    }

    if (canzero_get_lp_channel11_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel11_status(pdu_channel_status_ON);
      canzero_set_lp_channel11_current(2 + x);
    }else {
      canzero_set_lp_channel11_status(pdu_channel_status_OFF);
      canzero_set_lp_channel11_current(0.01 + x * 0.05);
    }
    if (canzero_get_lp_channel12_control() == pdu_channel_control_ON) {
      canzero_set_lp_channel12_status(pdu_channel_status_ON);
      canzero_set_lp_channel12_current(2 + x);
    }else {
      canzero_set_lp_channel12_status(pdu_channel_status_OFF);
      canzero_set_lp_channel12_current(0.01 + x * 0.05);
    }

    if (canzero_get_hp_channel1_control() == pdu_channel_control_ON) {
      canzero_set_hp_channel1_status(pdu_channel_status_ON);
      canzero_set_hp_channel1_current(4 + x);
    }else {
      canzero_set_hp_channel1_status(pdu_channel_status_OFF);
      canzero_set_hp_channel1_current(0.01 + x * 0.05);
    }

    if (canzero_get_hp_channel2_control() == pdu_channel_control_ON) {
      canzero_set_hp_channel2_status(pdu_channel_status_ON);
      canzero_set_hp_channel2_current(4 + x);
    }else {
      canzero_set_hp_channel2_status(pdu_channel_status_OFF);
      canzero_set_hp_channel2_current(0.01 + x * 0.05);
    }
    if (canzero_get_hp_channel3_control() == pdu_channel_control_ON) {
      canzero_set_hp_channel3_status(pdu_channel_status_ON);
      canzero_set_hp_channel3_current(4 + x);
    }else {
      canzero_set_hp_channel3_status(pdu_channel_status_OFF);
      canzero_set_hp_channel3_current(0.01 + x * 0.05);
    }

    if (canzero_get_hp_channel4_control() == pdu_channel_control_ON) {
      canzero_set_hp_channel4_status(pdu_channel_status_ON);
      canzero_set_hp_channel4_current(4 + x);
    }else {
      canzero_set_hp_channel4_status(pdu_channel_status_OFF);
      canzero_set_hp_channel4_current(0.01 + x * 0.05);
    }
    usleep(100);
  }
  return 0;
}
