/*
 * Samsung Exynos5 SoC series FIMC-IS driver
 *
 * exynos5 fimc-is video functions
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/videodev2.h>
#include <linux/videodev2_exynos_camera.h>

#include "interface/fimc-is-interface-library.h"
#include "interface/fimc-is-interface-ddk.h"
#include "fimc-is-device-sensor-peri.h"
#include "fimc-is-device-sensor.h"
#include "fimc-is-video.h"

extern struct device *fimc_is_dev;
#ifdef FIXED_SENSOR_DEBUG
extern struct fimc_is_sysfs_sensor sysfs_sensor;
#endif

struct fimc_is_device_sensor_peri *find_peri_by_cis_id(struct fimc_is_device_sensor *device,
							u32 cis)
{
	u32 mindex = 0, mmax = 0;
	struct fimc_is_module_enum *module_enum = NULL;
	struct fimc_is_resourcemgr *resourcemgr = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG_NULL(!device);
	FIMC_BUG_NULL(device->instance >= FIMC_IS_SENSOR_COUNT);

	resourcemgr = device->resourcemgr;
	module_enum = device->module_enum;
	FIMC_BUG_NULL(!module_enum);

	if (unlikely(resourcemgr == NULL))
		return NULL;

	mmax = atomic_read(&device->module_count);
	for (mindex = 0; mindex < mmax; mindex++) {
		if (module_enum[mindex].ext.sensor_con.product_name == cis) {
			sensor_peri = (struct fimc_is_device_sensor_peri *)module_enum[mindex].private_data;
			break;
		}
	}

	if (mindex >= mmax) {
		merr("cis(%d) is not found", device, cis);
	}

	return sensor_peri;
}

struct fimc_is_device_sensor_peri *find_peri_by_act_id(struct fimc_is_device_sensor *device,
							u32 actuator)
{
	u32 mindex = 0, mmax = 0;
	struct fimc_is_module_enum *module_enum = NULL;
	struct fimc_is_resourcemgr *resourcemgr = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG_NULL(!device);
	resourcemgr = device->resourcemgr;
	module_enum = device->module_enum;
	FIMC_BUG_NULL(!module_enum);

	if (unlikely(resourcemgr == NULL))
		return NULL;

	mmax = atomic_read(&device->module_count);
	for (mindex = 0; mindex < mmax; mindex++) {
		if (module_enum[mindex].ext.actuator_con.product_name == actuator) {
			sensor_peri = (struct fimc_is_device_sensor_peri *)module_enum[mindex].private_data;
			break;
		}
	}

	if (mindex >= mmax) {
		merr("actuator(%d) is not found", device, actuator);
	}

	return sensor_peri;
}

struct fimc_is_device_sensor_peri *find_peri_by_flash_id(struct fimc_is_device_sensor *device,
							u32 flash)
{
	u32 mindex = 0, mmax = 0;
	struct fimc_is_module_enum *module_enum = NULL;
	struct fimc_is_resourcemgr *resourcemgr = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG_NULL(!device);
	resourcemgr = device->resourcemgr;
	module_enum = device->module_enum;
	FIMC_BUG_NULL(!module_enum);

	if (unlikely(resourcemgr == NULL))
		return NULL;

	mmax = atomic_read(&device->module_count);
	for (mindex = 0; mindex < mmax; mindex++) {
		if (module_enum[mindex].ext.flash_con.product_name == flash) {
			sensor_peri = (struct fimc_is_device_sensor_peri *)module_enum[mindex].private_data;
			break;
		}
	}

	if (mindex >= mmax) {
		merr("flash(%d) is not found", device, flash);
	}

	return sensor_peri;
}

struct fimc_is_device_sensor_peri *find_peri_by_preprocessor_id(struct fimc_is_device_sensor *device,
							u32 preprocessor)
{
	u32 mindex = 0, mmax = 0;
	struct fimc_is_module_enum *module_enum = NULL;
	struct fimc_is_resourcemgr *resourcemgr = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG_NULL(!device);
	resourcemgr = device->resourcemgr;
	module_enum = device->module_enum;
	FIMC_BUG_NULL(!module_enum);

	if (unlikely(resourcemgr == NULL))
		return NULL;

	mmax = atomic_read(&device->module_count);
	for (mindex = 0; mindex < mmax; mindex++) {
		if (module_enum[mindex].ext.preprocessor_con.product_name == preprocessor) {
			sensor_peri = (struct fimc_is_device_sensor_peri *)module_enum[mindex].private_data;
			break;
		}
	}

	if (mindex >= mmax) {
		merr("preprocessor(%d) is not found", device, preprocessor);
		printk("preprocessor is not found");
	}

	return sensor_peri;
}

struct fimc_is_device_sensor_peri *find_peri_by_ois_id(struct fimc_is_device_sensor *device,
							u32 ois)
{
	u32 mindex = 0, mmax = 0;
	struct fimc_is_module_enum *module_enum = NULL;
	struct fimc_is_resourcemgr *resourcemgr = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG_NULL(!device);
	resourcemgr = device->resourcemgr;
	module_enum = device->module_enum;
	FIMC_BUG_NULL(!module_enum);

	if (unlikely(resourcemgr == NULL))
		return NULL;

	mmax = atomic_read(&device->module_count);
	for (mindex = 0; mindex < mmax; mindex++) {
		if (module_enum[mindex].ext.ois_con.product_name == ois) {
			sensor_peri = (struct fimc_is_device_sensor_peri *)module_enum[mindex].private_data;
			break;
		}
	}

	if (mindex >= mmax) {
		merr("ois(%d) is not found", device, ois);
	}

	return sensor_peri;
}

int fimc_is_sensor_peri_s_totalgain(struct fimc_is_device_sensor *device,
	struct ae_param expo,
	struct ae_param again,
	struct ae_param dgain)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

#ifdef FIXED_SENSOR_DEBUG
	if (unlikely(sysfs_sensor.is_en == true)) {
		expo.long_val = sysfs_sensor.long_exposure_time;
		expo.short_val = sysfs_sensor.short_exposure_time;
		dbg_sensor(1, "exposure = %d %d\n", expo.long_val, expo.short_val);

		again.long_val = sysfs_sensor.long_analog_gain * 10;
		again.short_val = sysfs_sensor.short_analog_gain * 10;
		dbg_sensor(1, "again = %d %d\n", sysfs_sensor.long_analog_gain, sysfs_sensor.short_analog_gain);

		dgain.long_val = sysfs_sensor.long_digital_gain * 10;
		dgain.short_val = sysfs_sensor.short_digital_gain * 10;
		dbg_sensor(1, "dgain = %d %d\n", sysfs_sensor.long_digital_gain, sysfs_sensor.short_digital_gain);
	}
#endif

	ret = CALL_CISOPS(&sensor_peri->cis, cis_set_totalgain, sensor_peri->subdev_cis, &expo, &again, &dgain);
	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		goto p_err;
	}

	device->exposure_time = expo.long_val;
	/* 0: Previous input, 1: Current input */
	sensor_peri->cis.cis_data->analog_gain[0] = sensor_peri->cis.cis_data->analog_gain[1];
	sensor_peri->cis.cis_data->analog_gain[1] = again.long_val;
	sensor_peri->cis.cis_data->digital_gain[0] = sensor_peri->cis.cis_data->digital_gain[1];
	sensor_peri->cis.cis_data->digital_gain[1] = dgain.long_val;

p_err:
	return ret;
}

static void fimc_is_sensor_init_expecting_dm(struct fimc_is_device_sensor *device,
	struct fimc_is_cis *cis)
{
	int i = 0;
	u32 m_fcount;
	u32 sensitivity;
	u64 exposureTime, long_exposure, short_exposure;
	u32 long_dgain, long_again, short_dgain, short_again;
	struct fimc_is_sensor_ctl *module_ctl;
	camera2_sensor_ctl_t *sensor_ctrl = NULL;
	camera2_sensor_uctl_t *sensor_uctrl = NULL;

	if (test_bit(FIMC_IS_SENSOR_FRONT_START, &device->state)) {
		mwarn("sensor is already stream on", device);
		goto p_err;
	}

	m_fcount = (device->fcount + 1) % EXPECT_DM_NUM;

	module_ctl = &cis->sensor_ctls[m_fcount];
	sensor_ctrl = &module_ctl->cur_cam20_sensor_ctrl;
	sensor_uctrl = &module_ctl->cur_cam20_sensor_udctrl;

	sensitivity = sensor_uctrl->sensitivity;
	exposureTime = sensor_uctrl->exposureTime;
	long_exposure = sensor_uctrl->longExposureTime;
	short_exposure = sensor_uctrl->shortExposureTime;
	long_dgain = sensor_uctrl->longDigitalGain;
	long_again = sensor_uctrl->longAnalogGain;
	short_dgain = sensor_uctrl->shortDigitalGain;
	short_again = sensor_uctrl->shortAnalogGain;

	if (module_ctl->valid_sensor_ctrl == true) {
		if (sensor_ctrl->sensitivity)
			sensitivity = sensor_ctrl->sensitivity;

		if (sensor_ctrl->exposureTime)
			exposureTime = sensor_ctrl->exposureTime;
	}

	for (i = m_fcount + 2; i < m_fcount + EXPECT_DM_NUM; i++) {
		cis->expecting_sensor_dm[i % EXPECT_DM_NUM].sensitivity = sensitivity;
		cis->expecting_sensor_dm[i % EXPECT_DM_NUM].exposureTime = exposureTime;

		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].longExposureTime = long_exposure;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].shortExposureTime = short_exposure;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].digitalGain = long_dgain;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].analogGain = long_dgain;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].longDigitalGain = long_dgain;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].longAnalogGain = long_dgain;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].shortDigitalGain = short_dgain;
		cis->expecting_sensor_udm[i % EXPECT_DM_NUM].shortAnalogGain = short_again;
	}

p_err:
	return;
}

void fimc_is_sensor_cis_status_dump_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_cis *cis;
	struct fimc_is_device_sensor_peri *sensor_peri;

	FIMC_BUG_VOID(!data);

	cis = container_of(data, struct fimc_is_cis, cis_status_dump_work);
	FIMC_BUG_VOID(!cis);

	sensor_peri = container_of(cis, struct fimc_is_device_sensor_peri, cis);

	if (sensor_peri->subdev_cis) {
		ret = CALL_CISOPS(cis, cis_log_status, sensor_peri->subdev_cis);
		if (ret < 0) {
			err("err!!! log_status ret(%d)", ret);
		}
	}
}

void fimc_is_sensor_set_cis_uctrl_list(struct fimc_is_device_sensor_peri *sensor_peri,
		enum fimc_is_exposure_gain_count num_data,
		u32 *exposure,
		u32 *total_gain,
		u32 *analog_gain,
		u32 *digital_gain)
{
	int i = 0;
	camera2_sensor_uctl_t *sensor_uctl;

	FIMC_BUG_VOID(!sensor_peri);
	FIMC_BUG_VOID(!exposure);
	FIMC_BUG_VOID(!total_gain);
	FIMC_BUG_VOID(!analog_gain);
	FIMC_BUG_VOID(!digital_gain);

	for (i = 0; i < CAM2P0_UCTL_LIST_SIZE; i++) {
		if (sensor_peri->cis.sensor_ctls[i].force_update) {
			dbg_sensor(1, "skip uctl_list set, sensor_ctl[%d]->force_update\n", i);
			continue;
		}

		sensor_uctl = &sensor_peri->cis.sensor_ctls[i].cur_cam20_sensor_udctrl;

		fimc_is_sensor_ctl_update_exposure_to_uctl(sensor_uctl, num_data, exposure);
		fimc_is_sensor_ctl_update_gain_to_uctl(sensor_uctl, num_data, analog_gain, digital_gain);
	}
}

void fimc_is_sensor_sensor_work_fn(struct kthread_work *work)
{
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct fimc_is_device_sensor *device;

	sensor_peri = container_of(work, struct fimc_is_device_sensor_peri, sensor_work);

	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_cis);

	fimc_is_sensor_ctl_frame_evt(device);
}

int fimc_is_sensor_init_sensor_thread(struct fimc_is_device_sensor_peri *sensor_peri)
{
	int ret = 0;
	struct sched_param param = {.sched_priority = TASK_SENSOR_WORK_PRIO};

	if (sensor_peri->sensor_task == NULL) {
		spin_lock_init(&sensor_peri->sensor_work_lock);
		kthread_init_work(&sensor_peri->sensor_work, fimc_is_sensor_sensor_work_fn);
		kthread_init_worker(&sensor_peri->sensor_worker);
		sensor_peri->sensor_task = kthread_run(kthread_worker_fn,
						&sensor_peri->sensor_worker,
						"fimc_is_sen_sensor_work");
		if (IS_ERR(sensor_peri->sensor_task)) {
			err("failed to create kthread for sensor, err(%ld)",
				PTR_ERR(sensor_peri->sensor_task));
			ret = PTR_ERR(sensor_peri->sensor_task);
			sensor_peri->sensor_task = NULL;
			return ret;
		}

		ret = sched_setscheduler_nocheck(sensor_peri->sensor_task, SCHED_FIFO, &param);
		if (ret) {
			err("sched_setscheduler_nocheck is fail(%d)", ret);
			return ret;
		}

		kthread_init_work(&sensor_peri->sensor_work, fimc_is_sensor_sensor_work_fn);
	}

	return ret;
}

void fimc_is_sensor_deinit_sensor_thread(struct fimc_is_device_sensor_peri *sensor_peri)
{
	if (sensor_peri->sensor_task != NULL) {
		if (kthread_stop(sensor_peri->sensor_task))
			err("kthread_stop fail");

		sensor_peri->sensor_task = NULL;
		sensor_peri->use_sensor_work = false;
		info("%s:\n", __func__);
	}
}

int fimc_is_sensor_init_mode_change_thread(struct fimc_is_device_sensor_peri *sensor_peri)
{
	int ret = 0;

	/* Always first applyed to mode change when camera on */
	sensor_peri->mode_change_first = true;

	kthread_init_work(&sensor_peri->mode_change_work, fimc_is_sensor_mode_change_work_fn);
	kthread_init_worker(&sensor_peri->mode_change_worker);
	sensor_peri->mode_change_task = kthread_run(kthread_worker_fn,
						&sensor_peri->mode_change_worker,
						"fimc_is_sensor_mode_change");
	if (IS_ERR(sensor_peri->mode_change_task)) {
		err("failed to create kthread fir sensor mode change, err(%ld)",
			PTR_ERR(sensor_peri->mode_change_task));
		ret = PTR_ERR(sensor_peri->mode_change_task);
		sensor_peri->mode_change_task = NULL;
		return ret;
	}

	return ret;
}

void fimc_is_sensor_deinit_mode_change_thread(struct fimc_is_device_sensor_peri *sensor_peri)
{
	if (sensor_peri->mode_change_task != NULL) {
		if (kthread_stop(sensor_peri->mode_change_task))
			err("kthread_stop fail");

		sensor_peri->mode_change_task = NULL;
		info("%s:\n", __func__);
	}
}

int fimc_is_sensor_initial_setting_low_exposure(struct fimc_is_device_sensor_peri *sensor_peri)
{
	int ret = 0;
	struct fimc_is_device_sensor *device;
	struct ae_param expo, again, dgain;
	struct fimc_is_cis_ops *cis_ops = NULL;
	u32 tgain[EXPOSURE_GAIN_MAX] = {1000, 1000, 1000};
	FIMC_BUG(!sensor_peri);

	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_cis);
	FIMC_BUG(!device);

	dbg_sensor(1, "[%s] expo(%d), again(%d), dgain(%d)\n", __func__,
			sensor_peri->cis.cis_data->low_expo_start, 100, 100);

	again.long_val = again.short_val = again.middle_val = 1000;
	dgain.long_val = dgain.short_val = dgain.middle_val = 1000;
	expo.long_val = expo.short_val = expo.middle_val =
			sensor_peri->cis.cis_data->low_expo_start;

	cis_ops = (struct fimc_is_cis_ops *)sensor_peri->cis.cis_ops;
	if(cis_ops->cis_set_exposure_time
		&& cis_ops->cis_set_analog_gain
		&& cis_ops->cis_set_digital_gain) {
		fimc_is_sensor_peri_s_analog_gain(device, again);
		fimc_is_sensor_peri_s_digital_gain(device, dgain);
		fimc_is_sensor_peri_s_exposure_time(device, expo);
	}else {
		fimc_is_sensor_peri_s_totalgain(device, expo, again, dgain);
	}

#if !defined(DISABLE_LIB)
	sensor_peri->sensor_interface.cis_itf_ops.request_reset_expo_gain(&sensor_peri->sensor_interface,
			EXPOSURE_GAIN_COUNT_3,
			&expo.long_val,
			tgain,
			&again.long_val,
			&dgain.long_val);
#endif

	return ret;
}

void fimc_is_sensor_mode_change_work_fn(struct kthread_work *work)
{
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct fimc_is_cis *cis;

	TIME_LAUNCH_STR(LAUNCH_SENSOR_INIT);
	sensor_peri = container_of(work, struct fimc_is_device_sensor_peri, mode_change_work);

	cis = (struct fimc_is_cis *)v4l2_get_subdevdata(sensor_peri->subdev_cis);

	/* cis global setting is only set to first mode change time */
	if (sensor_peri->mode_change_first == true) {
		CALL_CISOPS(cis, cis_set_global_setting, cis->subdev);
	}

	CALL_CISOPS(cis, cis_mode_change, cis->subdev, cis->cis_data->sens_config_index_cur);

	sensor_peri->mode_change_first = false;
	TIME_LAUNCH_END(LAUNCH_SENSOR_INIT);
}

int fimc_is_sensor_mode_change(struct fimc_is_cis *cis, u32 mode)
{
	int ret = 0;
	struct fimc_is_device_sensor_peri *sensor_peri;

	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	sensor_peri = container_of(cis, struct fimc_is_device_sensor_peri, cis);

	CALL_CISOPS(cis, cis_data_calculation, cis->subdev, cis->cis_data->sens_config_index_cur);
	kthread_queue_work(&sensor_peri->mode_change_worker, &sensor_peri->mode_change_work);

	return ret;
}

void fimc_is_sensor_setting_mode_change(struct fimc_is_device_sensor_peri *sensor_peri)
{
	struct fimc_is_device_sensor *device;
	struct ae_param expo;
	struct ae_param again;
	struct ae_param dgain;
	struct fimc_is_cis_ops *cis_ops = NULL;
	u32 tgain[EXPOSURE_GAIN_MAX] = {0, 0, 0};
	enum fimc_is_exposure_gain_count num_data;
	u32 frame_duration = 0;

	FIMC_BUG_VOID(!sensor_peri);

	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_cis);
	FIMC_BUG_VOID(!device);

	num_data = sensor_peri->cis.exp_gain_cnt;
	switch (num_data) {
	case EXPOSURE_GAIN_COUNT_1:
		expo.val = expo.short_val = sensor_peri->cis.mode_chg.exposure;
		again.val = again.short_val = sensor_peri->cis.mode_chg.analog_gain;
		dgain.val = dgain.short_val = sensor_peri->cis.mode_chg.digital_gain;
		expo.middle_val = 1000;
		again.middle_val = 1000;
		dgain.middle_val = 1000;

		if (expo.val == 0 || again.val < 1000 || dgain.val < 1000) {
			err("[%s] invalid mode change settings exp(%d), again(%d), dgain(%d)\n",
				__func__, expo.val, again.val, dgain.val);
			expo.val = sensor_peri->cis.cis_data->low_expo_start;
			again.val = 1000;
			dgain.val = 1000;
		}

		tgain[EXPOSURE_GAIN_LONG] = fimc_is_sensor_calculate_tgain(dgain.val, again.val);
		break;
	case EXPOSURE_GAIN_COUNT_2:
		expo.long_val = sensor_peri->cis.mode_chg.long_exposure;
		again.long_val = sensor_peri->cis.mode_chg.long_analog_gain;
		dgain.long_val = sensor_peri->cis.mode_chg.long_digital_gain;
		expo.short_val = sensor_peri->cis.mode_chg.short_exposure;
		again.short_val = sensor_peri->cis.mode_chg.short_analog_gain;
		dgain.short_val = sensor_peri->cis.mode_chg.short_digital_gain;
		expo.middle_val = 1000;
		again.middle_val = 1000;
		dgain.middle_val = 1000;

		if (expo.long_val == 0 || again.long_val < 1000 || dgain.long_val < 1000
			|| expo.short_val == 0 || again.short_val < 1000 || dgain.short_val < 1000) {
			err("[%s] invalid mode change settings exp(%d %d), again(%d %d), dgain(%d %d)\n",
				__func__, expo.long_val, expo.short_val,
				again.long_val, again.short_val, dgain.long_val, dgain.short_val);
			expo.long_val = expo.short_val = sensor_peri->cis.cis_data->low_expo_start;
			again.long_val = again.short_val = 1000;
			dgain.long_val = dgain.short_val = 1000;
		}

		tgain[EXPOSURE_GAIN_LONG] = fimc_is_sensor_calculate_tgain(dgain.long_val, again.long_val);
		tgain[EXPOSURE_GAIN_SHORT] = fimc_is_sensor_calculate_tgain(dgain.short_val, again.short_val);
		break;
	case EXPOSURE_GAIN_COUNT_3:
		expo.long_val = sensor_peri->cis.mode_chg.long_exposure;
		again.long_val = sensor_peri->cis.mode_chg.long_analog_gain;
		dgain.long_val = sensor_peri->cis.mode_chg.long_digital_gain;
		expo.short_val = sensor_peri->cis.mode_chg.short_exposure;
		again.short_val = sensor_peri->cis.mode_chg.short_analog_gain;
		dgain.short_val = sensor_peri->cis.mode_chg.short_digital_gain;
		expo.middle_val = sensor_peri->cis.mode_chg.middle_exposure;
		again.middle_val = sensor_peri->cis.mode_chg.middle_analog_gain;
		dgain.middle_val = sensor_peri->cis.mode_chg.middle_digital_gain;

		if (expo.long_val == 0 || again.long_val < 1000 || dgain.long_val < 1000
			|| expo.short_val == 0 || again.short_val < 1000 || dgain.short_val < 1000
			|| expo.middle_val == 0 || again.middle_val < 1000 || dgain.middle_val < 1000) {
			err("[%s] invalid mode change settings exp(%d %d %d), again(%d %d %d), dgain(%d %d %d)\n",
				__func__, expo.long_val, expo.short_val,
				again.long_val, again.short_val, dgain.long_val, dgain.short_val);
			expo.long_val = expo.short_val = expo.middle_val = sensor_peri->cis.cis_data->low_expo_start;
			again.long_val = again.short_val = again.middle_val = 1000;
			dgain.long_val = dgain.short_val = again.middle_val = 1000;
		}

		tgain[EXPOSURE_GAIN_LONG] = fimc_is_sensor_calculate_tgain(dgain.long_val, again.long_val);
		tgain[EXPOSURE_GAIN_SHORT] = fimc_is_sensor_calculate_tgain(dgain.short_val, again.short_val);
		tgain[EXPOSURE_GAIN_MIDDLE] = fimc_is_sensor_calculate_tgain(dgain.middle_val, again.middle_val);
		break;
	default:
		err("[%s] invalid exp_gain_count(%d)\n", __func__, num_data);
	}

	dbg_sensor(1, "[%s]num_data(%d): expo(L(%d), M(%d), S(%d) / again(L(%d), M(%d), S(%d) / dgain(L(%d), M(%d), S(%d)\n",
		__func__, num_data, expo.long_val, expo.middle_val, expo.short_val,
				again.long_val, again.middle_val, again.short_val,
				dgain.long_val, dgain.middle_val, dgain.middle_val);

	if (sensor_peri->cis.long_term_mode.sen_strm_off_on_enable) {
		CALL_CISOPS(&sensor_peri->cis, cis_set_long_term_exposure, sensor_peri->subdev_cis);
	} else {
		if (sensor_peri->cis.cis_data->frame_length_lines_shifter > 0
			&& sensor_peri->cis.cis_data->min_frame_us_time >= 1000000)
			CALL_CISOPS(&sensor_peri->cis, cis_data_calculation, sensor_peri->subdev_cis, device->cfg->mode);
	}
	CALL_CISOPS(&sensor_peri->cis, cis_adjust_frame_duration, sensor_peri->subdev_cis,
			expo.long_val, &frame_duration);
	fimc_is_sensor_peri_s_frame_duration(device, frame_duration);

	cis_ops = (struct fimc_is_cis_ops *)sensor_peri->cis.cis_ops;
	if(cis_ops->cis_set_exposure_time
		&& cis_ops->cis_set_analog_gain
		&& cis_ops->cis_set_digital_gain) {
		fimc_is_sensor_peri_s_analog_gain(device, again);
		fimc_is_sensor_peri_s_digital_gain(device, dgain);
		fimc_is_sensor_peri_s_exposure_time(device, expo);
	}else {
		fimc_is_sensor_peri_s_totalgain(device, expo, again, dgain);
	}

	fimc_is_sensor_peri_s_wb_gains(device, sensor_peri->cis.mode_chg_wb_gains);
	fimc_is_sensor_peri_s_sensor_stats(device, false, NULL,
			(void *)(uintptr_t)(sensor_peri->cis.sensor_stats || sensor_peri->cis.lsc_table_status));

	sensor_peri->sensor_interface.cis_itf_ops.request_reset_expo_gain(&sensor_peri->sensor_interface,
			num_data,
			&expo.long_val,
			tgain,
			&again.long_val,
			&dgain.long_val);
}

void fimc_is_sensor_flash_fire_work(struct work_struct *data)
{
	int ret = 0;
	u32 frame_duration = 0;
	struct fimc_is_flash *flash;
	struct fimc_is_flash_data *flash_data;
	struct fimc_is_device_sensor *device;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct v4l2_subdev *subdev_flash;
	struct ae_param expo, dgain, again;
	struct fimc_is_cis_ops *cis_ops = NULL;
	u32 tgain[EXPOSURE_GAIN_MAX];
	u32 step = 0;
	FIMC_BUG_VOID(!data);

	flash_data = container_of(data, struct fimc_is_flash_data, flash_fire_work);
	FIMC_BUG_VOID(!flash_data);

	flash = container_of(flash_data, struct fimc_is_flash, flash_data);
	FIMC_BUG_VOID(!flash);

	sensor_peri = flash->sensor_peri;
	FIMC_BUG_VOID(!sensor_peri);

	subdev_flash = sensor_peri->subdev_flash;

	device = v4l2_get_subdev_hostdata(subdev_flash);
	FIMC_BUG_VOID(!device);

	mutex_lock(&sensor_peri->cis.control_lock);

	if (!sensor_peri->cis.cis_data->stream_on) {
		warn("[%s] already stream off\n", __func__);
		goto already_stream_off;
	}

	/* sensor stream off */
	ret = CALL_CISOPS(&sensor_peri->cis, cis_stream_off, sensor_peri->subdev_cis);
	if (ret < 0) {
		err("[%s] stream off fail\n", __func__);
		goto fail_cis_stream_off;
	}

	ret = CALL_CISOPS(&sensor_peri->cis, cis_wait_streamoff, sensor_peri->subdev_cis);
	if (ret < 0) {
		err("[%s] wait stream off fail\n", __func__);
		goto fail_cis_stream_off;
	}

	/* preprocessor stream off */
	if (sensor_peri->subdev_preprocessor) {
		ret = CALL_PREPROPOPS(sensor_peri->preprocessor, preprocessor_stream_off,
			sensor_peri->subdev_preprocessor);
		if (ret) {
			err("[%s] preprocessor stream off fail\n", __func__);
			goto fail_preprocessor_stream_off;
		}
	}

	dbg_flash("[%s] steram off done\n", __func__);

	/* flash setting */

	step = flash->flash_ae.main_fls_strm_on_off_step;

	if (sensor_peri->sensor_interface.cis_mode == ITF_CIS_SMIA) {
		expo.val = expo.short_val = expo.middle_val = flash->flash_ae.expo[step];
		again.val = again.short_val = again.middle_val = flash->flash_ae.again[step];
		dgain.val = dgain.short_val = dgain.middle_val = flash->flash_ae.dgain[step];
		tgain[0] = tgain[1] = tgain[2] = flash->flash_ae.tgain[step];

		CALL_CISOPS(&sensor_peri->cis, cis_adjust_frame_duration, sensor_peri->subdev_cis,
		    flash->flash_ae.expo[step], &frame_duration);
		fimc_is_sensor_peri_s_frame_duration(device, frame_duration);

		cis_ops = (struct fimc_is_cis_ops *)sensor_peri->cis.cis_ops;
		if(cis_ops->cis_set_exposure_time
			&& cis_ops->cis_set_analog_gain
			&& cis_ops->cis_set_digital_gain) {
			fimc_is_sensor_peri_s_analog_gain(device, again);
			fimc_is_sensor_peri_s_digital_gain(device, dgain);
			fimc_is_sensor_peri_s_exposure_time(device, expo);
		}else {
			fimc_is_sensor_peri_s_totalgain(device, expo, again, dgain);
		}

		sensor_peri->sensor_interface.cis_itf_ops.request_reset_expo_gain(&sensor_peri->sensor_interface,
			EXPOSURE_GAIN_COUNT_3,
			&expo.val,
			tgain,
			&again.val,
			&dgain.val);
	} else {
		expo.long_val = expo.middle_val = flash->flash_ae.long_expo[step]; /* TODO: divide middle */
		expo.short_val = flash->flash_ae.short_expo[step];
		again.long_val = again.middle_val = flash->flash_ae.long_again[step];
		again.short_val = flash->flash_ae.short_again[step];
		dgain.long_val = dgain.middle_val = flash->flash_ae.long_dgain[step];
		dgain.short_val = flash->flash_ae.short_again[step];
		tgain[0] = tgain[2] = flash->flash_ae.long_tgain[step];
		tgain[1] = flash->flash_ae.short_tgain[step];

		CALL_CISOPS(&sensor_peri->cis, cis_adjust_frame_duration, sensor_peri->subdev_cis,
			MAX(flash->flash_ae.long_expo[step], flash->flash_ae.short_expo[step]), &frame_duration);
		fimc_is_sensor_peri_s_frame_duration(device, frame_duration);

		cis_ops = (struct fimc_is_cis_ops *)sensor_peri->cis.cis_ops;
		if(cis_ops->cis_set_exposure_time
			&& cis_ops->cis_set_analog_gain
			&& cis_ops->cis_set_digital_gain) {
			fimc_is_sensor_peri_s_analog_gain(device, again);
			fimc_is_sensor_peri_s_digital_gain(device, dgain);
			fimc_is_sensor_peri_s_exposure_time(device, expo);
		}else {
			fimc_is_sensor_peri_s_totalgain(device, expo, again, dgain);
		}

		sensor_peri->sensor_interface.cis_itf_ops.request_reset_expo_gain(&sensor_peri->sensor_interface,
			EXPOSURE_GAIN_COUNT_3,
			&expo.val,
			tgain,
			&again.val,
			&dgain.val);
	}

	dbg_flash("[%s][FLASH] mode %d, intensity %d, firing time %d us, step %d\n", __func__,
			flash->flash_data.mode,
			flash->flash_data.intensity,
			flash->flash_data.firing_time_us,
			step);

	/* flash fire */
	if (flash->flash_ae.pre_fls_ae_reset == true) {
		if (flash->flash_ae.frm_num_pre_fls != 0) {
			flash->flash_data.mode = CAM2_FLASH_MODE_OFF;
			flash->flash_data.intensity = 0;
			flash->flash_data.firing_time_us = 0;

			info("[%s] pre-flash OFF(%d), pow(%d), time(%d)\n",
					__func__,
					flash->flash_data.mode,
					flash->flash_data.intensity,
					flash->flash_data.firing_time_us);

			ret = fimc_is_sensor_flash_fire(sensor_peri, flash->flash_data.intensity);
			if (ret) {
				err("failed to turn off flash at flash expired handler\n");
			}

			flash->flash_ae.pre_fls_ae_reset = false;
			flash->flash_ae.frm_num_pre_fls = 0;
		}
	} else if (flash->flash_ae.main_fls_ae_reset == true) {
		if (flash->flash_ae.main_fls_strm_on_off_step == 0) {
			if (flash->flash_data.flash_fired == false) {
				flash->flash_data.mode = CAM2_FLASH_MODE_SINGLE;
				flash->flash_data.intensity = 10;
				flash->flash_data.firing_time_us = 500000;

				info("[%s] main-flash ON(%d), pow(%d), time(%d)\n",
					__func__,
					flash->flash_data.mode,
					flash->flash_data.intensity,
					flash->flash_data.firing_time_us);

				ret = fimc_is_sensor_flash_fire(sensor_peri, flash->flash_data.intensity);
				if (ret) {
					err("failed to turn off flash at flash expired handler\n");
				}
			} else {
				flash->flash_ae.main_fls_ae_reset = false;
				flash->flash_ae.main_fls_strm_on_off_step = 0;
				flash->flash_ae.frm_num_main_fls[0] = 0;
				flash->flash_ae.frm_num_main_fls[1] = 0;
			}
			flash->flash_ae.main_fls_strm_on_off_step++;
		} else if (flash->flash_ae.main_fls_strm_on_off_step == 1) {
			flash->flash_data.mode = CAM2_FLASH_MODE_OFF;
			flash->flash_data.intensity = 0;
			flash->flash_data.firing_time_us = 0;

			info("[%s] main-flash OFF(%d), pow(%d), time(%d)\n",
					__func__,
					flash->flash_data.mode,
					flash->flash_data.intensity,
					flash->flash_data.firing_time_us);

			ret = fimc_is_sensor_flash_fire(sensor_peri, flash->flash_data.intensity);
			if (ret) {
				err("failed to turn off flash at flash expired handler\n");
			}

			flash->flash_ae.main_fls_ae_reset = false;
			flash->flash_ae.main_fls_strm_on_off_step = 0;
			flash->flash_ae.frm_num_main_fls[0] = 0;
			flash->flash_ae.frm_num_main_fls[1] = 0;
		}
	}

	/* preprocessor stream on */
	if (sensor_peri->subdev_preprocessor) {
		ret = CALL_PREPROPOPS(sensor_peri->preprocessor, preprocessor_stream_on,
			sensor_peri->subdev_preprocessor);
		if (ret) {
			err("[%s] preprocessor stream on fail\n", __func__);
		}
	}

fail_preprocessor_stream_off:
	/* sensor stream on */
	ret = CALL_CISOPS(&sensor_peri->cis, cis_stream_on, sensor_peri->subdev_cis);
	if (ret < 0) {
		err("[%s] stream on fail\n", __func__);
	}

	ret = CALL_CISOPS(&sensor_peri->cis, cis_wait_streamon, sensor_peri->subdev_cis);
	if (ret < 0)
		err("[%s] sensor wait stream on fail\n", __func__);

fail_cis_stream_off:
already_stream_off:
	mutex_unlock(&sensor_peri->cis.control_lock);
}

void fimc_is_sensor_flash_expire_handler(unsigned long data)
{
	struct fimc_is_device_sensor_peri *device = (struct fimc_is_device_sensor_peri *)data;
	struct v4l2_subdev *subdev_flash;
	struct fimc_is_flash *flash;

	FIMC_BUG_VOID(!device);

	subdev_flash = device->subdev_flash;
	FIMC_BUG_VOID(!subdev_flash);

	flash = v4l2_get_subdevdata(subdev_flash);
	FIMC_BUG_VOID(!flash);

	schedule_work(&device->flash->flash_data.flash_expire_work);
}

void fimc_is_sensor_flash_expire_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_flash *flash;
	struct fimc_is_flash_data *flash_data;
	struct fimc_is_device_sensor_peri *sensor_peri;

	FIMC_BUG_VOID(!data);

	flash_data = container_of(data, struct fimc_is_flash_data, flash_expire_work);
	FIMC_BUG_VOID(!flash_data);

	flash = container_of(flash_data, struct fimc_is_flash, flash_data);
	FIMC_BUG_VOID(!flash);

	sensor_peri = flash->sensor_peri;

	ret = fimc_is_sensor_flash_fire(sensor_peri, 0);
	if (ret) {
		err("failed to turn off flash at flash expired handler\n");
	}
}

void fimc_is_sensor_ois_set_init_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_ois *ois;
	struct fimc_is_device_sensor_peri *sensor_peri;

	WARN_ON(!data);

	ois = container_of(data, struct fimc_is_ois, ois_set_init_work);
	WARN_ON(!ois);

	sensor_peri = ois->sensor_peri;

	ret = CALL_OISOPS(sensor_peri->ois, ois_set_mode, sensor_peri->subdev_ois,
		OPTICAL_STABILIZATION_MODE_CENTERING);
	if (ret < 0)
		err("v4l2_subdev_call(ois_set_mode) is fail(%d)", ret);

	msleep(40);

	ois->initial_centering_mode = true;
}

void fimc_is_sensor_aperture_set_start_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_aperture *aperture;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct fimc_is_device_sensor *device;
	struct fimc_is_core *core;

	WARN_ON(!data);

	aperture = container_of(data, struct fimc_is_aperture, aperture_set_start_work);
	WARN_ON(!aperture);

	sensor_peri = aperture->sensor_peri;

	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_mcu);
	WARN_ON(!device);

	core = (struct fimc_is_core *)device->private_data;

	mutex_lock(&core->ois_mode_lock);

	ret = CALL_APERTUREOPS(sensor_peri->mcu->aperture, set_aperture_value, sensor_peri->subdev_mcu,
		sensor_peri->mcu->aperture->start_value);
	if (ret < 0)
		err("[%s] aperture set fail\n", __func__);

	mutex_unlock(&core->ois_mode_lock);
}

void fimc_is_sensor_aperture_set_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_aperture *aperture;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct fimc_is_device_sensor *device;
	bool need_stream_off = false;

	WARN_ON(!data);

	aperture = container_of(data, struct fimc_is_aperture, aperture_set_work);
	WARN_ON(!aperture);

	sensor_peri = aperture->sensor_peri;
	WARN_ON(!sensor_peri->subdev_cis);

	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_mcu);
	WARN_ON(!device);

	info("[%s] start\n", __func__);

	//mutex_lock(&aperture->control_lock);

	if (device->sstream)
		need_stream_off = true;

#if 0 // need to check
	/* Sensor stream off */
	if (need_stream_off) {
		mutex_lock(&sensor_peri->cis.control_lock);
		ret = CALL_CISOPS(&sensor_peri->cis, cis_stream_off, sensor_peri->subdev_cis);
		if (ret < 0)
			err("[%s] stream off fail\n", __func__);

		ret = CALL_CISOPS(&sensor_peri->cis, cis_wait_streamoff, sensor_peri->subdev_cis);
		if (ret < 0)
			err("[%s] wait stream off fail\n", __func__);
		mutex_unlock(&sensor_peri->cis.control_lock);
	}
#endif
	ret = CALL_APERTUREOPS(sensor_peri->mcu->aperture, set_aperture_value, sensor_peri->subdev_mcu,
		sensor_peri->mcu->aperture->new_value);
	if (ret < 0)
		err("[%s] aperture set fail\n", __func__);

#if 0 // need to check
	/* Sensor stream on */
	if (need_stream_off && device->sstream) {
		mutex_lock(&sensor_peri->cis.control_lock);
		ret = CALL_CISOPS(&sensor_peri->cis, cis_stream_on, sensor_peri->subdev_cis);
		if (ret < 0)
			err("[%s] stream on fail\n", __func__);
		mutex_unlock(&sensor_peri->cis.control_lock);
	}
#endif
	//mutex_unlock(&aperture->control_lock);

	info("[%s] end\n", __func__);
}

int fimc_is_sensor_flash_fire(struct fimc_is_device_sensor_peri *device,
				u32 on)
{
	int ret = 0;
	struct v4l2_subdev *subdev_flash;
	struct fimc_is_flash *flash;
	struct v4l2_control ctrl;

	FIMC_BUG(!device);

	subdev_flash = device->subdev_flash;
	if (!subdev_flash) {
		err("subdev_flash is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	flash = v4l2_get_subdevdata(subdev_flash);
	if (!flash) {
		err("flash is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	if (flash->flash_data.mode == CAM2_FLASH_MODE_OFF && (bool)on == 1) {
		err("Flash mode is off");
		flash->flash_data.flash_fired = false;
		goto p_err;
	}

	if (flash->flash_data.flash_fired != (bool)on) {
		ctrl.id = V4L2_CID_FLASH_SET_FIRE;
		ctrl.value = on ? flash->flash_data.intensity : 0;
		ret = v4l2_subdev_call(subdev_flash, core, s_ctrl, &ctrl);
		if (ret < 0) {
			err("err!!! ret(%d)", ret);
			goto p_err;
		}
		flash->flash_data.flash_fired = (bool)on;
	}

	if (flash->flash_data.mode == CAM2_FLASH_MODE_SINGLE ||
			flash->flash_data.mode == CAM2_FLASH_MODE_OFF) {
		if (flash->flash_data.flash_fired == true) {
			/* Flash firing time have to be setted in case of capture flash
			 * Max firing time of capture flash is 1 sec
			 */
			if (flash->flash_data.firing_time_us == 0 || flash->flash_data.firing_time_us > 1 * 1000 * 1000)
				flash->flash_data.firing_time_us = 1 * 1000 * 1000;

			setup_timer(&flash->flash_data.flash_expire_timer, fimc_is_sensor_flash_expire_handler, (unsigned long)device);
			mod_timer(&flash->flash_data.flash_expire_timer, jiffies +  usecs_to_jiffies(flash->flash_data.firing_time_us));
		} else {
			if (flash->flash_data.flash_expire_timer.data) {
				del_timer(&flash->flash_data.flash_expire_timer);
				flash->flash_data.flash_expire_timer.data = (unsigned long)NULL;
			}
		}
	}

p_err:
	return ret;
}

int fimc_is_sensor_peri_notify_actuator(struct v4l2_subdev *subdev, void *arg)
{
	int ret = 0;
	u32 frame_index;
	struct fimc_is_module_enum *module = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;
	struct fimc_is_actuator_interface *actuator_itf = NULL;

	FIMC_BUG(!subdev);
	FIMC_BUG(!arg);

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev);
	if (unlikely(!module)) {
		err("%s, module in is NULL", __func__);
		ret = -EINVAL;
		goto p_err;
	}

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;
	if (unlikely(!sensor_peri)) {
		err("%s, sensor_peri is NULL", __func__);
		ret = -EINVAL;
		goto p_err;
	}

	if (!test_bit(FIMC_IS_SENSOR_ACTUATOR_AVAILABLE, &sensor_peri->peri_state)) {
		dbg_sensor(1, "%s: FIMC_IS_SENSOR_ACTUATOR_NOT_AVAILABLE\n", __func__);
		goto p_err;
	}

	actuator_itf = &sensor_peri->sensor_interface.actuator_itf;

	/* Set expecting actuator position */
	frame_index = (*(u32 *)arg + 1) % EXPECT_DM_NUM;
	sensor_peri->cis.expecting_lens_udm[frame_index].pos = actuator_itf->virtual_pos;

	dbg_actuator("%s: expexting frame cnt(%d), algorithm position(%d)\n",
			__func__, (*(u32 *)arg + 1), actuator_itf->virtual_pos);

p_err:

	return ret;
}

int fimc_is_sensor_peri_notify_vsync(struct v4l2_subdev *subdev, void *arg)
{
	int ret = 0;
	u32 vsync_count = 0;
	struct fimc_is_cis *cis = NULL;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

#ifdef USE_CAMERA_MIPI_CLOCK_VARIATION_RUNTIME
	struct fimc_is_flash *flash = NULL;
	bool do_mipi_clock_change_work = true;
#endif

#ifdef USE_CAMERA_FACTORY_DRAM_TEST
	struct fimc_is_device_sensor *device;
#endif

	FIMC_BUG(!subdev);
	FIMC_BUG(!arg);

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev);
	if (unlikely(!module)) {
		err("%s, module in is NULL", __func__);
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	vsync_count = *(u32 *)arg;

	cis = (struct fimc_is_cis *)v4l2_get_subdevdata(sensor_peri->subdev_cis);

	cis->cis_data->sen_vsync_count = vsync_count;

	if (sensor_peri->sensor_task != NULL
		|| sensor_peri->use_sensor_work) {
		/* run sensor setting thread */
		kthread_queue_work(&sensor_peri->sensor_worker, &sensor_peri->sensor_work);
	}

	if (sensor_peri->subdev_flash != NULL) {
	    ret = fimc_is_sensor_peri_notify_flash_fire(subdev, arg);
	    if (unlikely(ret < 0))
		err("err!!!(%s), notify flash fire fail(%d)", __func__, ret);
	}

	if (test_bit(FIMC_IS_SENSOR_ACTUATOR_AVAILABLE, &sensor_peri->peri_state)) {
		/* M2M case */
		if (sensor_peri->sensor_interface.otf_flag_3aa == false) {
			if (sensor_peri->actuator->valid_flag == 1)
				do_gettimeofday(&sensor_peri->actuator->start_time);

			ret = fimc_is_actuator_notify_m2m_actuator(subdev);
			if (ret)
				err("err!!!(%s), sensor notify M2M actuator fail(%d)", __func__, ret);
		}
	}

	/* Sensor Long Term Exposure mode(LTE mode) set */
	if (cis->long_term_mode.sen_strm_off_on_enable && cis->lte_work_enable) {
		if ((cis->long_term_mode.frame_interval == cis->long_term_mode.frm_num_strm_off_on_interval) ||
				(cis->long_term_mode.frame_interval <= 0)) {
			schedule_work(&sensor_peri->cis.long_term_mode_work);
		}
		if (cis->long_term_mode.frame_interval > 0)
			cis->long_term_mode.frame_interval--;
	}

#ifdef USE_CAMERA_MIPI_CLOCK_VARIATION_RUNTIME
	if (cis->long_term_mode.sen_strm_off_on_enable)
		do_mipi_clock_change_work = false;

	flash = sensor_peri->flash;

	if (sensor_peri->subdev_flash && flash) {
		if (flash->flash_ae.frm_num_pre_fls != 0)
			do_mipi_clock_change_work = false;

		if (flash->flash_ae.frm_num_main_fls[flash->flash_ae.main_fls_strm_on_off_step] != 0)
			do_mipi_clock_change_work = false;
	}

	if (cis->mipi_clock_index_new != cis->mipi_clock_index_cur && do_mipi_clock_change_work) {
		schedule_work(&sensor_peri->cis.mipi_clock_change_work);
	}
#endif

#ifdef USE_CAMERA_FACTORY_DRAM_TEST
	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_cis);
	WARN_ON(!device);

	if (device->cfg->ex_mode == EX_DRAMTEST) {
		info("FRS DRAMTEST checking... %d\n", device->fcount);

		/* check 8 frame (section 1) -> check 8 frame (section 2) */
		if ((cis->factory_dramtest_section2_fcount > 0)
			&& (cis->factory_dramtest_section2_fcount - 1 == device->fcount)) {
			info("FRS DRAMTEST will check section 2\n");
			schedule_work(&sensor_peri->cis.factory_dramtest_work);
		}
	}
#endif

p_err:
	return ret;
}

#define cal_dur_time(st, ed) ((ed.tv_sec - st.tv_sec) + (ed.tv_usec - st.tv_usec))
int fimc_is_sensor_peri_notify_vblank(struct v4l2_subdev *subdev, void *arg)
{
	int ret = 0;
	struct fimc_is_module_enum *module = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;
	struct fimc_is_actuator *actuator = NULL;

	FIMC_BUG(!subdev);
	FIMC_BUG(!arg);

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev);
	if (unlikely(!module)) {
		err("%s, module is NULL", __func__);
		return -EINVAL;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;
	if (unlikely(!sensor_peri)) {
		err("%s, sensor_peri is NULL", __func__);
		return -EINVAL;
	}
	actuator = sensor_peri->actuator;

	if (test_bit(FIMC_IS_SENSOR_ACTUATOR_AVAILABLE, &sensor_peri->peri_state)) {
		/* M2M case */
		if (sensor_peri->sensor_interface.otf_flag_3aa == false) {
			/* valid_time is calculated at once */
			if (actuator->valid_flag == 1) {
				actuator->valid_flag = 0;

				do_gettimeofday(&actuator->end_time);
				actuator->valid_time = cal_dur_time(actuator->start_time, actuator->end_time);
			}
		}

		ret = fimc_is_sensor_peri_notify_actuator(subdev, arg);
		if (ret < 0) {
			err("%s, notify_actuator is NULL", __func__);
			return -EINVAL;
		}
	}

	return ret;
}

int fimc_is_sensor_peri_notify_flash_fire(struct v4l2_subdev *subdev, void *arg)
{
	int ret = 0;
	u32 vsync_count = 0;
	struct fimc_is_module_enum *module = NULL;
	struct fimc_is_flash *flash = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!subdev);
	FIMC_BUG(!arg);

	vsync_count = *(u32 *)arg;

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev);
	FIMC_BUG(!module);

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	flash = sensor_peri->flash;
	FIMC_BUG(!flash);

	dbg_flash("[%s](%d), notify flash mode(%d), pow(%d), time(%d), pre-num(%d), main_num(%d)\n",
		__func__, vsync_count,
		flash->flash_data.mode,
		flash->flash_data.intensity,
		flash->flash_data.firing_time_us,
		flash->flash_ae.frm_num_pre_fls,
		flash->flash_ae.frm_num_main_fls[flash->flash_ae.main_fls_strm_on_off_step]);


	if (flash->flash_ae.frm_num_pre_fls != 0) {
		dbg_flash("[%s](%d), pre-flash schedule\n", __func__, vsync_count);

		schedule_work(&sensor_peri->flash->flash_data.flash_fire_work);
	}

	if (flash->flash_ae.frm_num_main_fls[flash->flash_ae.main_fls_strm_on_off_step] != 0) {
		if (flash->flash_ae.frm_num_main_fls[flash->flash_ae.main_fls_strm_on_off_step] == vsync_count) {
			dbg_flash("[%s](%d), main-flash schedule\n", __func__, vsync_count);

			schedule_work(&sensor_peri->flash->flash_data.flash_fire_work);
		}
	}

	return ret;
}

int fimc_is_sensor_peri_notify_actuator_init(struct v4l2_subdev *subdev)
{
	int ret = 0;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!subdev);

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev);
	if (!module) {
		err("%s, module is NULL", __func__);
		ret = -EINVAL;
			goto p_err;
	}

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	if (test_bit(FIMC_IS_SENSOR_ACTUATOR_AVAILABLE, &sensor_peri->peri_state) &&
		(sensor_peri->actuator->actuator_data.actuator_init)) {
		ret = v4l2_subdev_call(sensor_peri->subdev_actuator, core, init, 0);
		if (ret)
			warn("Actuator init fail\n");

		sensor_peri->actuator->actuator_data.actuator_init = false;
	}

p_err:
	return ret;
}

int fimc_is_sensor_peri_pre_flash_fire(struct v4l2_subdev *subdev, void *arg)
{
	int ret = 0;
	u32 vsync_count = 0;
	struct fimc_is_module_enum *module = NULL;
	struct fimc_is_flash *flash = NULL;
	struct fimc_is_sensor_ctl *sensor_ctl = NULL;
	camera2_flash_uctl_t *flash_uctl = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!subdev);
	FIMC_BUG(!arg);

	vsync_count = *(u32 *)arg;

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev);
	FIMC_BUG(!module);

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	flash = sensor_peri->flash;
	FIMC_BUG(!flash);

	mutex_lock(&sensor_peri->cis.control_lock);

	sensor_ctl = &sensor_peri->cis.sensor_ctls[vsync_count % CAM2P0_UCTL_LIST_SIZE];

	if ((sensor_ctl->valid_flash_udctrl == false)
		|| (vsync_count != sensor_ctl->flash_frame_number))
		goto p_err;

	flash_uctl = &sensor_ctl->cur_cam20_flash_udctrl;

	if ((flash_uctl->flashMode != flash->flash_data.mode) ||
		(flash_uctl->flashMode != CAM2_FLASH_MODE_OFF && flash_uctl->firingPower == 0)) {
		flash->flash_data.mode = flash_uctl->flashMode;
		flash->flash_data.intensity = flash_uctl->firingPower;
		flash->flash_data.firing_time_us = flash_uctl->firingTime;

		info("[%s](%d) pre-flash mode(%d), pow(%d), time(%d)\n", __func__,
			vsync_count, flash->flash_data.mode,
			flash->flash_data.intensity, flash->flash_data.firing_time_us);
		ret = fimc_is_sensor_flash_fire(sensor_peri, flash->flash_data.intensity);
	}

	/* HACK: reset uctl */
	flash_uctl->flashMode = 0;
	flash_uctl->firingPower = 0;
	flash_uctl->firingTime = 0;
	sensor_ctl->flash_frame_number = 0;
	sensor_ctl->valid_flash_udctrl = false;

p_err:
	mutex_unlock(&sensor_peri->cis.control_lock);
	return ret;
}

void fimc_is_sensor_peri_m2m_actuator(struct work_struct *data)
{
	int ret = 0;
	int index;
	struct fimc_is_device_sensor *device;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct fimc_is_actuator_interface *actuator_itf;
	struct fimc_is_actuator *actuator;
	struct fimc_is_actuator_data *actuator_data;
	u32 pre_position, request_frame_cnt;
	u32 cur_frame_cnt;
	u32 i;

	actuator_data = container_of(data, struct fimc_is_actuator_data, actuator_work);
	FIMC_BUG_VOID(!actuator_data);

	actuator = container_of(actuator_data, struct fimc_is_actuator, actuator_data);
	FIMC_BUG_VOID(!actuator);

	sensor_peri = actuator->sensor_peri;
	FIMC_BUG_VOID(!sensor_peri);

	device = v4l2_get_subdev_hostdata(sensor_peri->subdev_actuator);
	FIMC_BUG_VOID(!device);

	actuator_itf = &sensor_peri->sensor_interface.actuator_itf;

	cur_frame_cnt = device->ischain->group_3aa.fcount;
	request_frame_cnt = sensor_peri->actuator->pre_frame_cnt[0];
	pre_position = sensor_peri->actuator->pre_position[0];
	index = sensor_peri->actuator->actuator_index;

	for (i = 0; i < index; i++) {
		sensor_peri->actuator->pre_position[i] = sensor_peri->actuator->pre_position[i+1];
		sensor_peri->actuator->pre_frame_cnt[i] = sensor_peri->actuator->pre_frame_cnt[i+1];
	}

	/* After moving index, latest value change is Zero */
	sensor_peri->actuator->pre_position[index] = 0;
	sensor_peri->actuator->pre_frame_cnt[index] = 0;

	sensor_peri->actuator->actuator_index --;
	index = sensor_peri->actuator->actuator_index;

	if (cur_frame_cnt != request_frame_cnt)
		warn("AF frame count is not match (AF request count : %d, setting request count : %d\n",
				request_frame_cnt, cur_frame_cnt);

	ret = fimc_is_actuator_ctl_set_position(device, pre_position);
	if (ret < 0) {
		err("err!!! ret(%d), invalid position(%d)",
				ret, pre_position);
	}
	actuator_itf->hw_pos = pre_position;

	dbg_sensor(1, "%s: pre_frame_count(%d), pre_position(%d), cur_frame_cnt (%d), index(%d)\n",
			__func__,
			request_frame_cnt,
			pre_position,
			cur_frame_cnt,
			index);
}

void fimc_is_sensor_long_term_mode_set_work(struct work_struct *data)
{
	int ret = 0;
	int i = 0;
	struct fimc_is_cis *cis = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct v4l2_subdev *subdev_cis;
	struct fimc_is_device_sensor *device;
	struct ae_param expo, dgain, again;
	struct fimc_is_cis_ops *cis_ops = NULL;
	u32 tgain[EXPOSURE_GAIN_MAX];
	u32 step = 0;
	u32 frame_duration = 0;

	FIMC_BUG_VOID(!data);

	cis = container_of(data, struct fimc_is_cis, long_term_mode_work);
	FIMC_BUG_VOID(!cis);
	FIMC_BUG_VOID(!cis->cis_data);

	sensor_peri = container_of(cis, struct fimc_is_device_sensor_peri, cis);
	FIMC_BUG_VOID(!sensor_peri);

	subdev_cis = sensor_peri->subdev_cis;
	if (!subdev_cis) {
		err("[%s]: no subdev_cis", __func__);
		ret = -ENXIO;
		return;
	}

	device = v4l2_get_subdev_hostdata(subdev_cis);
	FIMC_BUG_VOID(!device);

	info("[%s] start\n", __func__);
	/* Sensor stream off */
	ret = CALL_CISOPS(cis, cis_stream_off, subdev_cis);
	if (ret < 0) {
		err("[%s] stream off fail\n", __func__);
		return;
	}

	ret = CALL_CISOPS(cis, cis_wait_streamoff, subdev_cis);
	if (ret < 0) {
		err("[%s] stream off fail\n", __func__);
		return;
	}

	/* Preprocessor stream off */
	if (sensor_peri->subdev_preprocessor) {
		ret = CALL_PREPROPOPS(sensor_peri->preprocessor, preprocessor_stream_off,
				sensor_peri->subdev_preprocessor);
		if (ret) {
			err("[%s] preprocessor stream off fail\n", __func__);
			return;
		}
	}
	dbg_sensor(1, "[%s] stream off done\n", __func__);

	step = cis->long_term_mode.sen_strm_off_on_step;
	if (step >= 1)
		cis->long_term_mode.sen_strm_off_on_enable = 0;

	/* LTE mode setting */
	ret = CALL_CISOPS(cis, cis_set_long_term_exposure, subdev_cis);
	if (ret < 0) {
		err("[%s] long term exposure set fail\n", __func__);
		return;
	}

	/* Preprocessor lemode setting */
	if (sensor_peri->subdev_preprocessor) {
		ret = CALL_PREPROPOPS(sensor_peri->preprocessor, preprocessor_set_le_mode,
				sensor_peri->subdev_preprocessor, &cis->long_term_mode.lemode_set);
		if (ret) {
			err("[%s] preprocessor stream off fail\n", __func__);
			return;
		}
	}

	expo.val = expo.short_val = expo.middle_val = cis->long_term_mode.expo[step];
	again.val = again.short_val = again.middle_val = cis->long_term_mode.again[step];
	dgain.val = dgain.short_val = dgain.middle_val = cis->long_term_mode.dgain[step];
	tgain[0] = tgain[1] = tgain[2] = cis->long_term_mode.tgain[step];

	CALL_CISOPS(&sensor_peri->cis, cis_adjust_frame_duration, sensor_peri->subdev_cis,
			cis->long_term_mode.expo[step], &frame_duration);
	fimc_is_sensor_peri_s_frame_duration(device, frame_duration);

	cis_ops = (struct fimc_is_cis_ops *)sensor_peri->cis.cis_ops;
	if(cis_ops->cis_set_exposure_time
		&& cis_ops->cis_set_analog_gain
		&& cis_ops->cis_set_digital_gain) {
		fimc_is_sensor_peri_s_analog_gain(device, again);
		fimc_is_sensor_peri_s_digital_gain(device, dgain);
		fimc_is_sensor_peri_s_exposure_time(device, expo);
	}else {
		fimc_is_sensor_peri_s_totalgain(device, expo, again, dgain);
	}

	sensor_peri->sensor_interface.cis_itf_ops.request_reset_expo_gain(&sensor_peri->sensor_interface,
			EXPOSURE_GAIN_COUNT_3,
			&expo.val,
			tgain,
			&again.val,
			&dgain.val);

	step = cis->long_term_mode.sen_strm_off_on_step++;

	/* Preprocessor stream on */
	if (sensor_peri->subdev_preprocessor) {
		ret = CALL_PREPROPOPS(sensor_peri->preprocessor, preprocessor_stream_on,
				sensor_peri->subdev_preprocessor);
		if (ret) {
			err("[%s] preprocessor stream on fail\n", __func__);
			return;
		}
	}

	/* Sensor stream on */
	ret = CALL_CISOPS(cis, cis_stream_on, subdev_cis);
	if (ret < 0) {
		err("[%s] stream off fail\n", __func__);
		return;
	}
	dbg_sensor(1, "[%s] stream on done\n", __func__);

	/* Reset when step value is 2 */
	if (step >= 1) {
		for (i = 0; i < 2; i++) {
			cis->long_term_mode.expo[i] = 0;
			cis->long_term_mode.tgain[i] = 0;
			cis->long_term_mode.again[i] = 0;
			cis->long_term_mode.dgain[i] = 0;
			cis->long_term_mode.sen_strm_off_on_step = 0;
			cis->long_term_mode.frm_num_strm_off_on_interval = 0;
		}
	} else {
		cis->long_term_mode.lemode_set.lemode = 0;
	}

	info("[%s] end\n", __func__);
}

#ifdef USE_CAMERA_MIPI_CLOCK_VARIATION_RUNTIME
void fimc_is_sensor_mipi_clock_change_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_cis *cis = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct v4l2_subdev *subdev_cis;

	FIMC_BUG_VOID(!data);

	cis = container_of(data, struct fimc_is_cis, mipi_clock_change_work);

	FIMC_BUG_VOID(!cis);

	sensor_peri = container_of(cis, struct fimc_is_device_sensor_peri, cis);
	FIMC_BUG_VOID(!sensor_peri);

	subdev_cis = sensor_peri->subdev_cis;
	if (!subdev_cis) {
		err("[%s]: no subdev_cis", __func__);
		return;
	}

	info("[%s] start\n", __func__);
	/* Sensor stream off */
	ret = CALL_CISOPS(cis, cis_stream_off, subdev_cis);
	if (ret < 0) {
		err("[%s] stream off fail\n", __func__);
		return;
	}

	/* Sensor stream on */
	ret = CALL_CISOPS(cis, cis_stream_on, subdev_cis);
	if (ret < 0) {
		err("[%s] stream off fail\n", __func__);
		return;
	}
	dbg_sensor(1, "[%s] stream on done\n", __func__);
	info("[%s] end\n", __func__);
}
#endif

#ifdef USE_CAMERA_FACTORY_DRAM_TEST
void fimc_is_sensor_factory_dramtest_work(struct work_struct *data)
{
	int ret = 0;
	struct fimc_is_cis *cis = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct v4l2_subdev *subdev_cis;

	WARN_ON(!data);

	cis = container_of(data, struct fimc_is_cis, factory_dramtest_work);

	WARN_ON(!cis);

	sensor_peri = container_of(cis, struct fimc_is_device_sensor_peri, cis);
	WARN_ON(!sensor_peri);

	subdev_cis = sensor_peri->subdev_cis;
	if (!subdev_cis) {
		err("[%s]: no subdev_cis", __func__);
		return;
	}

	ret = CALL_CISOPS(cis, cis_set_frs_control, subdev_cis, FRS_DRAM_TEST_SECTION2);
	if (ret < 0) {
		err("[%s] cis_set_frs_control fail\n", __func__);
	}
}
#endif


void fimc_is_sensor_peri_init_work(struct fimc_is_device_sensor_peri *sensor_peri)
{
	FIMC_BUG_VOID(!sensor_peri);

	if (sensor_peri->flash) {
		INIT_WORK(&sensor_peri->flash->flash_data.flash_fire_work, fimc_is_sensor_flash_fire_work);
		INIT_WORK(&sensor_peri->flash->flash_data.flash_expire_work, fimc_is_sensor_flash_expire_work);
	}

	INIT_WORK(&sensor_peri->cis.cis_status_dump_work, fimc_is_sensor_cis_status_dump_work);

	if (sensor_peri->actuator) {
		INIT_WORK(&sensor_peri->actuator->actuator_data.actuator_work, fimc_is_sensor_peri_m2m_actuator);
		hrtimer_init(&sensor_peri->actuator->actuator_data.afwindow_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	}

	/* Init to LTE mode work */
	INIT_WORK(&sensor_peri->cis.long_term_mode_work, fimc_is_sensor_long_term_mode_set_work);
#ifdef USE_CAMERA_MIPI_CLOCK_VARIATION_RUNTIME
	INIT_WORK(&sensor_peri->cis.mipi_clock_change_work, fimc_is_sensor_mipi_clock_change_work);
#endif
#ifdef USE_CAMERA_FACTORY_DRAM_TEST
	INIT_WORK(&sensor_peri->cis.factory_dramtest_work, fimc_is_sensor_factory_dramtest_work);
#endif

	if (sensor_peri->mcu && sensor_peri->mcu->aperture) {
		INIT_WORK(&sensor_peri->mcu->aperture->aperture_set_start_work, fimc_is_sensor_aperture_set_start_work);
		INIT_WORK(&sensor_peri->mcu->aperture->aperture_set_work, fimc_is_sensor_aperture_set_work);
	}
}

void fimc_is_sensor_peri_probe(struct fimc_is_device_sensor_peri *sensor_peri)
{
	FIMC_BUG_VOID(!sensor_peri);

	clear_bit(FIMC_IS_SENSOR_ACTUATOR_AVAILABLE, &sensor_peri->peri_state);
	clear_bit(FIMC_IS_SENSOR_FLASH_AVAILABLE, &sensor_peri->peri_state);
	clear_bit(FIMC_IS_SENSOR_PREPROCESSOR_AVAILABLE, &sensor_peri->peri_state);
	clear_bit(FIMC_IS_SENSOR_OIS_AVAILABLE, &sensor_peri->peri_state);
	clear_bit(FIMC_IS_SENSOR_APERTURE_AVAILABLE, &sensor_peri->peri_state);
	clear_bit(FIMC_IS_SENSOR_PDP_AVAILABLE, &sensor_peri->peri_state);

	mutex_init(&sensor_peri->cis.control_lock);
}

int fimc_is_sensor_peri_s_stream(struct fimc_is_device_sensor *device,
					bool on)
{
	int ret = 0;
	int i = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;
	struct v4l2_subdev *subdev_cis = NULL;
	struct v4l2_subdev *subdev_preprocessor = NULL;
	struct fimc_is_cis *cis = NULL;
	struct fimc_is_preprocessor *preprocessor = NULL;
	struct fimc_is_core *core = NULL;
	struct fimc_is_dual_info *dual_info = NULL;

	FIMC_BUG(!device);

	core = (struct fimc_is_core *)device->private_data;
	dual_info = &core->dual_info;

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		return -EINVAL;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		return -EINVAL;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	subdev_cis = sensor_peri->subdev_cis;
	if (!subdev_cis) {
		err("[SEN:%d] no subdev_cis(s_stream, on:%d)", module->sensor_id, on);
		return -ENXIO;
	}
	cis = (struct fimc_is_cis *)v4l2_get_subdevdata(subdev_cis);
	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	//if (sensor_peri->aperture)
		//mutex_lock(&sensor_peri->aperture->control_lock);

	subdev_preprocessor = sensor_peri->subdev_preprocessor;
	if (subdev_preprocessor) {
		preprocessor = (struct fimc_is_preprocessor *)v4l2_get_subdevdata(subdev_preprocessor);
		FIMC_BUG(!preprocessor);
	}

	ret = fimc_is_sensor_peri_debug_fixed((struct fimc_is_device_sensor *)v4l2_get_subdev_hostdata(subdev_module));
	if (ret) {
		err("fimc_is_sensor_peri_debug_fixed is fail(%d)", ret);
		goto p_err;
	}

	if (on) {
		fimc_is_sensor_init_expecting_dm(device, cis);

		/* If sensor setting @work is queued or executing,
		   wait for it to finish execution when working s_format */
		kthread_flush_work(&sensor_peri->mode_change_work);

		/* just for auto dual camera mode to reduce power consumption */
#ifdef USE_OIS_SLEEP_MODE
		if (sensor_peri->ois)
			fimc_is_sensor_ois_start((struct fimc_is_device_sensor *)v4l2_get_subdev_hostdata(subdev_module));
#endif

/* For dual camera project to  reduce power consumption of ois */
#ifndef CONFIG_CAMERA_USE_MCU
#ifdef CAMERA_REAR2_OIS
		if (sensor_peri->mcu && sensor_peri->mcu->ois) {
			ret = CALL_OISOPS(sensor_peri->mcu->ois, ois_set_power_mode, sensor_peri->subdev_mcu);
			if (ret < 0)
				err("v4l2_subdev_call(ois_set_power_mode) is fail(%d)", ret);
		}
#endif
#endif
		/* set aperture as start value */
		if (sensor_peri->mcu && sensor_peri->mcu->aperture
			&& (sensor_peri->mcu->aperture->start_value != sensor_peri->mcu->aperture->cur_value)) {
#ifndef CONFIG_CAMERA_USE_MCU
			flush_work(&sensor_peri->ois->ois_set_init_work);
#endif
			schedule_work(&sensor_peri->mcu->aperture->aperture_set_start_work);
		} else {
			if (sensor_peri->mcu && sensor_peri->mcu->ois) {
				mutex_lock(&core->ois_mode_lock);
				ret = CALL_OISOPS(sensor_peri->mcu->ois, ois_set_mode, sensor_peri->subdev_mcu,
					sensor_peri->mcu->ois->ois_mode);
				if (ret < 0)
					err("v4l2_subdev_call(ois_set_mode) is fail(%d)", ret);
				mutex_unlock(&core->ois_mode_lock);
			}
		}

#ifdef USE_AF_SLEEP_MODE
		if (sensor_peri->actuator && sensor_peri->actuator->actuator_ops) {
			ret = CALL_ACTUATOROPS(sensor_peri->actuator, set_active, sensor_peri->subdev_actuator, 1);
			if (ret) {
				err("[SEN:%d] actuator set active fail\n", module->sensor_id);
				goto p_err;
			}
		}
#endif
		/* stream on sequence */
		if (cis->need_mode_change == false && cis->use_initial_ae == false) {
			/* only first time after camera on */
			fimc_is_sensor_initial_setting_low_exposure(sensor_peri);
			cis->need_mode_change = true;
		} else {
			fimc_is_sensor_setting_mode_change(sensor_peri);
		}

		if (subdev_preprocessor) {
			ret = CALL_PREPROPOPS(preprocessor, preprocessor_wait_s_input, subdev_preprocessor);
			if (ret) {
				err("[SEN:%d] preprocessor wait s_input timeout\n", module->sensor_id);
				goto p_err;
			}

			/* Before stream on preprocessor, do stream off and mode change */
			ret = CALL_PREPROPOPS(preprocessor, preprocessor_stream_off, subdev_preprocessor);
			if (ret) {
				err("[SEN:%d] v4l2_subdev_call(preprocessor_stream, off:%d) is fail(%d)",
						module->sensor_id, on, ret);
				goto p_err;
			}

			ret = CALL_PREPROPOPS(preprocessor, preprocessor_mode_change, subdev_preprocessor, device);
			if (ret) {
				err("[SEN:%d] v4l2_subdev_call(preprocessor_mode_change) is fail(%d)",
						module->sensor_id, ret);
				goto p_err;
			}

			ret = CALL_PREPROPOPS(preprocessor, preprocessor_stream_on, subdev_preprocessor);
			if (ret) {
				err("[SEN:%d] v4l2_subdev_call(preprocessor_stream, on:%d) is fail(%d)",
						module->sensor_id, on, ret);
				goto p_err;
			}
		}

		if (sensor_peri->mcu) {
			if (sensor_peri->mcu->aperture
				&& (sensor_peri->mcu->aperture->start_value != sensor_peri->mcu->aperture->cur_value)) {
				flush_work(&sensor_peri->mcu->aperture->aperture_set_start_work);
			}
		}

		ret = CALL_CISOPS(cis, cis_stream_on, subdev_cis);
		if (ret < 0) {
			err("[%s]: sensor stream on fail\n", __func__);
		} else {
			ret = CALL_CISOPS(cis, cis_wait_streamon, subdev_cis);
			if (ret < 0) {
				err("[%s]: sensor wait stream on fail\n", __func__);
			}
		}
	} else {
		/* stream off sequence */
		mutex_lock(&cis->control_lock);
		ret = CALL_CISOPS(cis, cis_stream_off, subdev_cis);
		if (ret == 0)
			ret = CALL_CISOPS(cis, cis_wait_streamoff, subdev_cis);

		if (cis->long_term_mode.sen_strm_off_on_enable) {
			cis->long_term_mode.sen_strm_off_on_enable = 0;
			ret = CALL_CISOPS(cis, cis_set_long_term_exposure, subdev_cis);
			info("[%s] stopped long_exp_capture mode\n", __func__);

			for (i = 0; i < 2; i++) {
				cis->long_term_mode.expo[i] = 0;
				cis->long_term_mode.tgain[i] = 0;
				cis->long_term_mode.again[i] = 0;
				cis->long_term_mode.dgain[i] = 0;
			}
			cis->long_term_mode.sen_strm_off_on_step = 0;
			cis->long_term_mode.frm_num_strm_off_on_interval = 0;
			cis->long_term_mode.lemode_set.lemode = 0;
		}

		mutex_unlock(&cis->control_lock);

#ifdef USE_OIS_SLEEP_MODE
		if (sensor_peri->ois)
			fimc_is_sensor_ois_stop((struct fimc_is_device_sensor *)v4l2_get_subdev_hostdata(subdev_module));
#endif

#ifdef USE_AF_SLEEP_MODE
		if (sensor_peri->actuator && sensor_peri->actuator->actuator_ops
			&& (dual_info->mode != FIMC_IS_DUAL_MODE_NOTHING)) {
			ret = CALL_ACTUATOROPS(sensor_peri->actuator, set_active, sensor_peri->subdev_actuator, 0);
			if (ret) {
				err("[SEN:%d] actuator set sleep fail\n", module->sensor_id);
				goto p_err;
			}
		}
#endif

		if (sensor_peri->flash != NULL && dual_info->mode == FIMC_IS_DUAL_MODE_NOTHING) {
			mutex_lock(&cis->control_lock);
			sensor_peri->flash->flash_data.mode = CAM2_FLASH_MODE_OFF;
			if (sensor_peri->flash->flash_data.flash_fired == true) {
				ret = fimc_is_sensor_flash_fire(sensor_peri, 0);
				if (ret) {
					err("failed to turn off flash at flash expired handler\n");
				}
#if defined(CONFIG_LEDS_S2MU106_FLASH)
				pdo_ctrl_by_flash(0);
				muic_afc_set_voltage(9);
				info("[%s]%d Down Volatge set Clear \n" ,__func__,__LINE__);
#endif
			}
			mutex_unlock(&cis->control_lock);
		}

		if (subdev_preprocessor){
			ret = CALL_PREPROPOPS(preprocessor, preprocessor_stream_off, subdev_preprocessor);
			if (ret) {
				err("[SEN:%d] v4l2_subdev_call(preprocessor_stream, off:%d) is fail(%d)",
						module->sensor_id, on, ret);
				goto p_err;
			}
		}
		memset(&sensor_peri->cis.cur_sensor_uctrl, 0, sizeof(camera2_sensor_uctl_t));
		memset(&sensor_peri->cis.expecting_sensor_dm[0], 0, sizeof(camera2_sensor_dm_t) * EXPECT_DM_NUM);
		memset(&sensor_peri->cis.expecting_sensor_udm[0], 0, sizeof(camera2_sensor_udm_t) * EXPECT_DM_NUM);
		for (i = 0; i < CAM2P0_UCTL_LIST_SIZE; i++) {
			memset(&sensor_peri->cis.sensor_ctls[i].cur_cam20_sensor_udctrl, 0, sizeof(camera2_sensor_uctl_t));
			sensor_peri->cis.sensor_ctls[i].valid_sensor_ctrl = 0;
			sensor_peri->cis.sensor_ctls[i].force_update = false;
			memset(&sensor_peri->cis.sensor_ctls[i].cur_cam20_flash_udctrl, 0, sizeof(camera2_flash_uctl_t));
			sensor_peri->cis.sensor_ctls[i].valid_flash_udctrl = false;

			memset(&sensor_peri->cis.sensor_ctls[i].roi_control, 0, sizeof(struct roi_setting_t));
			memset(&sensor_peri->cis.sensor_ctls[i].lsi_stat_control, 0,
					sizeof(struct sensor_lsi_3hdr_stat_control_per_frame));
			memset(&sensor_peri->cis.sensor_ctls[i].imx_stat_control, 0,
					sizeof(struct sensor_imx_3hdr_stat_control_per_frame));
			memset(&sensor_peri->cis.sensor_ctls[i].imx_tone_control, 0,
					sizeof(struct sensor_imx_3hdr_tone_control));
			memset(&sensor_peri->cis.sensor_ctls[i].imx_ev_control, 0,
					sizeof(struct sensor_imx_3hdr_ev_control));
		}
		sensor_peri->cis.sensor_stats = false;
		memset(&sensor_peri->cis.imx_sensor_stats, 0,
				sizeof(struct sensor_imx_3hdr_stat_control_mode_change));
		memset(&sensor_peri->cis.lsi_sensor_stats, 0,
				sizeof(struct sensor_lsi_3hdr_stat_control_mode_change));
		sensor_peri->cis.lsc_table_status = false;
		memset(&sensor_peri->cis.imx_lsc_table_3hdr, 0,
				sizeof(struct sensor_imx_3hdr_lsc_table_init));

		sensor_peri->use_sensor_work = false;
	}
	if (ret < 0) {
		err("[SEN:%d] v4l2_subdev_call(s_stream, on:%d) is fail(%d)",
				module->sensor_id, on, ret);
		goto p_err;
	}

#ifdef HACK_SDK_RESET
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;
	sensor_peri->sensor_interface.reset_flag = false;
#endif

p_err:
	//if (sensor_peri->aperture)
		//mutex_unlock(&sensor_peri->aperture->control_lock);

	return ret;
}

#ifdef SUPPORT_REMOSAIC_CROP_ZOOM
static int fimc_is_sensor_peri_crop_zoom(struct fimc_is_device_sensor *device,
					struct seamless_mode_change_info *mode_change)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;
	struct v4l2_subdev *subdev_paf;
	struct fimc_is_sensor_cfg *cfg;
	struct fimc_is_device_csi *csi;
	struct v4l2_subdev_format fmt;
	struct fimc_is_cis *cis;
	struct v4l2_subdev *sd;
	u32 __iomem *base_reg;
	u32 vc = 0;
	u32 lindex = 0;
	u32 hindex = 0;
	u32 indexes = 0;

	FIMC_BUG(!device);
	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;
#if defined(CONFIG_CAMERA_PDP)
	subdev_paf = sensor_peri->subdev_pdp;
#elif defined(CONFIG_CAMERA_PAFSTAT)
	subdev_paf = sensor_peri->subdev_pafstat;
#endif
	csi = (struct fimc_is_device_csi *)v4l2_get_subdevdata(device->subdev_csi);
	base_reg = csi->base_reg;

	sd = sensor_peri->subdev_cis;
	if (!sd) {
		err("[MOD:%s] no subdev_cis(set_fmt)", module->sensor_name);
		ret = -ENXIO;
		goto p_err;
	}
	cis = (struct fimc_is_cis *)v4l2_get_subdevdata(sd);
	FIMC_BUG(!cis);
	FIMC_BUG(!cis->cis_data);

	device->ex_mode = mode_change->ex_mode;
	device->image.framerate = mode_change->fps;
	device->image.window.width = mode_change->width;
	device->image.window.height = mode_change->height;
	clear_bit(FIMC_IS_SENSOR_S_CONFIG, &device->state);

	cfg = fimc_is_sensor_g_mode(device);
	device->cfg = cfg;
	if (!device->cfg) {
		merr("sensor cfg is invalid", device);
		goto p_err;
	}
	set_bit(FIMC_IS_SENSOR_S_CONFIG, &device->state);

	csi->sensor_cfg = cfg;
	cis->cis_data->sens_config_index_cur = cfg->mode;
	cis->cis_data->cur_width = cfg->width;
	cis->cis_data->cur_height = cfg->height;
	if (subdev_paf) {
		fmt.format.width = cfg->width;
		fmt.format.height = cfg->height;

		ret = v4l2_subdev_call(subdev_paf, pad, set_fmt, NULL, &fmt);
		if (ret) {
			err("[MOD:%s] PAF set_fmt is fail(%d)", module->sensor_name, ret);
			goto p_err;
		}
	}

	for (vc = CSI_VIRTUAL_CH_0; vc < CSI_VIRTUAL_CH_MAX; vc++) {
		csi_hw_s_config_crop_zoom(base_reg,
				vc, &cfg->input[vc],
				cfg->input[vc].width,
				cfg->input[vc].height);

		minfo("[CSI] VC%d: size(%dx%d)\n", csi, vc,
			cfg->input[vc].width, cfg->input[vc].height);
	}
	csi_hw_s_irq_msk(base_reg, true);
	csi_hw_enable(base_reg);

	/* update binning ratio for tetra:2 remosaic:1  */
	ret = fimc_is_ischain_s_sensor_size(device->ischain, NULL, &lindex, &hindex, &indexes);
	if (ret < 0) {
		err("err!!! fimc_is_ischain_s_sensor_size(%d)", ret);
		goto p_err;
	}

	ret = fimc_is_sensor_mode_change(cis, cfg->mode);
	if (ret < 0) {
		err("err!!! fimc_is_sensor_mode_change(%d)", ret);
		goto p_err;
	}

	ret = fimc_is_itf_s_param(device->ischain, NULL, lindex, hindex, indexes);
	if (ret < 0)
		err("err!!! fimc_is_itf_s_param(%d)", ret);
p_err:
	return ret;
}
#endif

#ifdef SUPPORT_SENSOR_SEAMLESS_3HDR
static int fimc_is_sensor_peri_s_3hdr_mode(struct fimc_is_device_sensor *device,
					struct seamless_mode_change_info *mode_change)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module = NULL;
	struct fimc_is_sensor_cfg *cfg = NULL;
	struct fimc_is_module_enum *module = NULL;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;
	struct fimc_is_cis *cis = NULL;
	u32 max_again = 0, max_dgain = 0;

	FIMC_BUG(!mode_change);
	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	FIMC_BUG(!subdev_module);

	module = v4l2_get_subdevdata(subdev_module);
	FIMC_BUG(!module);

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;
	FIMC_BUG(!sensor_peri);
	cis = &sensor_peri->cis;

	if (device->ex_mode == mode_change->ex_mode) {
		info("%s: already in %d exmode\n", __func__, mode_change->ex_mode);
		return 0;
	}

	if (cis->cis_data->cur_width != mode_change->width
	  || cis->cis_data->cur_height != mode_change->height
	  || device->image.framerate != mode_change->fps) {
		merr("%dx%d@%d -> %dx%d@%d not allowed", device,
			cis->cis_data->cur_width, cis->cis_data->cur_height, device->image.framerate,
			mode_change->width, mode_change->height, mode_change->fps);
	}

	device->cfg = NULL;
	device->ex_mode = mode_change->ex_mode;

	cfg = fimc_is_sensor_g_mode(device);
	device->cfg = cfg;
	if (!device->cfg) {
		merr("sensor cfg is invalid", device);
		ret = -EINVAL;
		goto p_err;
	}

	sensor_peri->cis.cis_data->sens_config_index_cur = device->cfg->mode;

	CALL_CISOPS(cis, cis_data_calculation, cis->subdev, device->cfg->mode);

	ret = CALL_CISOPS(cis, cis_mode_change, cis->subdev, device->cfg->mode);
	if (ret < 0)
		goto p_err;

	/* Update max again, dgain */
	CALL_CISOPS(cis, cis_get_max_analog_gain, cis->subdev, &max_again);
	CALL_CISOPS(cis, cis_get_max_digital_gain, cis->subdev, &max_dgain);
	info("%s: max again permile %d, max dgain permile %d\n", __func__, max_again, max_dgain);

p_err:
	return ret;
}
#endif

int fimc_is_sensor_peri_s_mode_change(struct fimc_is_device_sensor *device,
					struct seamless_mode_change_info *mode_change)
{
	int ret = 0;

	FIMC_BUG(!device);

	switch(mode_change->ex_mode) {
#ifdef SUPPORT_REMOSAIC_CROP_ZOOM
	case EX_CROP_ZOOM:
		ret = fimc_is_sensor_peri_crop_zoom(device, mode_change);
		break;
	case EX_NONE:
		if(device->ex_mode == EX_CROP_ZOOM)
			ret = fimc_is_sensor_peri_crop_zoom(device, mode_change);
		break;
#endif
#ifdef SUPPORT_SENSOR_SEAMLESS_3HDR
	case EX_3DHDR:
	case EX_SEAMLESS_TETRA:
		ret = fimc_is_sensor_peri_s_3hdr_mode(device, mode_change);
		break;
#endif
	default:
		err("err!!! Unknown mode(%#x)", device->ex_mode);
		ret = -EINVAL;
		goto p_err;
	}

p_err:
	return ret;
}

int fimc_is_sensor_peri_s_frame_duration(struct fimc_is_device_sensor *device,
					u32 frame_duration)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

#ifdef FIXED_SENSOR_DEBUG
	sysfs_sensor.max_fps = sensor_peri->cis.cis_data->max_fps;

	if (unlikely(sysfs_sensor.is_en == true) || unlikely(sysfs_sensor.is_fps_en == true)) {
		if (sysfs_sensor.set_fps < sysfs_sensor.max_fps) {
			sysfs_sensor.frame_duration = sysfs_sensor.set_fps;
		} else if (sysfs_sensor.frame_duration > sysfs_sensor.max_fps) {
			sysfs_sensor.frame_duration = sysfs_sensor.max_fps;
		}

		frame_duration = FPS_TO_DURATION_US(sysfs_sensor.frame_duration);
		dbg_sensor(1, "sysfs_sensor.frame_duration = %d\n", sysfs_sensor.frame_duration);
	} else
		sysfs_sensor.frame_duration = FPS_TO_DURATION_US(frame_duration);
#endif

	ret = CALL_CISOPS(&sensor_peri->cis, cis_set_frame_duration, sensor_peri->subdev_cis, frame_duration);
	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		goto p_err;
	}
	device->frame_duration = frame_duration;

p_err:
	return ret;
}

int fimc_is_sensor_peri_s_exposure_time(struct fimc_is_device_sensor *device,
	struct ae_param expo)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

#ifdef FIXED_SENSOR_DEBUG
	if (unlikely(sysfs_sensor.is_en == true)) {
		expo.long_val = sysfs_sensor.long_exposure_time;
		expo.short_val = sysfs_sensor.short_exposure_time;
		dbg_sensor(1, "exposure = %d %d\n", expo.long_val, expo.short_val);
	}
#endif

	ret = CALL_CISOPS(&sensor_peri->cis, cis_set_exposure_time, sensor_peri->subdev_cis, &expo);
	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		goto p_err;
	}

	device->exposure_time = expo.long_val;

p_err:
	return ret;
}

int fimc_is_sensor_peri_s_analog_gain(struct fimc_is_device_sensor *device,
	struct ae_param again)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

#ifdef FIXED_SENSOR_DEBUG
	if (unlikely(sysfs_sensor.is_en == true)) {
		again.long_val = sysfs_sensor.long_analog_gain * 10;
		again.short_val = sysfs_sensor.short_analog_gain * 10;
		dbg_sensor(1, "again = %d %d\n", sysfs_sensor.long_analog_gain, sysfs_sensor.short_analog_gain);
	}
#endif

	ret = CALL_CISOPS(&sensor_peri->cis, cis_set_analog_gain, sensor_peri->subdev_cis, &again);
	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		goto p_err;
	}
	/* 0: Previous input, 1: Current input */
	sensor_peri->cis.cis_data->analog_gain[0] = sensor_peri->cis.cis_data->analog_gain[1];
	sensor_peri->cis.cis_data->analog_gain[1] = again.long_val;

p_err:
	return ret;
}

int fimc_is_sensor_peri_s_digital_gain(struct fimc_is_device_sensor *device,
	struct ae_param dgain)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		ret = -EINVAL;
		goto p_err;
	}

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

#ifdef FIXED_SENSOR_DEBUG
	if (unlikely(sysfs_sensor.is_en == true)) {
		dgain.long_val = sysfs_sensor.long_digital_gain * 10;
		dgain.short_val = sysfs_sensor.short_digital_gain * 10;
		dbg_sensor(1, "dgain = %d %d\n", sysfs_sensor.long_digital_gain, sysfs_sensor.short_digital_gain);
	}
#endif

	ret = CALL_CISOPS(&sensor_peri->cis, cis_set_digital_gain, sensor_peri->subdev_cis, &dgain);
	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		goto p_err;
	}
	/* 0: Previous input, 1: Current input */
	sensor_peri->cis.cis_data->digital_gain[0] = sensor_peri->cis.cis_data->digital_gain[1];
	sensor_peri->cis.cis_data->digital_gain[1] = dgain.long_val;

p_err:
	return ret;
}

int fimc_is_sensor_peri_s_wb_gains(struct fimc_is_device_sensor *device,
		struct wb_gains wb_gains)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;

	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	BUG_ON(!device);
	BUG_ON(!device->subdev_module);

	subdev_module = device->subdev_module;

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	ret = CALL_CISOPS(&sensor_peri->cis, cis_set_wb_gains, sensor_peri->subdev_cis, wb_gains);
	if (ret < 0)
		err("failed to set wb gains(%d)", ret);

p_err:
	return ret;
}

int fimc_is_sensor_peri_s_sensor_stats(struct fimc_is_device_sensor *device,
		bool streaming,
		struct fimc_is_sensor_ctl *module_ctl,
		void *data)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;

	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	BUG_ON(!device);
	BUG_ON(!device->subdev_module);

	subdev_module = device->subdev_module;

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	if (streaming) {
		FIMC_BUG(!module_ctl);

		if (module_ctl->update_roi) {
			ret = CALL_CISOPS(&sensor_peri->cis, cis_set_roi_stat,
						sensor_peri->subdev_cis, module_ctl->roi_control);
			if (ret < 0)
				err("failed to set roi stat(%d)", ret);
		}

		if (module_ctl->update_3hdr_stat) {
			if (!strcmp(module->sensor_maker, "SLSI"))
				ret = CALL_CISOPS(&sensor_peri->cis, cis_set_3hdr_stat,
							sensor_peri->subdev_cis,
							streaming,
							(void *)&module_ctl->lsi_stat_control);
			else if (!strcmp(module->sensor_maker, "SONY"))
				ret = CALL_CISOPS(&sensor_peri->cis, cis_set_3hdr_stat,
							sensor_peri->subdev_cis,
							streaming,
							(void *)&module_ctl->imx_stat_control);
			if (ret < 0)
				err("failed to set 3hdr stat(%d)", ret);
		}

		if (module_ctl->update_tone) {
			ret = CALL_CISOPS(&sensor_peri->cis, cis_set_tone_stat,
						sensor_peri->subdev_cis, module_ctl->imx_tone_control);
			if (ret < 0)
				err("failed to set tone stat(%d)", ret);
		}

		if (module_ctl->update_ev) {
			ret = CALL_CISOPS(&sensor_peri->cis, cis_set_ev_stat,
						sensor_peri->subdev_cis, module_ctl->imx_ev_control);
			if (ret < 0)
				err("failed to set ev stat(%d)", ret);
		}
	} else {
		if (data) {
			if (!strcmp(module->sensor_maker, "SLSI")) {
				ret = CALL_CISOPS(&sensor_peri->cis, cis_set_3hdr_stat,
							sensor_peri->subdev_cis,
							streaming,
							(void *)&sensor_peri->cis.lsi_sensor_stats);
				if (ret < 0)
					err("failed to set 3hdr lsc init table(%d)", ret);
			} else if (!strcmp(module->sensor_maker, "SONY")) {
				if (sensor_peri->cis.lsc_table_status) {
					ret = CALL_CISOPS(&sensor_peri->cis, cis_init_3hdr_lsc_table,
								sensor_peri->subdev_cis,
								(void *)&sensor_peri->cis.imx_lsc_table_3hdr);
					if (ret < 0)
						err("failed to set 3hdr lsc init table(%d)", ret);
				}
				if (sensor_peri->cis.sensor_stats) {
					ret = CALL_CISOPS(&sensor_peri->cis, cis_set_3hdr_stat,
								sensor_peri->subdev_cis,
								streaming,
								(void *)&sensor_peri->cis.imx_sensor_stats);
					if (ret < 0)
						err("failed to set 3hdr stat(%d)", ret);
				}
			}
		}
	}
p_err:
	return ret;
}

int fimc_is_sensor_peri_adj_ctrl(struct fimc_is_device_sensor *device,
		u32 input,
		struct v4l2_control *ctrl)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;

	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);
	FIMC_BUG(!device->subdev_module);
	FIMC_BUG(!device->subdev_csi);
	FIMC_BUG(!ctrl);

	subdev_module = device->subdev_module;

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	switch (ctrl->id) {
	case V4L2_CID_SENSOR_ADJUST_FRAME_DURATION:
		ret = CALL_CISOPS(&sensor_peri->cis, cis_adjust_frame_duration, sensor_peri->subdev_cis, input, &ctrl->value);
		break;
	case V4L2_CID_SENSOR_ADJUST_ANALOG_GAIN:
		ret = CALL_CISOPS(&sensor_peri->cis, cis_adjust_analog_gain, sensor_peri->subdev_cis, input, &ctrl->value);
		break;
	default:
		err("err!!! Unknown CID(%#x)", ctrl->id);
		ret = -EINVAL;
		goto p_err;
	}

	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		ctrl->value = 0;
		goto p_err;
	}

p_err:
	return ret;
}

int fimc_is_sensor_peri_compensate_gain_for_ext_br(struct fimc_is_device_sensor *device,
				u32 expo, u32 *again, u32 *dgain)
{
	int ret = 0;
	struct v4l2_subdev *subdev_module;

	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri = NULL;

	FIMC_BUG(!device);
	FIMC_BUG(!device->subdev_module);

	subdev_module = device->subdev_module;

	module = v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("module is NULL");
		ret = -EINVAL;
		goto p_err;
	}
	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;

	if (*again == 0 || *dgain == 0) {
		dbg_sensor(1, "%s: skip", __func__);
		goto p_err;
	}

	ret = CALL_CISOPS(&sensor_peri->cis, cis_compensate_gain_for_extremely_br, sensor_peri->subdev_cis, expo, again, dgain);
	if (ret < 0) {
		err("err!!! ret(%d)", ret);
		goto p_err;
	}

p_err:
	return ret;
}

int fimc_is_sensor_peri_debug_fixed(struct fimc_is_device_sensor *device)
{
	int ret = 0;
	struct ae_param expo, dgain, again;

	if (!device) {
		err("device is null\n");
		goto p_err;
	}

	if (unlikely(sysfs_sensor.is_en == true)) {
		dbg_sensor(1, "sysfs_sensor.frame_duration = %d\n", sysfs_sensor.frame_duration);
		if (fimc_is_sensor_peri_s_frame_duration(device,
					FPS_TO_DURATION_US(sysfs_sensor.frame_duration))) {
			err("failed to set frame duration : %d\n - %d",
				sysfs_sensor.frame_duration, ret);
			goto p_err;
		}

		dbg_sensor(1, "exposure = %d %d\n",
				sysfs_sensor.long_exposure_time, sysfs_sensor.short_exposure_time);
		expo.long_val = sysfs_sensor.long_exposure_time;
		expo.short_val = sysfs_sensor.short_exposure_time;
		if (fimc_is_sensor_peri_s_exposure_time(device, expo)) {
			err("failed to set exposure time : %d %d\n - %d",
				sysfs_sensor.long_exposure_time, sysfs_sensor.short_exposure_time, ret);
			goto p_err;
		}

		dbg_sensor(1, "again = %d %d\n", sysfs_sensor.long_analog_gain, sysfs_sensor.short_analog_gain);
		again.long_val = sysfs_sensor.long_analog_gain * 10;
		again.short_val = sysfs_sensor.long_analog_gain * 10;
		ret = fimc_is_sensor_peri_s_analog_gain(device, again);
		if (ret < 0) {
			err("failed to set analog gain : %d %d\n - %d",
					sysfs_sensor.long_analog_gain,
					sysfs_sensor.short_analog_gain, ret);
			goto p_err;
		}

		dbg_sensor(1, "dgain = %d %d\n", sysfs_sensor.long_digital_gain, sysfs_sensor.short_digital_gain);
		dgain.long_val = sysfs_sensor.long_digital_gain * 10;
		dgain.short_val = sysfs_sensor.long_digital_gain * 10;
		ret = fimc_is_sensor_peri_s_digital_gain(device, dgain);
		if (ret < 0) {
			err("failed to set digital gain : %d %d\n - %d",
				sysfs_sensor.long_digital_gain,
				sysfs_sensor.short_digital_gain, ret);
			goto p_err;
		}
	}

p_err:
	return ret;
}

void fimc_is_sensor_peri_actuator_check_landing_time(ulong data)
{
	u32 *check_time_out = (u32 *)data;

	FIMC_BUG_VOID(!check_time_out);

	warn("Actuator softlanding move is time overrun. Skip by force.\n");
	*check_time_out = true;
}

int fimc_is_sensor_peri_actuator_check_move_done(struct fimc_is_device_sensor_peri *device)
{
	int ret = 0;
	struct fimc_is_actuator *actuator;
	struct fimc_is_actuator_interface *actuator_itf;
	struct fimc_is_actuator_data *actuator_data;
	struct v4l2_control v4l2_ctrl;

	FIMC_BUG(!device);

	actuator = device->actuator;
	actuator_itf = &device->sensor_interface.actuator_itf;
	actuator_data = &actuator->actuator_data;

	v4l2_ctrl.id = V4L2_CID_ACTUATOR_GET_STATUS;
	v4l2_ctrl.value = ACTUATOR_STATUS_BUSY;
	actuator_data->check_time_out = false;

	setup_timer(&actuator_data->timer_wait,
			fimc_is_sensor_peri_actuator_check_landing_time,
			(ulong)&actuator_data->check_time_out);

	mod_timer(&actuator->actuator_data.timer_wait,
		jiffies +
		msecs_to_jiffies(actuator_itf->soft_landing_table.step_delay));
	do {
		ret = v4l2_subdev_call(device->subdev_actuator, core, g_ctrl, &v4l2_ctrl);
		if (ret) {
			err("[SEN:%d] v4l2_subdev_call(g_ctrl, id:%d) is fail",
					actuator->id, v4l2_ctrl.id);
			goto exit;
		}
	} while (v4l2_ctrl.value == ACTUATOR_STATUS_BUSY &&
			actuator_data->check_time_out == false);

exit:
	if (actuator->actuator_data.timer_wait.data) {
		del_timer(&actuator->actuator_data.timer_wait);
		actuator->actuator_data.timer_wait.data = (unsigned long)NULL;
	}

	return ret;
}

int fimc_is_sensor_peri_actuator_softlanding(struct fimc_is_device_sensor_peri *device)
{
	int ret = 0;
	int i;
	struct fimc_is_actuator *actuator;
	struct fimc_is_actuator_data *actuator_data;
	struct fimc_is_actuator_interface *actuator_itf;
	struct fimc_is_actuator_softlanding_table *soft_landing_table;
	struct v4l2_control v4l2_ctrl;

	FIMC_BUG(!device);

	if (!test_bit(FIMC_IS_SENSOR_ACTUATOR_AVAILABLE, &device->peri_state)) {
		dbg_sensor(1, "%s: FIMC_IS_SENSOR_ACTUATOR_NOT_AVAILABLE\n", __func__);
		return ret;
	}

	actuator_itf = &device->sensor_interface.actuator_itf;
	actuator = device->actuator;
	actuator_data = &actuator->actuator_data;
	soft_landing_table = &actuator_itf->soft_landing_table;

	if (!soft_landing_table->enable) {
		soft_landing_table->position_num = 1;
		soft_landing_table->step_delay = 200;
		soft_landing_table->hw_table[0] = 0;
	}
#ifdef USE_CAMERA_ACT_DRIVER_SOFT_LANDING
	v4l2_ctrl.id = V4L2_CID_ACTUATOR_SOFT_LANDING;
	ret = v4l2_subdev_call(device->subdev_actuator, core, s_ctrl, &v4l2_ctrl);

	if(ret != HW_SOFTLANDING_FAIL){
		if(ret)
			err("[SEN:%d] v4l2_subdev_call(s_ctrl, id:%d) is fail(%d)",
				actuator->id, v4l2_ctrl.id, ret);
		return ret;
	}
#endif

	ret = fimc_is_sensor_peri_actuator_check_move_done(device);
	if (ret) {
		err("failed to get actuator position : ret(%d)\n", ret);
		return ret;
	}

	for (i = 0; i < soft_landing_table->position_num; i++) {
		if (actuator->position < soft_landing_table->hw_table[i])
			continue;

		dbg_sensor(1, "%s: cur_pos(%d) --> tgt_pos(%d)\n",
					__func__,
					actuator->position, soft_landing_table->hw_table[i]);

		v4l2_ctrl.id = V4L2_CID_ACTUATOR_SET_POSITION;
		v4l2_ctrl.value = soft_landing_table->hw_table[i];
		ret = v4l2_subdev_call(device->subdev_actuator, core, s_ctrl, &v4l2_ctrl);
		if (ret) {
			err("[SEN:%d] v4l2_subdev_call(s_ctrl, id:%d) is fail(%d)",
					actuator->id, v4l2_ctrl.id, ret);
			return ret;
		}

		actuator_itf->virtual_pos = soft_landing_table->virtual_table[i];
		actuator_itf->hw_pos = soft_landing_table->hw_table[i];

		/* The actuator needs a delay time when lens moving for soft landing. */
		msleep(soft_landing_table->step_delay);

		ret = fimc_is_sensor_peri_actuator_check_move_done(device);
		if (ret) {
			err("failed to get actuator position : ret(%d)\n", ret);
			return ret;
		}
	}

	return ret;
}

/* M2M AF position setting */
int fimc_is_sensor_peri_call_m2m_actuator(struct fimc_is_device_sensor *device)
{
	int ret = 0;
	int index;
	struct fimc_is_module_enum *module;
	struct fimc_is_device_sensor_peri *sensor_peri;
	struct v4l2_subdev *subdev_module;

	FIMC_BUG(!device);

	subdev_module = device->subdev_module;
	if (!subdev_module) {
		err("subdev_module is NULL");
		return -EINVAL;
	}

	module = (struct fimc_is_module_enum *)v4l2_get_subdevdata(subdev_module);
	if (!module) {
		err("subdev_module is NULL");
		return -EINVAL;
	}

	sensor_peri = (struct fimc_is_device_sensor_peri *)module->private_data;
	if (!sensor_peri) {
		err("sensor_peri is NULL");
		return -EINVAL;
	}

	index = sensor_peri->actuator->actuator_index;

	if (index >= 0) {
		dbg_sensor(1, "%s: M2M actuator set schedule\n", __func__);
		schedule_work(&sensor_peri->actuator->actuator_data.actuator_work);
	}
	else {
		/* request_count zero is not request set position in FW */
		dbg_sensor(1, "actuator request position is Zero\n");
		sensor_peri->actuator->actuator_index = -1;

		return ret;
	}

	return ret;
}
