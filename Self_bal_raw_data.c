/*
 * GccApplication get_raw_data.c
 *
 * Created: 7/31/2019 9:58:24 PM
 * Author : SHUBHAM
 */ 

#include <avr/io.h>
void mpu6050_getRawData(int16_t *ax,int16_t *ay, int16_t *az,int16_t *gx,int16_t *gy, int16_t *gz)
{
	mpu6050_readBytes(MPU6050_RA_ACCEL_XOUT_H, 14, (uint8_t *)buffer);
	*ax = (((int16_t)buffer[0]<<8)|buffer[1]);
	*ay = (((int16_t)buffer[2]<<8)|buffer[3]);
	*az = (((int16_t)buffer[4]<<8)|buffer[5]);
	*gx = (((int16_t)buffer[6]<<8)|buffer[7]);
	*gy = (((int16_t)buffer[8]<<8)|buffer[9]);
	*gz = (((int16_t)buffer[10]<<8)|buffer[11]);
}


int main(void)
{
    /* Replace with your application co
    while (1) 
    {
    }
}

