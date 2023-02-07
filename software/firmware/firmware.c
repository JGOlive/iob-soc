#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "printf.h"
#include "iob-pwm.h"
#include "iob-gpio.h"
#include "iob-timer.h"

#define DISPLAY_REFRESH_RATE 2

uint8_t sseg_table[10] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144}; //esta em decimal. nao sei se é preciso ser hexa
uint8_t sseg_table_point[10] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16}; //com ponto
void display(uint32_t digits){

  uint8_t sseg_ca_value, digit_1, digit_2, digit_3, digit_4;

  
  if(digits <= 10000){
	  digit_1 = digits/1000; 
	  digit_2 = (digits%1000)/100;
	  digit_3 = (digits%100)/10;
	  digit_4 = (digits%10);
	  
	  sseg_ca_value = sseg_table[digit_1];	
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(7);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_2];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(11);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_3];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(13);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_4];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(14);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
  
  }else if(digits >= 10000){
  
	  digit_1 = digits/10000; 
	  digit_2 = (digits%10000)/1000;
	  digit_3 = (digits%1000)/100;
	  digit_4 = (digits%100)/10;
	  
	  sseg_ca_value = sseg_table[digit_1];	
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(7);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table_point[digit_2];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(11);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_3];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(13);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_4];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(14);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
  
  }else if(digits >= 100000){
  	  uint32_t cem_mil = 10000;
  	  cem_mil = cem_mil*10;	
	  digit_1 = digits/cem_mil; 
	  digit_2 = (digits%cem_mil)/10000;
	  digit_3 = (digits%10000)/1000;
	  digit_4 = (digits%1000)/100;
	  
	    sseg_ca_value = sseg_table[digit_1];	
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(7);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_2];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(11);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table_point[digit_3];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(13);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
	  
	  sseg_ca_value = sseg_table[digit_4];
	  gpio_set_sseg_ca(sseg_ca_value); 
	  gpio_set_sseg_an(14);
	  timer_reset();
	  while(timer_time_ms()<=DISPLAY_REFRESH_RATE);
  
  }
  
  return;
  
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
  
  uint32_t freq = 2861; // freq = ((190.7348633*sw_value)/10)*10;
  uint16_t buffer = 0, sw_value = 15, period;

  while(1){
  	
  	if(gpio_sw_get()!=0 && gpio_sw_get()<=512)
  		sw_value = gpio_sw_get();
  	
  	if(buffer != sw_value){
  	
  		buffer = sw_value;
  		
  		freq = ((190.7348633*sw_value)/10)*10;
  		
  		period = sw_value;
  		
  		pwm_set_period(period);
  	}
  	
  	display(freq);	
  }
  
  uart_finish();
}
