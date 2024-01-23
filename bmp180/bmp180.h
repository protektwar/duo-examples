#ifndef _BMP180_H_
#define _BMP180_H_

#define DEBUG_BMP180 0
#define BMP180_I2C_DEV "/dev/i2c-1"

#define BMP180_I2C_ADDR  0x77

// hardware registers
#define BMP180_REG_CTRL_MEAS  0xF4
#define BMP180_REG_SOFT_RESET 0xE0
#define BMP180_CHIP_ID        0xD0
#define BMP180_READ  1
#define BMP180_WRITE 0
#define BMP180_READ_ADDR  0xEF
#define BMP180_WRITE_ADDR 0xEE
#define BMP180_ULTRALOWPOWER 0 // 00b 1x read | Ultra low power mode
#define BMP180_STANDARD      1 // 01b 2x read | Standard mode
#define BMP180_HIGHRES       2 // 10b 4x read | High-res mode
#define BMP180_ULTRAHIGHRES  3 // 11b 8x read | Ultra high-res mode

#define BMP180_CTRL_TEMP        0x2E
#define BMP180_CTRL_PRESSURE_0  0x34
#define BMP180_CTRL_PRESSURE_1  0x74
#define BMP180_CTRL_PRESSURE_2  0xB4
#define BMP180_CTRL_PRESSURE_3  0xF4

#define BMP180_REG_OUT_XLSB 0xF8
#define BMP180_REG_OUT_LSB  0xF7
#define BMP180_REG_OUT_MSB  0xF6

// calibration registers
#define BMP180_REG_AC1_MSB 0xAA
#define BMP180_REG_AC1_LSB 0xAB
#define BMP180_REG_AC2_MSB 0xAC
#define BMP180_REG_AC2_LSB 0xAD
#define BMP180_REG_AC3_MSB 0xAE
#define BMP180_REG_AC3_LSB 0xAF
#define BMP180_REG_AC4_MSB 0xB0
#define BMP180_REG_AC4_LSB 0xB1
#define BMP180_REG_AC5_MSB 0xB2
#define BMP180_REG_AC5_LSB 0xB3
#define BMP180_REG_AC6_MSB 0xB4
#define BMP180_REG_AC6_LSB 0xB5
#define BMP180_REG_B1_MSB  0xB6
#define BMP180_REG_B1_LSB  0xB7
#define BMP180_REG_B2_MSB  0xB8
#define BMP180_REG_B2_LSB  0xB9
#define BMP180_REG_MB_MSB  0xBA
#define BMP180_REG_MB_LSB  0xBB
#define BMP180_REG_MC_MSB  0xBC
#define BMP180_REG_MC_LSB  0xBD
#define BMP180_REG_MD_MSB  0xBE
#define BMP180_REG_MD_LSB  0xBF


static int oss;
/*
* Immutable calibration data read from bmp180
*/
struct bmp180_calib_param {
    int16_t ac1;
    int16_t ac2;
    int16_t ac3;
    uint16_t ac4;
    uint16_t ac5;
    uint16_t ac6;
    int16_t b1;
    int16_t b2;
    int16_t mb;
    int16_t mc;
    int16_t md;
};

int bmp180_setup(int oversampling);
void bmp180_init(int fd);
void bmp180_get_calib_params(int fd, struct bmp180_calib_param* params); 
uint16_t bmp180_get_ut(int fd);
uint32_t bmp180_get_up(int fd);
int32_t bmp180_get_B5(int fd, const struct bmp180_calib_param params);
int32_t bmp180_get_temperature(int fd, const struct bmp180_calib_param params);
int32_t bmp180_get_pressure(int fd, const struct bmp180_calib_param params);

#endif
