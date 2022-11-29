#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "printf.h"

#define ITERATIONS 20 
#define MAX_STR_SIZE 200

char send_string[200];

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

  int numbers_int[ITERATIONS];
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats 
  generate_fibonacci_nums(numbers_int, ITERATIONS);

  generate_string(numbers_int,send_string, ITERATIONS); 
   
  printf("%s\n", send_string);

  //test file send
  char *sendfile = malloc(1000);
  int send_file_size = 0;
  send_file_size = string_copy(sendfile, send_string);
  uart_sendfile("Sendfile.txt", send_file_size, sendfile);

  //test file receive
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

  uart_finish();
}
