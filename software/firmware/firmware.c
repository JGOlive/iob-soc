#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "iob-gpio.h"
#include "printf.h"
#include "iob-timer.h"

unsigned int pwm_timepoint_array[4] =  {50, 100, 50, 0};
unsigned int pwn_ton[10];
unsigned int freq = 1000, freq_buffer, period, t_total;
int numero_de_pontos_t_on = 4 , i;
unsigned long long k, l;
void pwm_gen()
{
  i = 0;
  while(i < numero_de_pontos_t_on)
    {
      //timer_reset();
      gpio_set(1);
      //while(timer_get_count() <= pwn_ton[i]);
      //k = timer_get_count(); 
      //printf("Ton[%d]: %d -> %lld timercount\n", i, pwn_ton[i], k);
      gpio_set(0);
      //while(timer_get_count() <= t_total);
      //l = timer_get_count();
      //printf("Toff[%d]: %d -> %lld timercount\n", i, (t_total - pwn_ton[i]), (l-k));
      i++;
    }
  return;
}

int main()  
{
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);
  
  //init gpio
  gpio_init(GPIO_BASE);

  //init timer
  timer_init(TIMER_BASE);
  
  //test puts
  uart_puts("\n\n\nHello world!\n");

  //set gpio and read
  gpio_set_output_enable(3);
  gpio_set(3);
  gpio_get();

  //ler_interruptor; codigo por fazer
  uint32_t recorrencia_da_leitura = 100, j = 0, k, l;
  //freq = gpio_get();
  freq_buffer = freq;
  period = 1000000/freq; // exemplo: frequencia = 1kHz -> periodo = 1 ms. Vamos fazer a sinosoide com 10 pontos, logo o t_total = periodo/10 = 0.1 ms = 100 us.
  t_total = period/10;
  printf("frequencia: %d, periodo: %d, t_total: %d\n", freq, period, t_total);
  for (j = 0; j < numero_de_pontos_t_on; j++)
    {
      pwn_ton[j] = ((t_total * pwm_timepoint_array[j])/100);
      printf("ton[%d] = %d\n", j, pwn_ton[j]);
    }
       
  //Entrar no loop infinito de dor e tortura sonora
  printf("inicio pwm \n");
  j = 0;
  while(j<=0)
    {
      if(j == recorrencia_da_leitura){
	//freq = gpio_get();
	//i = 0;
	if (freq != freq_buffer){
	  freq_buffer = freq;
	  period = (1*1000000)/freq;
	  t_total = period/10;
	}
      }
      pwm_gen();
      j++;
    }

  printf("fim do programa \n");

  uart_finish();
}








/*int fibonacci[100];
char charfibonacci[100];
char send_string[200]= "Sending this string as a file to console.\n"
                    "The file is then requested back from console.\n"
                    "The sent file is compared to the received file to confirm " 
                    "correct file transfer via UART using console.\n"
                    "Generating the file in the firmware creates an uniform "
                    "file transfer between pc-emul, simulation and fpga without"
                    " adding extra targets for file generation.\n";

void calculate_fibonacci_sequence(int n){
  fibonacci[0] = 0;
  int x = 0, y = 1, z = 0;
  for(int i = 1; i < n; i++){
    x = y;
    y = z;
    z = x + y;
    fibonacci[i] = z;
  }
  int i=0;
  int index = 0;
  for (i=0; i<n; i++)
   index += snprintf(&charfibonacci[index], 128-index, "%d, ", fibonacci[i]);
  return;
}
// copy src to dst
// return number of copied chars (excluding '\0')
int string_copy(char *dst, char *src) {
    if (dst == NULL || src == NULL) {
        return -1;
    }
    int cnt = 0;
    while(src[cnt] != 0){
        dst[cnt] = src[cnt];
        cnt++;
    }
    dst[cnt] = '\0';
    return cnt;
}

// 0: same string
// otherwise: different
int compare_str(char *str1, char *str2, int str_size) {
    int c = 0;
    while(c < str_size) {
        if (str1[c] != str2[c]){
            return str1[c] - str2[c];
        }
        c++;
    }
    return 0;
<<<<<<< HEAD
}

void generate_fibonacci_nums(int *number_array, int iter)
{
    int i;

    number_array[0] = 0;
    number_array[1] = 1;

    for (i = 2; i < iter; i++){
    number_array[i] = number_array[i-1] + number_array[i-2];
    }

return;
}

void generate_string(int *numbers, char* total_string, int iter){

    int i,decimal,n_numbers, str_idw = 20, num_test;
    char *number_string[10];
    char test_string[MAX_STR_SIZE] = "Fibonacci sequence:\n"; /*20 + \0*/
    char *space =" "; 
    
    for(i = 0; i< ITERATIONS; i++){
        decimal = 1;
        n_numbers = 0;
        while(numbers[i]/decimal >= 10){
            decimal = decimal*10;
            n_numbers = 1 + n_numbers;
        }
        num_test = numbers[i];
        while (n_numbers >= 0){
            test_string[str_idw] = '0'+ num_test/decimal;
            num_test = num_test % decimal;
            decimal = decimal/10;
            str_idw = str_idw + 1;
            n_numbers = n_numbers - 1;
        }
        test_string[str_idw] = ' ';
        str_idw = str_idw + 1;
    }
    test_string[str_idw] = '\n';
    test_string[str_idw + 1] = '\0';

    string_copy(total_string,test_string);
    return;
}

int main()
{
  uint32_t gpio_input;
  int numbers_int[ITERATIONS];
  // proj var
  uint32_t freq_ad = 32768;
  uint32_t freq_selectors, p_freq_selectors;
  uint32_t pwm_t;

  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  //init gpio
  gpio_init(GPIO_BASE);

  gpio_set_output_enable(7);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats 
  generate_fibonacci_nums(numbers_int, ITERATIONS);

  generate_string(numbers_int,send_string, ITERATIONS); 
   
  printf("%s\n", send_string);

  // project stuff
  //

  freq_selectors = freq_selectors && 0x0000FFFF;

  if(freq_selectors != p_freq_selectors){
    pwm_t = freq_ad/freq_selectors;
    

    p_freq_selectors = freq_selectors;
  }

  //gpio stuff
  gpio_input = gpio_get();
  gpio_set(2);

  printf("GPIO message: %d\n",gpio_input);
=======
}*/
>>>>>>> 9ca070596dbb4289776a059ab31e4a2c8985dd2a

  /*//test the first 100 numbers of febonacci sequence  
  calculate_fibonacci_sequence(20);
  printf("\n\n\n fibonacci sequence: %s\n\n\n", charfibonacci);  
  
  //test file send
  char *sendfile = malloc(1000);
  int send_file_size = 0;
  send_file_size = string_copy(sendfile, charfibonacci);
  uart_sendfile("Sendfile.txt", send_file_size, sendfile);

  test file receive
  char *recvfile = malloc(10000);
  int file_size = 0;
  file_size = uart_recvfile("Sendfile.txt", recvfile);

  //compare files
  if (compare_str(sendfile, recvfile, send_file_size)) {
      printf("FAILURE: Send and received file differ!\n");
  } else {
      printf("SUCCESS: Send and received file match!\n");
  }

  free(sendfile);
  free(recvfile);
*/
