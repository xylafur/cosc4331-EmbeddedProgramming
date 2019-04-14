#ifndef TIMER_UTIL_HEADER
#define TIMER_UTIL_HEADER

// bit(s)
// 9-8  TASSEL
// 7-6  ID
// 5-4  MC
// 2    TACLR
// 1    TAIE
// 0    TAIFG
#define TIMER_CTL_MASK(TASSEL, ID, MC, TACLR, TAIE, TAIFG)              \
    (((TASSEL & 0x3) << 8) | ((ID & 0x3) << 6) | ((MC & 0x3) << 4) |    \
     ((TACLR & 0x1) << 2) | ((TAIE & 0x1) << 1) | (TAIFG & 0x1))


#define TIMER_CCTL_TOGGLE 0x80
#define TIMER_CCTL_TOGGLE_RESET 0x40


#endif

