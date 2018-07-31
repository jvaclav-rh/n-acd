#pragma once

#include <c-rbtree.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>

enum {
        TIMER_E_SUCCESS,

        TIMER_E_TRIGGERED,
};

typedef struct Timer Timer;
typedef struct Timeout Timeout;

struct Timer {
        int fd;
        CRBTree tree;
        uint64_t scheduled_timeout;
};

#define TIMER_NULL(_x) {                                                        \
                .fd = -1,                                                       \
                .tree = C_RBTREE_INIT,                                          \
        }

struct Timeout {
        Timer *timer;
        CRBNode node;
        uint64_t timeout;
};

#define TIMEOUT_INIT(_x) {                                                      \
                .node = C_RBNODE_INIT((_x).node),                               \
        }

int timer_init(Timer *timer);
void timer_deinit(Timer *timer);

void timer_now(Timer *timer, uint64_t *nowp);

int timer_pop(Timer *timer, uint64_t now, Timeout **timerp);
void timer_rearm(Timer *timer);
int timer_read(Timer *timer);

void timeout_schedule(Timeout *timeout, Timer *timer, uint64_t time);
void timeout_unschedule(Timeout *timeout);

