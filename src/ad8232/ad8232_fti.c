/*
 * Author: Jon Trulson <jtrulson@ics.com>
 *         Abhishek Malik <abhishek.malik@intel.com>
 * Copyright (c) 2016 Intel Corporation.
 *
 * This program and the accompanying materials are made available under the
 * terms of the The MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 * SPDX-License-Identifier: MIT
 */

#include "ad8232.h"
#include "upm_fti.h"

/** 
 * This file implements the Function Table Interface (FTI) for this sensor
 */

const char upm_ad8232_name[] = "AD8232";
const char upm_ad8232_description[] = "AD8232 Heart Rate Monitor";
const upm_protocol_t upm_ad8232_protocol[] = {UPM_ANALOG, UPM_GPIO};
const upm_sensor_t upm_ad8232_category[] = {UPM_HEART_RATE};

// forward declarations
upm_sensor_descriptor_t upm_ad8232_get_descriptor (void* dev);
const void* upm_ad8232_get_ft(upm_sensor_t sensor_type);
void* upm_ad8232_init_name();
void upm_ad8232_close(void* dev);
upm_result_t upm_ad8232_get_value(void* dev, int* value,
                                  upm_heart_rate_u rate_unit);

upm_sensor_descriptor_t upm_ad8232_get_descriptor (void* dev){
    upm_sensor_descriptor_t usd;
    usd.name = upm_ad8232_name;
    usd.description = upm_ad8232_description;
    usd.protocol_size = 2;
    usd.protocol = upm_ad8232_protocol;
    usd.category_size = 1;
    usd.category = upm_ad8232_category;
    return usd;
}

static const upm_sensor_ft ft =
{
    .upm_sensor_init_name = &upm_ad8232_init_name,
    .upm_sensor_close = &upm_ad8232_close,
    //.upm_sensor_get_descriptor = &upm_ad8232_get_descriptor
};

static const upm_heart_rate_ft hft =
{
    .upm_heart_rate_get_value = &upm_ad8232_get_value
};

const void* upm_ad8232_get_ft(upm_sensor_t sensor_type){
    if(sensor_type == UPM_HEART_RATE){
        return &hft;
    }
    else if(sensor_type == UPM_SENSOR){
        return &ft;
    }

    return NULL;
}

void* upm_ad8232_init_name(){
    return NULL;
}

void upm_ad8232_close(void* dev){
    ad8232_close(dev);
}

upm_result_t upm_ad8232_get_value(void* dev, int* value,
                                  upm_heart_rate_u rate_unit){
    // rate_unit does not apply to this device, so...
    return ad8232_get_value(dev, value);
}