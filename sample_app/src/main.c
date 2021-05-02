/*
 * Copyright (c) 2018 Kiril Zyapkov
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <init.h>
#include <stdio.h>

#include <drivers/gpio.h>
#include <drivers/sensor.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

void accel_readout(const struct device *acc)
{
	int err;
	if (acc == NULL) return;
	struct sensor_value accel[3];
	err = sensor_sample_fetch(acc);
	if (err) {
		LOG_WRN("the sensor crapped: %d", err);
		return;
	}
	err = sensor_channel_get(acc, SENSOR_CHAN_ACCEL_XYZ, accel);
	if (err) {
		LOG_WRN("data is crap: %d", err);
		return;
	}
	/* Print accel x,y,z and mag x,y,z data */
	printf("\rAX=%10.6f AY=%10.6f AZ=%10.6f",
		sensor_value_to_double(&accel[0]),
		sensor_value_to_double(&accel[1]),
		sensor_value_to_double(&accel[2]));
}

void main(void)
{
	LOG_INF("Hello CJMCU-8332!");

	const struct device *acc;

	// acc = device_get_binding("LIS3DH");
	// acc = device_get_binding(DT_LABEL(DT_INST(0, st_lis3dh)));
	acc = DEVICE_DT_GET(DT_INST(0, st_lis3dh));

	if (acc == NULL) {
		LOG_ERR("NO ACC DEVICE!");
		return;
	}
	LOG_INF("temp device is %p, name is %s", acc, acc->name);

	while (true) {
		accel_readout(acc);
		k_msleep(20);
	}
}
