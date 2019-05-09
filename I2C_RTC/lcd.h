#include <reg51.h>
void startbit(void);
void delay1(void);
void stopbit(void);
void ackbit(void);
char sendi2c(char var);
char readi2c(void);
void nack(void);
char dec_bcd(char dec);
void lcd_digit(char var);
void readack(void);
void display_date(char date, char month, char year, char day);
void read_date(void);
void set_date(char day, char date, char month, char year);

void lcd_cmd(char a);
void lcd_data(char b);
void lcd_init(void);
void delay(void);
void print_lcd(char *ptr);

char bcd_dec(char var);

void status_alarm(char x);
void set_alarm(char x);


void msdelay(int m);



void uart_init(void);
void uart_tx(char var);
void uart_print(char *ptr);
char uart_rx(void);
void uart_array(char ptr[30]);