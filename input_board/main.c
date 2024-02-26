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

  canzero_set_sdc_status(sdc_status_CLOSED);

  while (1) {
    usleep(100);
  }
  return 0;
}
