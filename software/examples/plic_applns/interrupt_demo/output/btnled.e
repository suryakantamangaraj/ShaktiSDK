# 1 "./interrupt_demo.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "./interrupt_demo.c"
# 23 "./interrupt_demo.c"
# 1 "/home/rise/gitlab/shakti-sdk/bsp/include/gpio.h" 1
# 34 "/home/rise/gitlab/shakti-sdk/bsp/include/gpio.h"
# 1 "/home/rise/gitlab/shakti-sdk/bsp/third_party/artix7_35t/platform.h" 1
# 35 "/home/rise/gitlab/shakti-sdk/bsp/include/gpio.h" 2
# 45 "/home/rise/gitlab/shakti-sdk/bsp/include/gpio.h"
long int read_word(int *addr);






void write_word(int *addr, unsigned long val);
# 24 "./interrupt_demo.c" 2
# 1 "/home/rise/gitlab/shakti-sdk/bsp/include/uart.h" 1
# 32 "/home/rise/gitlab/shakti-sdk/bsp/include/uart.h"
# 1 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdint.h" 1 3 4
# 9 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdint.h" 3 4
# 1 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 1 3 4
# 12 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 3 4
# 1 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 1 3 4







# 1 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/features.h" 1 3 4
# 28 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/features.h" 3 4
# 1 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/_newlib_version.h" 1 3 4
# 29 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/features.h" 2 3 4
# 9 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 2 3 4
# 41 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4

# 41 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef signed char __int8_t;

typedef unsigned char __uint8_t;
# 55 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef short int __int16_t;

typedef short unsigned int __uint16_t;
# 77 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef long int __int32_t;

typedef long unsigned int __uint32_t;
# 103 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef long long int __int64_t;

typedef long long unsigned int __uint64_t;
# 134 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef signed char __int_least8_t;

typedef unsigned char __uint_least8_t;
# 160 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef short int __int_least16_t;

typedef short unsigned int __uint_least16_t;
# 182 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef long int __int_least32_t;

typedef long unsigned int __uint_least32_t;
# 200 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef long long int __int_least64_t;

typedef long long unsigned int __uint_least64_t;
# 214 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/machine/_default_types.h" 3 4
typedef long long int __intmax_t;







typedef long long unsigned int __uintmax_t;







typedef int __intptr_t;

typedef unsigned int __uintptr_t;
# 13 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 2 3 4
# 1 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/_intsup.h" 1 3 4
# 35 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
# 187 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
# 14 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 2 3 4
# 1 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/_stdint.h" 1 3 4
# 20 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/sys/_stdint.h" 3 4
typedef __int8_t int8_t ;



typedef __uint8_t uint8_t ;







typedef __int16_t int16_t ;



typedef __uint16_t uint16_t ;







typedef __int32_t int32_t ;



typedef __uint32_t uint32_t ;







typedef __int64_t int64_t ;



typedef __uint64_t uint64_t ;






typedef __intmax_t intmax_t;




typedef __uintmax_t uintmax_t;




typedef __intptr_t intptr_t;




typedef __uintptr_t uintptr_t;
# 15 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 2 3 4






typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;




typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;




typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;




typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
# 51 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 3 4
  typedef int int_fast8_t;
  typedef unsigned int uint_fast8_t;
# 61 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 3 4
  typedef int int_fast16_t;
  typedef unsigned int uint_fast16_t;
# 71 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 3 4
  typedef int int_fast32_t;
  typedef unsigned int uint_fast32_t;
# 81 "/home/rise/gitlab/tools/riscv32-unknown-elf/include/stdint.h" 3 4
  typedef long long int int_fast64_t;
  typedef long long unsigned int uint_fast64_t;
# 10 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdint.h" 2 3 4
# 33 "/home/rise/gitlab/shakti-sdk/bsp/include/uart.h" 2




# 36 "/home/rise/gitlab/shakti-sdk/bsp/include/uart.h"
typedef struct
{
 unsigned short baud;
 unsigned short reserv0;
 unsigned int tx_reg;
 unsigned int rcv_reg;
 unsigned char status;
 unsigned char reserv1;
 unsigned short reserv2;
 unsigned short delay;
 unsigned short reserv3;
 unsigned short control;
 unsigned short reserv5;
 unsigned char ien;
 unsigned char reserv6;
 unsigned short reserv7;
 unsigned char iqcycles;
 unsigned char reserv8;
 unsigned short reserv9;





} uart_struct;
# 92 "/home/rise/gitlab/shakti-sdk/bsp/include/uart.h"
extern uart_struct *uart_instance[3];
extern unsigned char uart0_complete;
extern unsigned char uart1_complete;
extern unsigned char uart2_complete;
extern unsigned int uart0_tx_isr_count ;
extern unsigned int uart0_rcv_isr_count ;
extern unsigned int uart1_tx_isr_count ;
extern unsigned int uart1_rcv_isr_count ;
extern unsigned int uart2_tx_isr_count ;
extern unsigned int uart2_rcv_isr_count ;
extern unsigned char u0_rcv_char[10000];
extern unsigned char u1_rcv_char[10000];
extern unsigned char u2_rcv_char[10000];

void uart_init();
void set_baud_rate(uart_struct * uart_instance, unsigned int baudrate);
void enable_uart_interrupts(uart_struct * uart_instance, unsigned char interrupt);
void set_uart_rx_threshold(uart_struct * uart_instance, unsigned char rxthreshold);
uint32_t write_uart_character(uart_struct * uart_instance, uint8_t prn_character);
uint32_t write_uart_string(uart_struct * uart_instance, uint8_t * ptr_string);
uint8_t read_uart_character(uart_struct * uart_instance, char * prn_character);
uint8_t read_uart_string(uart_struct * uart_instance, char * ptr_string) ;
unsigned char uart0_isr();
unsigned char uart1_isr();
unsigned char uart2_isr();
# 25 "./interrupt_demo.c" 2
# 1 "/home/rise/gitlab/shakti-sdk/bsp/include/traps.h" 1
# 125 "/home/rise/gitlab/shakti-sdk/bsp/include/traps.h"
typedef void (*mtrap_fptr_t) (uintptr_t trap_cause, uintptr_t epc);

mtrap_fptr_t mcause_trap_table[16];

mtrap_fptr_t mcause_interrupt_table[16];


void default_handler(uintptr_t cause, uintptr_t epc);

unsigned int extract_ie_code(unsigned int num);

uintptr_t handle_trap(uintptr_t cause, uintptr_t epc);
# 26 "./interrupt_demo.c" 2

# 1 "/home/rise/gitlab/shakti-sdk/bsp/drivers/plic/plic_driver.h" 1
# 70 "/home/rise/gitlab/shakti-sdk/bsp/drivers/plic/plic_driver.h"
typedef enum
{
 INACTIVE = 0,
 ACTIVE = 1,
 SERVICED = 2,
 MASKED
}interrupt_status_e;





typedef struct
{
 unsigned int id;
 unsigned int priority;
 interrupt_status_e state;
 unsigned int count;
} interrupt_data_t;






typedef void (*plic_fptr_t) (unsigned int);
plic_fptr_t isr_table[28];
# 108 "/home/rise/gitlab/shakti-sdk/bsp/drivers/plic/plic_driver.h"
void mach_plic_handler(uintptr_t int_id, uintptr_t epc);

void configure_interrupt_pin(unsigned int pin);

void configure_interrupt(unsigned int int_id);
# 28 "./interrupt_demo.c" 2
# 1 "/home/rise/gitlab/shakti-sdk/bsp/include/log.h" 1
# 30 "/home/rise/gitlab/shakti-sdk/bsp/include/log.h"
# 1 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdarg.h" 1 3 4
# 40 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdarg.h" 3 4

# 40 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 99 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 31 "/home/rise/gitlab/shakti-sdk/bsp/include/log.h" 2
# 40 "/home/rise/gitlab/shakti-sdk/bsp/include/log.h"

# 40 "/home/rise/gitlab/shakti-sdk/bsp/include/log.h"
extern void vprintfmt(void (*putch)(int, void**), void **putdat, const char *fmt, va_list ap);


void log_trace(const char*fmt, ...);
void log_info(const char*fmt, ...);
void log_debug(const char*fmt, ...);
void log_warn(const char*fmt, ...);
void log_error(const char*fmt, ...);
void log_fatal(const char*fmt, ...);
# 29 "./interrupt_demo.c" 2
# 1 "/home/rise/gitlab/shakti-sdk/bsp/include/defines.h" 1
# 30 "./interrupt_demo.c" 2
# 1 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h" 1
# 24 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h"
# 1 "/home/rise/gitlab/tools/lib/gcc/riscv32-unknown-elf/8.2.0/include/stdbool.h" 1 3 4
# 25 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h" 2
# 51 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h"
void pwm_configure(int module_number, int clock_divisor, int period, int duty, 
# 51 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h" 3 4
                                                                              _Bool 
# 51 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h"
                                                                                   external_clock);
void pwm_start(int module_number, int mode);
int pwm_check_continuous_mode(int module_number);
void pwm_clear_registers(int module_number);
void pwm_init();
void pwm_set_external_clock(int module_number, 
# 56 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h" 3 4
                                              _Bool 
# 56 "/home/rise/gitlab/shakti-sdk/bsp/include/pwm_driver.h"
                                                   value);
void pwm_set_clock(int module_number, int clock_divisor);
void pwm_set_duty_cycle(int module_number, int duty);
void pwm_set_periodic_cycle(int module_number, int period);
void pwm_stop(int module_number);
void show_register_values(int module_number);
int set_pwm_period_register(int module_number, int value);
int set_pwm_duty_register(int module_number, int value);
int set_pwm_control_register(int module_number, int value);
int set_pwm_clock_register(int module_number, int value);
int configure_control_register_mode(int mode);
# 31 "./interrupt_demo.c" 2
# 39 "./interrupt_demo.c"
void dump_word_memory(unsigned int* start, unsigned int word_length)
{
 unsigned int i=0;
 void *address;

 address = (unsigned int *) start;

 while(i++< word_length)
 {
  log_info("address = %x data = %x\n", address, *(unsigned int *) address);
  address+=4;
 }
}
# 60 "./interrupt_demo.c"
void dump_byte_memory(unsigned int* start, unsigned int word_length)
{
 unsigned int i=0;
 void *address;

 address = (unsigned char *) start;

 while(i++< word_length)
 {
  log_info("address = %x data = %x\n", address, *(unsigned char
              *) address);
  address+=1;
 }
}
# 82 "./interrupt_demo.c"
unsigned handle_button_press (unsigned num)
{
 log_info("button pressed\n");
 return 0;
}
# 95 "./interrupt_demo.c"
int main(void){
 unsigned int int_id = 1;
 register uint32_t retval;
 int i;

 isr_table[1] = handle_button_press;

 dump_word_memory(0x0c000000, 24);
 dump_byte_memory(0x0c001000, 4);
 dump_byte_memory(0x0c002000, 4);
 read_word(0x0c010000);
 read_word(0x0c010010);

 plic_init();



 for(int i=1;i<25;i++)
  configure_interrupt(i);

 dump_word_memory(0x0c000000, 24);
 dump_byte_memory(0x0c001000, 4);
 dump_byte_memory(0x0c002000, 4);
 read_word(0x0c010000);
 read_word(0x0c010010);



 asm volatile("li      t0, 8\t\n"
       "csrrs   zero, mstatus, t0\t\n"
      );

 asm volatile("li      t0, 0x800\t\n"
       "csrrs   zero, mie, t0\t\n"
      );

 asm volatile(
       "csrr %[retval], mstatus\n"
       :
       [retval]
       "=r"
       (retval)
      );

 printf(" retval = %x\n", retval);

 asm volatile(
       "csrr %[retval], mie\n"
       :
       [retval]
       "=r"
       (retval)
      );

 printf(" retval = %x\n", retval);

 asm volatile(
       "csrr %[retval], mip\n"
       :
       [retval]
       "=r"
       (retval)
      );

 printf(" retval = %x\n", retval);

 while(1){
  asm volatile(
        "csrr %[retval], mip\n"
        :
        [retval]
        "=r"
        (retval)
       );

  i++;

  if((i%10000000) == 0){
   printf(" retval = %x\n", retval);
   dump_word_memory(0x0c000000, 24);
   dump_byte_memory(0x0c001000, 4);
   dump_byte_memory(0x0c002000, 4);
   read_word(0x0c010000);
   read_word(0x0c010010);
  }

 }

 return 0;
}
