#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "printf.h"
#include "iob-pwm.h"
#include "iob-gpio.h"
#include "iob-timer.h"


uint8_t sseg_table[9] = {255, 121, 36, 48, 25, 18, 2, 120, 0, 16}; //esta em decimal. nao sei se é preciso ser hexa
void display(uint16_t digits){

  uint8_t sseg_ca_value, digit_1, digit_2, digit_3, digit_4;

  digit_1 = digits/1000;
  digit_2 = digits/100 - (digits/1000)*1000;
  digit_3 = digits/10 - (digits/100)*100 - (digits/1000)*1000 ;
  digit_4 = digits - (digits/10)*10 - (digits/100)*100 - (digits/1000)*1000;
  
  sseg_ca_value = sseg_table[digit_1];	
  gpio_set_sseg_ca(sseg_ca_value); 
  gpio_set_sseg_an(1);
  timer_reset();
  while(timer_time_ms()<=20);
  
  sseg_ca_value = sseg_table[digit_2];
  gpio_set_sseg_ca(sseg_ca_value); 
  gpio_set_sseg_an(2);
  timer_reset();
  while(timer_time_ms()<=20);
  
  sseg_ca_value = sseg_table[digit_3];
  gpio_set_sseg_ca(sseg_ca_value); 
  gpio_set_sseg_an(4);
  timer_reset();
  while(timer_time_ms()<=20);
  
  sseg_ca_value = sseg_table[digit_4];
  gpio_set_sseg_ca(sseg_ca_value); 
  gpio_set_sseg_an(8);
  timer_reset();
  while(timer_time_ms()<=20);
  
}


int main()
{
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  //init pwm
  pwm_init(PWM_BASE);
  
  //init pwm
  gpio_init(GPIO_BASE);
  
  //init timer
  timer_init(TIMER_BASE);
  
  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");
  
  pwm_set_period(128);
  
  uint16_t freq=256, buffer=100 , sw_value, period;
  
  while(1){
  
  	sw_value = gpio_sw_get();
  
  	if(buffer != sw_value){
  	
  		buffer = sw_value;
  		
  		//freq = sw_value/16;
  		
  		//period = (1024 - 2*freq);
  		
  		period = freq;
  		
  		pwm_set_period(128);
  		
  	}
  	
  	display(freq);
  		
  
  gpio_set_sseg_ca(255);
  
  gpio_set_sseg_an(5);
  
  pwm_set_period(32);
  
  while(1);
  }
  uart_finish();
}
