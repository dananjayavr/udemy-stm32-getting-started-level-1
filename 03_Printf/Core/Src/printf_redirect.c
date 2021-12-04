/*
 * printf_redirect.c
 *
 *  Created on: Dec 4, 2021
 *      Author: dananjaya
 */


#include "uart.h"

int __io_putchar(int ch);
int _write(int file, char *ptr, int len);

int __io_putchar(int ch) {
  uint8_t c[1];
  c[0] = ch & 0x00FF;
  uart_UART1_Tx(&c[0], 1, 100);
  return ch;
}

int _write(int file, char *ptr, int len) {
  int dataIdx;
  for(dataIdx = 0; dataIdx < len; dataIdx++) {
    __io_putchar(*ptr++);
  }
  return len;
}
