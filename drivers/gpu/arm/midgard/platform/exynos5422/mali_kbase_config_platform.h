/*
 * Copyright (C) 2015 Samsung Electronics Co.Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define GPU_FREQ_KHZ_MAX	600000
#define GPU_FREQ_KHZ_MIN	600000

#define CPU_SPEED_FUNC (NULL)
#define GPU_SPEED_FUNC (NULL)

#define PLATFORM_FUNCS (&platform_funcs)
extern struct kbase_platform_funcs_conf platform_funcs;

#define POWER_MANAGEMENT_CALLBACKS (&pm_callbacks)
extern struct kbase_pm_callback_conf pm_callbacks;

