The readme is a brief overview on gpio, i2c, uart example applications. Next Releases will includes applications of qspi, spi and pwm support.
     
### GPIO_APPLICATIONS
   - This consists of applications developed using the gpio pins.

#### Contents ####
 
* Makefile 
    - The Makefile has support for different target boards and applications.
* btnled
     - This program controls the led using  the button.
     -  src code:btnled.c
     -  Test components :led,button.
* keyboard
    - The program is all about how to get the value of a key when pressed on the board.
    -  src code:keyboard.c
    -  Test components :pmod Keypad.
* motor
     - This is the program that tests the functioning of the  stepper motor using the gpio pins.
     -  src code:motor.c
     -  Test components: stepper motor.
* rdgpio
     - This is the program that reads the inputs given by the gpio pins.
     -  src code:rdgpio.c
* tglgpio
     - This is the program that performs the toggling of led.
     -  src code:tglgpio.c
     -  Test components:led

### I2C_APPLICATIONS
- This consists of applications developed using the i2c communication protocol.

#### Contents ####

* Make file
   - The Makefile has support for different target boards and applications.
* lm75
   - The program performs the Temperature sensing using the i2c communication protocol.
   - src code:lm75.c
   - sensor used:lm75x

### UART_APPLICATIONS 
  -  This consists of applications developed using the uart protocol.

#### Contents ####

* Makefile
  -  The Makefile has support for different target boards and applications.
* hello
  - The program is used to test the uart with the help of hello world program.
  -  src code:hello.c
* uartmp3
  - The program is used to play the mp3 format song using the uart.
  -  src code:uartmp3.c
* maze
  - A configurable rat in a maze game.
  -  src code:maze.c

