#include<lpc21xx.h>
int main()
{
uart0_init(9600);
adc_init();
uart0_string("\r\n LDR light Monitoring:");
while(1)
{
unsigned int adc_value;
adc_value=adc_read();
uart0_string("ADC VALUE: ");
uart0_integer(adc_value);
uart0_string("\r\n");
delay_ms(200);
}
}
