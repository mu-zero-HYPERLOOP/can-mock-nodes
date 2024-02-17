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

  while (1) {
    // calcualte SDC-status

    /* if (canzero_get_sdc_ */
    /* printf("SDC_STATUS: %u\n", canzero_get_pdu12_sdc_status()); */
    usleep(100000);
  }
  return 0;
}
