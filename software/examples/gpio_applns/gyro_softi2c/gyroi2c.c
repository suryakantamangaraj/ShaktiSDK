#include<stdint.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gpio_i2c.h"
#include"MPU6050.h"


#define I2C_WRITE 0
#define I2C_READ 1
#define DEBUG
#define MPU6050_SLAVE_ADDRESS 0xD0
#define MPU_6050_OUTPUT_BEGIN 0x3B
#define MPU6050_DLPF_CFG 0x20
#define MPU6050_SMPL_DIV 0x19
#define PI 3.141592654
char readbuf[20];
int AccX,AccY,AccZ;
int accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
int roll, pitch, yaw;
int AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
int AccErrorX,AccErrory;
int GyroX, GyroY, GyroZ;
int c = 0;
int i=0;
unsigned char delay = 100;
//int I2c_Read_byte(unsigned char ,unsigned char );

void measuring_value()
{
// read accelerometer data
   I2cSendSlaveAddress(MPU6050_SLAVE_ADDRESS, I2C_WRITE, delay);//selecting slave to be read
   I2cWriteData(MPU_6050_OUTPUT_BEGIN, delay);//selecting register to be read
   I2cSendSlaveAddress(MPU6050_SLAVE_ADDRESS, I2C_READ, delay);
   I2c_shakti_readbytes(readbuf,14,1, delay);//to read the output values
  printf("helloworld inside measuring value\n");

   AccX = (readbuf[0]<<8 |readbuf[1]) / 4096; //16-bit X-axis data
   AccY = (readbuf[2]<<8 |readbuf[3]) / 4096; //16-bit Y-axis data
   AccZ = (readbuf[4]<<8 |readbuf[5]) / 4096; //16-bit Z-axis data

   GyroX = (readbuf[8]<<8 |readbuf[9]) /65.5 ; //
   GyroY = (readbuf[10]<<8 |readbuf[11]) / 65.5; //
   GyroZ = (readbuf[12]<<8 |readbuf[13]) / 65.5;

// Correct the outputs with the calculated error values
     GyroX = GyroX + GyroErrorX ; // GyroErrorX
     GyroY = GyroY - GyroErrorY; // GyroErrorY
     GyroZ = GyroZ + GyroErrorZ; // GyroErrorZ
}

int main()
{
printf("MPU6050\n");
 I2cInit();//configuring data and clocks as output lines
   //VERIFYING DEVICE IDENTITY BY CHECKING "WHO AM I REGISTER"
printf("MPU6050 i2c Init completed\n");
	if(WHO_AM_I_DATA == I2c_Read_byte(MPU6050_SLAVE_ADDRESS,MPU6050_REG_WHO_AM_I, delay) )
   {
	printf("WHO AM I REGISTER SUCCESFULLY VERIFIED");
   }
   else
  {
	printf("something went wrong , device identity not verified");
  }
   //configuring power management register/
   //RESETTING MPU6050 USING POWER NANAGEMENT REGISTER
    I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_PWR_MGMT_1, MPU6050_RESET, delay);

    DelayLoop(1000,1000);   // we can use waitfor() function also (delay time to reset the device and initialisations proper)

  //setting internal clock of MPU6050
    I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_PWR_MGMT_1, MPU6050_CLK_8MHz, delay);

  // configuring accelerometer -set sensitivity scale factorMPU6050_SLAVE_ADDRESS to +-8g
    I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_ACCEL_CONFIG, ACC_SENS_8g, delay);

  // configuring gyroscope-set  sensitivity scale factor to +-500deg/sec
    I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_GYRO_CONFIG,GYRO_SENS_500, delay);
  // configuirng gyroscope output rate as 1khz
    I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_DLPF_CFG,0x01, delay);
  // configuring sample divider to 99(i.e sample rate= gyroscope output rate /(1+sample divider))
    I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_SMPL_DIV, 0x63, delay);//set sample rate to 10
   while(1)
  {
   measuring_value();

   printf("AccErrorX: %d,AccErrMPU6050_SLAVE_ADDRESSorX");
   printf("AccErrorY: %d,AccErrorY");
   printf("GyroErrorX: %d,GyroErrorX");
   printf("GyroErrorY: %d,GyroErrorY");
   printf("GyroErrorZ %d,GyroErrorZ");

   }
 return 0;
}

void calculate_imu_error()
{
   int c=0;
   int yaw;
   float accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
   while(c<200)
 {
   measuring_value();

   AccErrorX = AccErrorX + (atan(AccY / sqrt(pow(AccX, 2)) + pow(AccZ, 2)))* 180 / PI;
   AccErrorY = AccErrorY + (atan(AccY / sqrt(pow(AccX, 2)) + pow(AccZ, 2)))* 180 / PI;

    GyroErrorX = GyroErrorX + (GyroX / 65.5);
    GyroErrorY = GyroErrorY + (GyroY / 65.5);
    GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
    c++;
 }
   c=0;
   AccErrorX = AccErrorX / 200;
   AccErrorY = AccErrorY / 200;

  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
  // sum all reading
    GyroErrorX = GyroErrorX / 200;
    GyroErrorY = GyroErrorY / 200;
    GyroErrorZ = GyroErrorZ / 200;

    GyroX = GyroX - GyroErrorX ; // GyroErrorX
    GyroY = GyroY - GyroErrorY; // GyroErrorY
    GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}
