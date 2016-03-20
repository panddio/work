#ifndef __UART_DEBUG_H__
#define __UART_DEBUG_H__

int uart_init(int num);
void uart_uninit(int fd);
void uart_send_str(int uart_fd, char *str);
void uart_debug(int uart_id, char *head, char *debug_info);

#endif