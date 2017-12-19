# Code examples

# Introduction

This wiki pages defines the sample code which shall be available for the openD framework. The motivation is to provide sample implementation for the different openD unified API's. The example codes cover the management and the control of a DECT device and especially, the implementation of the DECT ULE profiles.

In general, every code example provides a minimal implementation. The sample codes define the usage of the Request-Confirm and Indication-Response principle related to the specific use case.

# Generic example

The openD framework API's follow the Request-Confirm and Indication-Response principle. This chapter provides an example on how to perform a Request to select the DECT mode for the device. It describes how to use the Management API including the Request and Confirm primitives.

```c
#include "opend_api.h"
#include "opend_mgmt_api.h"

static void mgmtApiConfirm( openD_mgmtApiCfm_t *mConfirm )
{
    switch( mConfirm->service )
    {
        case OPEND_MGMTAPI_DECTMODE:
        {
            if( mConfirm->status == OPEND_STATUS_OK )
            {
                // The operation was successful. We are now operating
                // in fixed part mode
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

static void mgmtApiIndication( openD_mgmtApiInd_t *mIndication )
{
    // Not important for this example
}

int main( void )
{
    openD_mgmtApiPrimitives_t mPrimitives;
    openD_mgmtApiReq_t mRequest;

    // Init openD
    if( openD_init( ) == OPEND_STATUS_OK )
    {
        // Operation was successful
    }

    // Fill mPrimitives with correct parameter settings
    mPrimitives.openD_mgmtApiCfm = mgmtApiConfirm;
    mPrimitives.openD_mgmtApiInd = mgmtApiIndication;

    // Call init
    if( openD_mgmtApi_init( &mPrimitives ) == OPEND_STATUS_OK )
    {
        // Operation was successful
    }

    // Prepare service
    mRequest.service = OPEND_MGMTAPI_DECTMODE;
    mRequest.param.dectMode = OPEND_MGMTAPI_DECTMODE_FP;

    if( openD_mgmtApi_request( &mRequest ) == OPEND_STATUS_OK )
    {
        // Operation was successful. We are waiting now for the confirmation
    }

    while( 1 )
    {
        // Do something
    }
}
```

# OpenD API

## Initialization

This is an example application which shows how to initialize the openD framework. This sample code can be used for every application to setup the openD framework properly.

# Management API

The example codes of the Management API cover all services which are available to manage the DECT device:

- Select DECT mode
> This example explains how to configure a request with the service `OPEND_MGMTAPI_DECTMODE`. The examples cover the DECT modes `MGMTAPI_DECTMODE_FP`, `MGMTAPI_DECTMODE_PP`,  `MGMTAPI_DECTMODE_HF` and `MGMTAPI_DECTMODE_SIXLOWPAN`. In general, the sample codes for those use cases provide an introduction on how to initiate and switch the DECT mode for the device.
- Power down control
> This example explains how to configure a request with the service `MGMTAPI_POWER_DOWN_CTRL`. This example handles the low power modes of the framework.
- Wake up
> This example explains how to configure a request with the service `MGMTAPI_WAKE_UP`. This example provides an introduction on how to use the API to wake up the device from low power modes.
- Keep alive
> This example explains how to configure a request with the service `MGMTAPI_KEEP_ALIVE`. The example contains the handling of primitive events.

# Audio API

The example codes of the Audio API cover all services which are available to change audio settings on a DECT device:

- Mute
> This example explains how to configure a request with the service `AUDIOAPI_MUTE`. The goal of this example is to mute the DECT device.
- Change volume
> This example explains how to configure a request with the service `AUDIOAPI_VOLUME`. This service configures the volume level of the DECT device.

# Subscription API

The example codes of the Subscribe API cover all services which are available to perform subscription services a DECT device:

- Enable subscription
> This example explains how to configure a request with the service `SUBAPI_SUBSCRIBE_ENABLE`. This request configures the device to allow the subscription. This configuration is necessary to subscribe a device.
- Subscribe
> This example explains how to configure a request with the service `SUBAPI_SUBSCRIBE`. This example shows how to subscribe a DECT device, e.g. a handset.
- Subscription delete
> This example explains how to configure a request with the service `SUBAPI_SUBSCRIPTION_DELETE`. This example shows how to remove a subscription.
- Set access code
> This example explains how to configure a request with the service `SUBAPI_SET_AC`. The purpose of this example is to show how an access code can be configures on a DECT device.


# HAN FUN API

The example codes of the HAN FUN API cover all profiles and the related services which are available to configure and control a DECT ULE device:

- Profile `OPEND_HANFUNAPI_AC_OUTLET`:
- Profile `OPEND_HANFUNAPI_AC_OUTLET_WITH_POWER_METERING`:
- Profile `OPEND_HANFUNAPI_ALERTABLE`:
- Profile `OPEND_HANFUNAPI_COLOUR_BULB`:
- Profile `OPEND_HANFUNAPI_CONTROLABLE_THERMOSTAT`:
- Profile `OPEND_HANFUNAPI_DIMMABLE_COLOUR_BULB`:
- Profile `OPEND_HANFUNAPI_DIMMABLE_LIGHT`:
- Profile `OPEND_HANFUNAPI_DIMMER_SWITCH`:
- Profile `OPEND_HANFUNAPI_DOOR_BELL`:
- Profile `OPEND_HANFUNAPI_DOOR_OPEN_CLOSE_DETECTOR`:
- Profile `OPEND_HANFUNAPI_ENVIRONMENT_MONITOR`:
- Profile `OPEND_HANFUNAPI_FLOOD_DETECTOR`:
- Profile `OPEND_HANFUNAPI_GAS_DETECTOR`:
- Profile `OPEND_HANFUNAPI_GLASS_BREAK_DETECTOR`:
- Profile `OPEND_HANFUNAPI_MOTION_DETECTOR`:
- Profile `OPEND_HANFUNAPI_SIMPLE_AIR_PRESSURE_SENSOR`:
- Profile `OPEND_HANFUNAPI_SIMPLE_BUTTON`:
- Profile `OPEND_HANFUNAPI_SIMPLE_DETECTOR`:
- Profile `OPEND_HANFUNAPI_SIMPLE_DOOR_LOCK`:
- Profile `OPEND_HANFUNAPI_SIMPLE_HUMIDITY_SENSOR`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LED`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROL`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROLLABLE`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROLLABLE_SWITCHABLE`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LEVEL_CONTROL_SWITCH`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LIGHT`:
- Profile `OPEND_HANFUNAPI_SIMPLE_LIGHT_SENSOR`:
- Profile `OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCH`:
- Profile `OPEND_HANFUNAPI_SIMPLE_ONOFF_SWITCHABLE`:
- Profile `OPEND_HANFUNAPI_SIMPLE_PENDANT`:
- Profile `OPEND_HANFUNAPI_SIMPLE_POWER_METER`:
- Profile `OPEND_HANFUNAPI_SIMPLE_TEMPERATURE_SENSOR`:
- Profile `OPEND_HANFUNAPI_SIREN`:
- Profile `OPEND_HANFUNAPI_SMOKE_DETECTOR`:
- Profile `OPEND_HANFUNAPI_USER_INTERFACE_LOCK`:
- Profile `OPEND_HANFUNAPI_VIBRATION_DETECTOR`:
- Profile `OPEND_HANFUNAPI_WINDOW_OPEN_CLOSE_DETECTOR`:
