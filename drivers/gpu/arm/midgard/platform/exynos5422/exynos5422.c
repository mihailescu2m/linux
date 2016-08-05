/*
 * Copyright (C) 2015 Samsung Electronics Co.Ltd
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

static int exynos5422_platform_init(struct kbase_device *kbdev)
{
	return 0;
}

static void exynos5422_platform_term(struct kbase_device *kbdev)
{
}

struct kbase_platform_funcs_conf platform_funcs = {
	.platform_init_func = exynos5422_platform_init,
	.platform_term_func = exynos5422_platform_term,
};


static struct kbase_platform_config exynos5422_platform_config = {
};

struct kbase_platform_config *kbase_get_platform_config(void)
{
	return &exynos5422_platform_config;
}

struct kbase_pm_callback_conf pm_callbacks = {
	.power_on_callback = exynos5422_platform_init,
	.power_off_callback = exynos5422_platform_term,
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

