void lcdData(char var);
void lcdCmd(char var);
void lcdInit(void);
void lcdPrint(char *ptr);

void msdelay(int m);
void delay(void);
void readAck(void);
void delay1(void);

void i2cStop(void);
char readI2c(void);
char sendI2c(char var);
void startBit(void);
void stopBit(void);

char bcdDec(char var);
char displayAmpm(char hr);
char decBcd(char dec);
void lcdDigit(char var);
void displayDate(char date, char month, char year, char day);
void readDate(void);
void setDate(char day, char date, char month, char year);
