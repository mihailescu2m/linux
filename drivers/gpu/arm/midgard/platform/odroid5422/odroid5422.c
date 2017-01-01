/*
 * Copyright (C) 2017 Hardkernel Co.Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <mali_kbase.h>
#include <mali_kbase_defs.h>
#include <mali_kbase_config.h>
#include <linux/pm_runtime.h>
#include <linux/suspend.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>

static int odroid5422_platform_init(struct kbase_device *kbdev)
{
	struct clk *dout_aclk_g3d;
	struct clk *fout_vpll;
	struct regulator *reg;
	struct device *dev = kbdev->dev;
	struct device_node *n = dev->of_node;
	u32 target_freq;
	u32 target_volts;
	int ret = 0;

	ret = of_property_read_u32(n, "mali-freq", &target_freq);
	if(0 < ret) {
		dev_err(dev, "failed to get mali-freq dt bind");
		return ret;
	}
	
	ret = of_property_read_u32(n, "mali-volts", &target_volts);
	if(0 < ret) {
		dev_err(dev, "failed to get mali-volts dt bind");
		return ret;
	}
	
	if(kbdev->current_freq == target_freq)
		return 0;
	
	reg = regulator_get_optional(dev, "gpu");
	if(IS_ERR_OR_NULL(reg)) {
		dev_err(dev, "Failed to get gpu-supply");
		return PTR_ERR(reg);
	}
	
	fout_vpll = clk_get(dev, "fout_vpll");
	if(IS_ERR_OR_NULL(fout_vpll)) {
		dev_err(dev, "Failed to get fout_vpll");
		return PTR_ERR(fout_vpll);
	}
	
	dout_aclk_g3d = clk_get(dev, "dout_aclk_g3d");
	if(IS_ERR_OR_NULL(dout_aclk_g3d)) {
		dev_err(dev, "Failed to get dout_aclk");
		return PTR_ERR(dout_aclk_g3d);
	}
	
	ret = regulator_set_voltage(reg, target_volts, target_volts);
	if(ret < 0) {
		dev_err(dev, "failed to set voltage");
		return ret;
	}
	
	ret = clk_set_rate(fout_vpll, target_freq);
	if(ret < 0) {
		dev_err(dev, "failed to set fout_vpll freq");
		return ret;
	}
	
	ret = clk_set_rate(dout_aclk_g3d, target_freq);
	if(ret < 0) {
		dev_err(dev, "failed to set dout_aclk_g3d freq");
		return ret;
	}
	
	return ret;
}

static void odroid5422_platform_term(struct kbase_device *kbdev)
{
}

struct kbase_platform_funcs_conf platform_funcs = {
	.platform_init_func = odroid5422_platform_init,
	.platform_term_func = odroid5422_platform_term,
};


static struct kbase_platform_config odroid5422_platform_config = {
};

struct kbase_platform_config *kbase_get_platform_config(void)
{
	return &odroid5422_platform_config;
}

struct kbase_pm_callback_conf pm_callbacks = {
	.power_on_callback = odroid5422_platform_init,
	.power_off_callback = odroid5422_platform_term,
	.power_suspend_callback = NULL,
	.power_resume_callback = NULL,
	.power_runtime_init_callback = NULL,
	.power_runtime_term_callback = NULL,
	.power_runtime_on_callback = NULL,
	.power_runtime_off_callback = NULL,
};

int kbase_platform_early_init(void)
{
	/* Nothing needed at this stage */
	return 0;
}
