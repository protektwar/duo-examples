#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringx.h>

#include <bmp180.h>
#include <math.h>

int bmp180_setup(int oversampling)
{
	printf("wiringXI2CSetup(%s, 0x%x)\n", BMP180_I2C_DEV, BMP180_I2C_ADDR);
	int fd_i2c = wiringXI2CSetup(BMP180_I2C_DEV, BMP180_I2C_ADDR);
	printf("fd_i2c: 0x%x\n", fd_i2c);
	if (fd_i2c < 0) {
        	printf("I2C Setup failed: 0x%x\n", fd_i2c);
		wiringXGC();
        	return -1;
	}
//	printf("bmp180_init\n");
//        bmp180_init(fd_i2c);
        printf("wiringXI2CReadReg8(0x%x, 0x%x)\n", fd_i2c, BMP180_CHIP_ID);
	int8_t chip_id = wiringXI2CReadReg8(fd_i2c, BMP180_CHIP_ID);
	if (chip_id != 0x55){
		printf("BMP180 wrong chip ID. Got %xd, expected 0x55\n", chip_id);
		return -1;
	}

	oss = oversampling;
	return fd_i2c;
}

void bmp180_init(int fd) 
{
//    const uint8_t reg_ctrl_meas_val = (oss << 6) | (0x01 << 5) | (0x00);
//    wiringXI2CWriteReg8(fd, BMP180_REG_CTRL_MEAS, reg_ctrl_meas_val);
}

void bmp180_get_calib_params(int fd, struct bmp180_calib_param* params) 
{
	if (DEBUG_BMP180 == 1) {
		printf("function bmp180_get_calib_params(0x%x, 0x%x)\n", fd, &params);
	}
	int8_t ac1_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC1_MSB);
	int8_t ac1_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC1_LSB);
        params->ac1 = (ac1_msb << 8) + ac1_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC1_MSB);
		printf("%d\n", ac1_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC1_LSB);
		printf("%d\n", ac1_lsb);
		printf("AC1: %d\n", params->ac1);
	}

	int8_t ac2_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC2_MSB);
	int8_t ac2_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC2_LSB);
        params->ac2 = (ac2_msb << 8) + ac2_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC2_MSB);
		printf("%d\n", ac2_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC2_LSB);
		printf("%d\n", ac2_lsb);
		printf("AC2: %d\n", params->ac2);
	}

	int8_t ac3_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC3_MSB);
	int8_t ac3_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC3_LSB);
        params->ac3 = (ac3_msb << 8) + ac3_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC3_MSB);
		printf("%d\n", ac3_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC3_LSB);
		printf("%d\n", ac3_lsb);
		printf("AC3: %d\n", params->ac3);
	}

	uint8_t ac4_msb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC4_MSB);
	uint8_t ac4_lsb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC4_LSB);
        params->ac4 = (ac4_msb << 8) + ac4_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC4_MSB);
		printf("%d\n", ac4_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC4_LSB);
		printf("%d\n", ac4_lsb);
		printf("AC4: %d\n", params->ac4);
	}

	uint8_t ac5_msb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC5_MSB);
	uint8_t ac5_lsb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC5_LSB);
        params->ac5 = (ac5_msb << 8) + ac5_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC5_MSB);
		printf("%d\n", ac5_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC5_LSB);
		printf("%d\n", ac5_lsb);
		printf("AC5: %d\n", params->ac5);
	}

	uint8_t ac6_msb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC6_MSB);
	uint8_t ac6_lsb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_AC6_LSB);
        params->ac6 = (ac6_msb << 8) + ac6_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC6_MSB);
		printf("%d\n", ac6_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_AC6_LSB);
		printf("%d\n", ac6_lsb);
		printf("AC6: %d\n", params->ac6);
	}

	int8_t b1_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_B1_MSB);
	int8_t b1_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_B1_LSB);
        params->b1 = (b1_msb << 8) + b1_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_B1_MSB);
		printf("%d\n", b1_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_B1_LSB);
		printf("%d\n", b1_lsb);
		printf("B1: %d\n", params->b1);
	}

	int8_t b2_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_B2_MSB);
	int8_t b2_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_B2_LSB);
        params->b2 = (b2_msb << 8) + b2_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_B2_MSB);
		printf("%d\n", b2_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_B2_LSB);
		printf("%d\n", b2_lsb);
		printf("B2: %d\n", params->b2);
	}

	int8_t mb_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_MB_MSB);
	int8_t mb_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_MB_LSB);
        params->mb = (mb_msb << 8) + mb_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_MB_MSB);
		printf("%d\n", mb_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_MB_LSB);
		printf("%d\n", mb_lsb);
		printf("MB: %d\n", params->mb);
	}

	int8_t mc_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_MC_MSB);
	int8_t mc_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_MC_LSB);
        params->mc = (mc_msb << 8) + mc_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_MC_MSB);
		printf("%d\n", mc_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_MC_LSB);
		printf("%d\n", mc_lsb);
		printf("MC: %d\n", params->mc);
	}

	int8_t md_msb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_MD_MSB);
	int8_t md_lsb = (int8_t)wiringXI2CReadReg8(fd, BMP180_REG_MD_LSB);

        params->md = (md_msb << 8) + md_lsb;
	if (DEBUG_BMP180 == 1) {
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_MD_MSB);
		printf("%d\n", md_msb);
		printf("wiringXI2CReadReg8(0x%x, 0x%X) = ", fd, BMP180_REG_MD_LSB);
		printf("%d\n", md_lsb);
		printf("MD: %d\n", params->md);
	}
}

uint16_t bmp180_get_ut(int fd)
{
	if (DEBUG_BMP180 == 1) {
		printf("bmp180_get_ut\n");
	}
	wiringXI2CWriteReg8(fd, BMP180_REG_CTRL_MEAS, BMP180_CTRL_TEMP);
        delayMicroseconds(5000);
	uint8_t out_msb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_OUT_MSB);
	uint8_t out_lsb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_OUT_LSB);
	uint16_t ut = (out_msb << 8) + out_lsb; 
	if (DEBUG_BMP180 == 1) {
		printf("out_msb: %d\n",out_msb);
		printf("out_lsb: %d\n",out_lsb);
		printf("ut: 0x%x | %d\n", ut, ut);
	}
	return ut;
}

uint32_t bmp180_get_up(int fd)
{
	if (DEBUG_BMP180 == 1) {
		printf("bmp180_get_up\n");
	}	
        wiringXI2CWriteReg8(fd, BMP180_REG_CTRL_MEAS, BMP180_CTRL_PRESSURE_0 + (oss << 6));
	if (oss == BMP180_ULTRALOWPOWER)
	   delayMicroseconds(5000);
	else if (oss == BMP180_STANDARD)
           delayMicroseconds(8000);
	else if (oss == BMP180_HIGHRES)
	   delayMicroseconds(14000);
	else
           delayMicroseconds(26000);
	uint8_t out_msb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_OUT_MSB);
	uint8_t out_lsb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_OUT_LSB);
	uint8_t out_xlsb = (uint8_t)wiringXI2CReadReg8(fd, BMP180_REG_OUT_XLSB);

	uint32_t up = ((out_msb << 16) + (out_lsb << 8) + out_xlsb) >> (8 - oss);
	if (DEBUG_BMP180 == 1) {
		printf("out_msb: %d | ", out_msb);
		printf("out_lsb: %d | ", out_lsb);
		printf("out_xlsb: %d | ", out_xlsb);
		printf("oversampling: %d\n", oss);
		printf("up: %d\n ", up);
	}
	return up;
}

int32_t bmp180_get_B5(int fd, const struct bmp180_calib_param params)
{	
	if (DEBUG_BMP180 == 1) {
  		printf("bmp180_get_B5\n");
	}

	int32_t UT = bmp180_get_ut(fd);
	if (DEBUG_BMP180 == 1) {
		printf("UT:  %u | ", UT);
		printf("AC5: %u | ", params.ac5);
		printf("AC6: %u | ", params.ac6);
		printf("MC:  %d | ", params.mc);
		printf("MD:  %d\n", params.md);
	}

	int32_t X1 = (UT - (int32_t)params.ac6) * ((int32_t)params.ac5) >> 15;
	int32_t X2 = ((int32_t)params.mc << 11) / (X1 + (int32_t)params.md);
	if (DEBUG_BMP180 == 1) {
		printf("X1:  %d | ", X1);
	  	printf("X2:  %d\n", X2);
		printf("X1 + X2:  %d\n", X1 + X2);
	}

	return X1 + X2;
}

int32_t bmp180_get_temperature(int fd, const struct bmp180_calib_param params)
{
	if (DEBUG_BMP180 == 1) {
		printf("bmp180_get_temperature\n");
	}
	int32_t B5 = bmp180_get_B5(fd, params);
	return ((B5 + 8) >> 4);
}

int32_t bmp180_get_pressure(int fd, const struct bmp180_calib_param params)
{
	if (DEBUG_BMP180 == 1) {
		printf("bmp180_get_pressure\n");
	}

        int32_t UP = bmp180_get_up(fd);
  	if (DEBUG_BMP180 == 1) {
		printf("UP: %d\n", UP);
	}

	int32_t B5 = bmp180_get_B5(fd, params);
	if (DEBUG_BMP180 == 1) {
		printf("B5: %d | ", B5);
	}

	int32_t B6 = B5 - 4000;
	if (DEBUG_BMP180 == 1) {
		printf("B6: %d\n", B6);
	}

	int32_t X1 = ((int32_t)params.b2 * ((B6 * B6) >> 12)) >> 11;
	if (DEBUG_BMP180 == 1) {
		printf("X1: %d | ", X1);
	}

	int32_t X2 = ((int32_t)params.ac2 * B6) >> 11;
	if (DEBUG_BMP180 == 1) {
		printf("X2: %d | ", X2);
	}

	int32_t X3 = X1 + X2;
	if (DEBUG_BMP180 == 1) {
		printf("X3: %d\n", X3);
	}

	int32_t B3 = ((((int32_t)params.ac1 * 4 + X3) << oss) + 2) >> 2;
	if (DEBUG_BMP180 == 1) {
		printf("B3: %d | ", B3);
	}

	X1 = ((int32_t)params.ac3 * B6) >> 13;
	if (DEBUG_BMP180 == 1) {
		printf("X1: %d | ", X1);
	}

	X2 = ((int32_t)params.b1 * ((B6 * B6) >> 12)) >> 16;
	if (DEBUG_BMP180 == 1) {
		printf("X2: %d | ", X2);
	}

	X3 = ((X1 + X2) + 2) >> 2;
	if (DEBUG_BMP180 == 1) {
		printf("X3: %d\n", X3);
	}

	uint32_t B4 = ((uint32_t)params.ac4 * (uint32_t)(X3 + 32768)) >> 15;
	if (DEBUG_BMP180 == 1) {
		printf("B4: %d | ", B4);
	}

	uint32_t B7 = ((uint32_t)UP - B3) * (uint32_t)(50000UL >> oss);
	if (DEBUG_BMP180 == 1) {
		printf("B7: %d\n ", B7);
	}
	int32_t p;
	if (B7 < 0x80000000) 
		p = (B7 * 2) / B4;
	else
		p = (B7 / B4) * 2;

	X1 = (p >> 8) * (p >> 8);
	if (DEBUG_BMP180 == 1) {
		printf("X1: %d | ", X1);
	}

	X1 = (X1 * 3038) >> 16;
	if (DEBUG_BMP180 == 1) {
		printf("X1: %d | ", X1);
	}

	X2 = (-7357 * p) >> 16;
	if (DEBUG_BMP180 == 1) {
		printf("X2: %d\n", X1);
	}
	p = p + ((X1 + X2 + 3791) >> 4) ;
  	if (DEBUG_BMP180 == 1) {
		printf("p: %d\n", p);
	}
	return p;
}
