#ifndef INC_RTG_H_
#define INC_RTG_H_

#include "usart.h"
#include "lwip.h"

/**
 * override printf
 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

extern struct netif gnetif;	//Generic data structure used for all lwIP network interfaces.

extern UART_HandleTypeDef huart3;
#define UART_DEBUG &huart3

extern
/*
 * BEGIN for Tools
 */
#define LINE_FEED 10
#define CARRIAGE_RETURN 13
/*
 * END for Tools
 */

void rtg_main();


#endif /* INC_RTG_H_ */

