
#include "canzero.h"
#include "mutex.h"
#include "socketcan.h"
#include "thread.h"
#include "time_util.h"
#include <stdlib.h>

static socketcan_socket can0;
static socketcan_socket can1;

void canzero_can0_setup(uint32_t baudrate, canzero_can_filter *filters,
                        int filter_count) {
  int erno;
  if (filter_count == 0) {
    erno = socketcan_socket_open(&can0, SOCKETCAN_BUS_CAN0, NULL, 0);
  } else {
    socketcan_filter *socket_filters =
        calloc(sizeof(socketcan_filter), filter_count);
    for (int i = 0; i < filter_count; ++i) {
      socket_filters->can_id = filters[i].id;
      socket_filters->can_mask = filters[i].mask;
    }
    erno = socketcan_socket_open(&can0, SOCKETCAN_BUS_CAN0, socket_filters,
                                 filter_count);
    free(socket_filters);
  }
  if (erno) {
    perror("Connected to can0");
    exit(EXIT_FAILURE);
  } else {
    printf("successfully connected can0\n");
  }
}

void canzero_can1_setup(uint32_t baudrate, canzero_can_filter *filters,
                        int filter_count) {
  int erno;
  if (filter_count == 0) {
    erno = socketcan_socket_open(&can1, SOCKETCAN_BUS_CAN1, NULL, 0);
  } else {
    socketcan_filter *socket_filters =
        calloc(sizeof(socketcan_filter), filter_count);
    for (int i = 0; i < filter_count; ++i) {
      socket_filters->can_id = filters[i].id;
      socket_filters->can_mask = filters[i].mask;
    }
    erno = socketcan_socket_open(&can1, SOCKETCAN_BUS_CAN1, socket_filters,
                          filter_count);
    free(socket_filters);
  }
  if (erno) {
    perror("Connected to can1");
    exit(EXIT_FAILURE);
  } else {
    printf("successfully connected can1\n");
  }
}

void canzero_can0_send(canzero_frame *frame) {
  socketcan_frame socket_frame;
  socket_frame.can_id = frame->id;
  socket_frame.len = frame->dlc;
  memcpy(&socket_frame.data, frame->data, sizeof(uint8_t) * 8);
  int erno = socketcan_send_frame(&can0, &socket_frame);
  if (erno) {
    perror("Sending on can0");
    exit(EXIT_FAILURE);
  }
}

void canzero_can1_send(canzero_frame *frame) {
  socketcan_frame socket_frame;
  socket_frame.can_id = frame->id;
  socket_frame.len = frame->dlc;
  memcpy(&socket_frame.data, frame->data, sizeof(uint8_t) * 8);
  int erno = socketcan_send_frame(&can1, &socket_frame);
  if (erno) {
    perror("Sending on can1");
  }
}

int canzero_can0_recv(canzero_frame *frame) {
  socketcan_frame socket_frame;
  int erno = socketcan_recv_frame(&can0, &socket_frame);
  if (erno) {
    perror("secu: receive frame");
    exit(EXIT_FAILURE);
  }
  frame->id = socket_frame.can_id;
  frame->dlc = socket_frame.can_dlc;
  memcpy(frame->data, socket_frame.data, sizeof(uint8_t) * 8);
  return 1;
}

int canzero_can1_recv(canzero_frame *frame) {
  socketcan_frame socket_frame;
  int erno = socketcan_recv_frame(&can1, &socket_frame);
  if (erno) {
    perror("secu: receive frame");
    exit(EXIT_FAILURE);
  }
  frame->id = socket_frame.can_id;
  frame->dlc = socket_frame.can_dlc;
  memcpy(frame->data, socket_frame.data, sizeof(uint8_t) * 8);
  return 1;
}

uint32_t canzero_get_time() { return time_now_ms(); }

static mutex critical_mutex;

void canzero_enter_critical() { mutex_lock(&critical_mutex); }

void canzero_exit_critical() { mutex_unlock(&critical_mutex); }

static uint32_t next_update = 0;

void canzero_request_update(uint32_t time) {
  next_update = time;
}

static void *can0_rx_loop(void *_) {
  while (1) {
    uint32_t now = time_now_ms();
    canzero_can0_poll();
  }
  return NULL;
}

static void *can1_rx_loop(void *_) {
  while (1) {
    uint32_t now = time_now_ms();
    canzero_can1_poll();
  }
  return NULL;
}

static void *update_loop(void *_) {
  while (1) {
    uint32_t timeout = next_update - time_now_ms();
    for (uint32_t i = 0; i < timeout * 1000; i++) {
      usleep(1);
      uint32_t now = time_now_ms();
      if (now >= next_update)
        break;
    }
    uint32_t now = time_now_ms();
    next_update = canzero_update_continue(now);
  }
  return NULL;
}

thread can0_rx_thread;
thread can1_rx_thread;
thread canzero_thread;

void can_start() {
  mutex_create(&critical_mutex);
  time_init();
  canzero_init();
  thread_create(&can0_rx_thread, can0_rx_loop, NULL);
  thread_create(&can1_rx_thread, can1_rx_loop, NULL);
  thread_create(&canzero_thread, update_loop, NULL);
}
