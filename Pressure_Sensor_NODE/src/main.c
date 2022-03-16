/*
Copyright (c) 2022 VAT

This application is reading pressure and operating temperature of a chip and sending it over CANFD
*/

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/can.h>
#include <drivers/gpio.h>
#define CAN_SILENT_PORT "PORTB"
#define CAN_SILENT_PIN  4
#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>


#define AG413_I2C_ADDR 0x38


const struct device *can_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_canbus));


void main(void)
{
	//const struct device *can_silent_port = device_get_binding(CAN_SILENT_PORT);
	struct can_timing timing, dtiming, timingpre;

	//gpio_pin_configure(can_silent_port, CAN_SILENT_PIN, GPIO_OUTPUT);

	//gpio_pin_set(can_silent_port, CAN_SILENT_PIN, GPIO_ACTIVE_LOW);
	const struct device *i2c_dev = DEVICE_DT_GET(DT_ALIAS(i2c_0));
	//uint8_t cmp_data[16];
	uint8_t data[16];
	uint16_t ret;
	float alpha = 7373 / 500;
	float beta = 819;
	float error = 221;

	if (!device_is_ready(i2c_dev)) {
		printk("I2C: Device is not ready.\n");
		return;
	}

	if (!device_is_ready(can_dev)) {
		printk("CAN: Device %s not ready.\n", can_dev->name);
		return;
	}

	can_set_mode(can_dev, CAN_NORMAL_MODE);

    uint32_t rate =0;

	
	can_calc_timing(can_dev, &timing, 250000, 800);
	can_calc_timing(can_dev, &dtiming,4000000, 800);
	
		
	can_get_core_clock(can_dev, &rate);
	printk("CAN clock %d \n", rate);

   

	while (1) {

		ret = i2c_read(
			i2c_dev, &data[0],
			4, AG413_I2C_ADDR); //second parameter is address of data where we want to read 2 bytes


		uint16_t pressure_data = ((data[0] & 0x3f) << 8) | data[1]; // &0x3f this is 16 bits, last two bits are zero(status bits)

		uint16_t temperature_data = ((data[2] << 8) | data[3]) >> 5;

		//printk("Pressure raw data: %d Temperature raw data: %d \n", pressure_data, temperature_data);

		k_sleep(K_MSEC(100));

		/* Temperature error multiplier is  1 for 0 to 85 degree celsius */
		
		volatile float temperature_C = (200.0 / 2047.0) * (float)temperature_data - 50.0;
		volatile float pressure_kpa = ((float)pressure_data - beta -(error*0)) / alpha;

		
		//printk("Pressure: %d kPa Operating temperature: %d C\r", (int)pressure_kpa, (int)temperature_C);
		printk("%d\n",(int)pressure_kpa);
		printk("%d\n",(int)temperature_C);
		

		struct can_pressure_frame_t {
		uint64_t length;
		uint32_t timestamp;
		//uint32_t num_beforepressure;
		uint32_t pressure;
		uint16_t temperature;
		};
		
		

		uint32_t time   = k_cycle_get_32();
		uint64_t length_of_dataframe=8;
		printk("%d\n",(uint32_t)time);
		k_sleep(K_MSEC(100));

		struct can_pressure_frame_t Pressure_data = { .length=length_of_dataframe,
		.timestamp=time,
		//.num_beforepressure=pressure_2nums,
		.pressure= pressure_kpa,
		.temperature=temperature_C};
		
		struct zcan_frame frame_data = {
		.fd=true,
        .id_type = CAN_STANDARD_IDENTIFIER,
        .rtr = CAN_DATAFRAME,
        .id = 0x123,
        .dlc = 8,
		/*.data[0]={Pressure_data.length},
		.data[4]={Pressure_data.timestamp},
		.data[5]={Pressure_data.num_beforepressure},
		.data[6]={Pressure_data.pressure},
		.data[7]={Pressure_data.temperature}
		*/
		};
		memcpy(&frame_data.data[0], &Pressure_data.length, sizeof(struct can_pressure_frame_t ));
		memcpy(&frame_data.data[1], &Pressure_data.timestamp, sizeof(struct can_pressure_frame_t ));
		memcpy(&frame_data.data[5], &Pressure_data.pressure, sizeof(struct can_pressure_frame_t ));
		memcpy(&frame_data.data[7], &Pressure_data.temperature, sizeof(struct can_pressure_frame_t ));



		
		can_send(can_dev,&frame_data,K_FOREVER,NULL,NULL);	
	
		k_msleep(1);	
	
	}
}


