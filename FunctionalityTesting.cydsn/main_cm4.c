/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "bmi160.h"
#include "time.h"

static struct bmi160_dev myBmi160;

static int8_t BMI160BurstWrite(uint8_t dev_addr, uint8_t reg_addr, uint8_t *dataw, uint16_t len)
{
    Cy_SCB_I2C_MasterSendStart(I2C_bus_HW, dev_addr, CY_SCB_I2C_WRITE_XFER, 0, &I2C_bus_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_bus_HW, reg_addr, 0, &I2C_bus_context);
    
    for(int i = 0;i<len; i++)
    {
        Cy_SCB_I2C_MasterWriteByte(I2C_bus_HW, dataw[i], 0, &I2C_bus_context);
        //printf("Write 0x%x -> 0x%x\r\n", reg_addr, dataw[i]);
    }
    Cy_SCB_I2C_MasterSendStop(I2C_bus_HW, 0, &I2C_bus_context);
    
    return 0;
}

static int8_t BMI160BurstRead(uint8_t dev_addr, uint8_t reg_addr, uint8_t *datar, uint16_t len)
{
    Cy_SCB_I2C_MasterSendStart(I2C_bus_HW, dev_addr, CY_SCB_I2C_WRITE_XFER, 0, &I2C_bus_context);
    Cy_SCB_I2C_MasterWriteByte(I2C_bus_HW, reg_addr, 0, &I2C_bus_context);
    Cy_SCB_I2C_MasterSendReStart(I2C_bus_HW, dev_addr, CY_SCB_I2C_READ_XFER, 0, &I2C_bus_context);
    
    for(int i = 0;i<len-1; i++)
    {
        Cy_SCB_I2C_MasterReadByte(I2C_bus_HW, CY_SCB_I2C_ACK, &datar[i], 0, &I2C_bus_context);
        //printf("Read 0x%x ->  0x%x\r\n", reg_addr, datar[i]);
    }
    Cy_SCB_I2C_MasterReadByte(I2C_bus_HW, CY_SCB_I2C_NAK, &datar[len-1], 0, &I2C_bus_context);
     //printf("Read 0x%x 0x%x\r\n", reg_addr, datar[len-1]);
    
    Cy_SCB_I2C_MasterSendStop(I2C_bus_HW, 0, &I2C_bus_context);
    
    return 0;
}

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    UART_bus_Start();  
    I2C_bus_Start();
    
    CyDelay(100);
    myBmi160.interface = BMI160_I2C_INTF;
    myBmi160.read = BMI160BurstRead;
    myBmi160.write = BMI160BurstWrite;
    myBmi160.delay_ms = CyDelay;
    myBmi160.id = BMI160_I2C_ADDR;
    
    bmi160_init(&myBmi160);
    
    myBmi160.gyro_cfg.odr = BMI160_GYRO_ODR_3200HZ;
    myBmi160.gyro_cfg.range = BMI160_GYRO_RANGE_2000_DPS;
    myBmi160.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;
    myBmi160.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;
    
    myBmi160.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
    myBmi160.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
    myBmi160.accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;
    myBmi160.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
    
    /* Set the sensor configuration */
    bmi160_set_sens_conf(&myBmi160);
    
    struct bmi160_sensor_data acceleration;
    struct bmi160_sensor_data gyro;
    uint8 reg_id;
    uint8 reg_data;
    float acc_x, acc_y, acc_z;
    uint32 accel_time, gyro_time;
    #define MAXACCEL (32768/2)
    time_t seconds_from_epoch;
    uint8 rlst;
    
    rlst = bmi160_get_regs(0x00, &reg_id, 1, &myBmi160);
    if (rlst != 0)
    {
        printf("Could not get ID...");
    }
    else
    {
        //printf("Printing ID: ");
        //printf("0x%x\r\n", reg_id);
        rlst = bmi160_get_regs(0x03, &reg_data, 1, &myBmi160);
        //printf("0x%x\r\n", reg_data);
    }
    
    for(;;)
    {
        bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL | BMI160_TIME_SEL), &acceleration, &gyro, &myBmi160);
    
        acc_x = (float)acceleration.x/MAXACCEL;
        acc_y = (float)acceleration.y/MAXACCEL;
        acc_z = (float)acceleration.z/MAXACCEL;
        accel_time = acceleration.sensortime;
        time(&seconds_from_epoch);
        printf("%ul    %ld    x=%1.2f y=%1.2f z=%1.2f\r\n", accel_time, seconds_from_epoch, acc_x, acc_y, acc_z);

        CyDelay(100);
    }
}

/* [] END OF FILE */
