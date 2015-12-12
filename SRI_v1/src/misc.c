#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "misc.h"
#include "lpc17xx_uart.h"

void PRINTF(const char *format, ...) {
  #ifdef WK_PORT_DEBUG
    char output_str[DEBUG_STR_LEN];

    va_list arg;
    va_start (arg, format);
    int res = vsnprintf(output_str,sizeof(output_str),format,arg);
    va_end(arg);

    if (res > 0)
      UART_Send(LPC_UART2, (char *)output_str, res, BLOCKING);
  #endif

  #ifdef CAT_PORT_DEBUG
    char output_str[DEBUG_STR_LEN];

    va_list arg;
    va_start (arg, format);
    int res = vsnprintf(output_str,sizeof(output_str),format,arg);
    va_end(arg);

    if (res > 0)
      UART_Send(LPC_UART0, (char *)output_str, res, BLOCKING);
  #endif
}
