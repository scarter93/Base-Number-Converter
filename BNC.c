#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

//converts "digit" to integer value (base 10)
#define to_number(digit) ((int)digit >= 65) ? ((int)(digit) - 55) : ((int)(digit) - 48)
//converts number to "digit" value (base 36)
#define to_char(num) num >= 10 ? (char)(num + 55) : (char)(num + 48)

char max_value[37] = "-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
*retuns number of digits required in conversion
*/
int base_digits(num, base){
   return (int)(1 + floor(log(num) / log(base)));
}
/*
* return 0 on failure, base on success
*/
int enter_base(char* base_str, int* base){
  int i;
  scanf("%s", base_str);
  for(i = 0; i < strlen(base_str); i++){
    if(!isdigit(base_str[i])){
      return 0;
    }

  }
  *(base) = atoi(base_str);
  if( *(base) == 0 || *(base) >= 37){
    return 0;
  }
  return *(base);
}
/*
* returns 0 on failure, else base on success
*/
int enter_value(char* input, int base){
  printf("Please enter a number in base %d less than 100 digits\n", base);
  scanf("%s", input);
  int i;

  for(i = 0; i < strlen(input); i++){
    input[i] = toupper(input[i]);
    if((int)(input[i]) > (int)(max_value[base])){
      return 0;
    }
  }
  return base;
}
/*
*returns number of digits or -1
*/
int convert(char* input, int base_st, int base_to, char* output){
  int value = 0;
  int i;
  for(i = strlen(input)-1; i >= 0; i--){
    if((int)(input[i]) > (int)(max_value[base_st])){
      return -1;
    }
    int pow_to = strlen(input)-1-i;
    int power_result = ceil(pow(base_st, pow_to));
    int result = to_number(input[i]);

    value += result*power_result;
  }

  int new_digits = base_digits(value, base_to);
  int check = base_to;

  while(value / check != 0){
    check *= base_to;
  }
  check = check/base_to;

  int entry = 0;
  while(entry != new_digits){
    int quo = value / check;
    int rem = value % check;
    output[entry] = to_char(quo);

    entry++;
    value = rem;
    check = check/base_to;
  }
  return new_digits;
}

void main(int argc, char** argv) {

  char base_str[10];
  int base;
  int value;
  int base_out;
  char input[100];
  char output[100];

  printf("Please enter a base to convert from (less than 37)\n");
  if(!enter_base(base_str, &base)){
    printf("%s is not a valid base...exiting\n", base_str);
    exit(-1);
  }

  if(!enter_value(input, base)){
    printf("%s is not a valid number for base %d...exiting\n", input, base);
    exit(-1);
  }

  printf("Please enter a base to convert to (less than 37)\n");
  if(!enter_base(base_str, &base_out)){
    printf("%s is not a valid base...exiting\n", base_str);
    exit(-1);
  }

  if( convert(input,base,base_out, output) == -1){
    printf("Error in conversion...exiting\n");
    exit(-1);
  }
  printf("result is %s\n", output);
}
