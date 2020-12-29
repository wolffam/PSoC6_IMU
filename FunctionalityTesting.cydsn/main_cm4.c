#include "project.h"
#include "stdio.h"
#include <stdlib.h> 
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
    RTC_Start();
    
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
    float acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
    uint32 sensor_time;
    #define MAXACCEL (32768/2)     // +/- 2G max
    #define MAXROTATE (32768/2000) // Degrees per second

    uint8 ret;
    ret = Cy_RTC_Init(&RTC_config);
    if (ret != CY_RTC_SUCCESS)
        printf("Failed to init date and time config");
    cy_stc_rtc_config_t dateTime;
    
    
    for(;;)
    {   
        RTC_GetDateAndTime(&dateTime);
        printf("%02u/%02u/%02u",(uint16_t) dateTime.date, 
                (uint16_t) dateTime.month, (uint16_t) dateTime.year);
        printf(" %02u:%02u:%02u", (uint16_t) dateTime.hour, 
                (uint16_t) dateTime.min, (uint16_t) dateTime.sec);
        
        bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL | BMI160_TIME_SEL), &acceleration, &gyro, &myBmi160);
        
        acc_x = (float)acceleration.x/MAXACCEL;
        acc_y = (float)acceleration.y/MAXACCEL;
        acc_z = (float)acceleration.z/MAXACCEL;
        
        gyro_x = (float)gyro.x/MAXROTATE;
        gyro_y = (float)gyro.y/MAXROTATE;
        gyro_z = (float)gyro.z/MAXROTATE;
        
        sensor_time = acceleration.sensortime;
       
        //printf("    %ul    x=%1.2f y=%1.2f z=%1.2f\r\n\r\n", sensor_time, acc_x, acc_y, acc_z);
        printf("    %ul    x=%1.2f y=%1.2f z=%1.2f\r\n\r\n", sensor_time, gyro_x, gyro_y, gyro_z);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
