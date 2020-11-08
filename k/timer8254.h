#ifndef TIMER8254_H_
#define TIMER8254_H_

#define PIT_COUNTER0	0x40
#define PIT_COUNTER1	0x41
#define PIT_COUNTER2	0x42
#define PIT_PORT	0x43

#define TIMER_BINARY_COUNTER	(0 << 0)
#define TIMER_BCD_COUNTER	(1 << 0)

#define TIMER_MODE(x)		(x << 1)

#define TIMER_READ		(0 << 4)
#define TIMER_RW_LSB		(1 << 4)
#define TIMER_RW_MSB		(2 << 4)
#define TIMER_RW_LSB_MSB	(3 << 4)

#define TIMER_COUNTER_SETUP(x)	(x << 6)

#define TIMER_MAX_FREQUENCY	1193182
#define TIMER_DESIRED_FREQUENCY	1000


#ifndef __ASSEMBLER__
void set_timer();
#endif

#endif