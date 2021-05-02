/*
 * Copyright (c) 2018 Kiril Zyapkov
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/gpio.h>

#include <soc.h>

int cjmcu8332_pinmux_init(const struct device *dev)
{
#ifdef CONFIG_LIS3DH
	struct device *gpio = device_get_binding(LIS3DH_GPIO_PORT);

	/* when using the I2C, CS must be tied high. */
	gpio_pin_configure(gpio, LIS3DH_CS_GPIO_PIN, GPIO_DIR_OUT);
	gpio_pin_write(gpio, LIS3DH_CS_GPIO_PIN, 1);

	/* SA0 has pullup enabled by default so it's better to keep it high,
	   this sets the sensor address 0x19 */
	gpio_pin_configure(gpio, LIS3DH_SA0_GPIO_PIN, GPIO_DIR_OUT);
	gpio_pin_write(gpio, LIS3DH_SA0_GPIO_PIN, 1);
#endif /* CONFIG_LIS3DH */

	return 0;

}

SYS_INIT(cjmcu8332_pinmux_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
