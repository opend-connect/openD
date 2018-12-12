# Release Notes

|             |                            |
| ---------:  | -------------------------- |
| __Project__ | HAN-FUN CI                 |
| __Version__ | v1.3.0                     |
| __Date__    | 23/06/2015                 |

## Overview

This a ULE Alliance's HAN-FUN Common Implementation public release.

This software release allows third-party vendors to easily create devices that are compatible with the ULE Alliance HAN-FUN standard v1.2.0.

Not all of the standard has been implemented so far, please see the *Features* section for further information on what has been implemented and what is missing.

For more information on requirements, building and using this software package, please see the README file present in the software distribution.

## Features

* A - Attribute
* C - Command

### New

  * Simple Temperature interface.
  * Simple Humidity interface.
  * Simple Temperature Sensor profile.
  * Simple Humidity Sensor profile.

### 1. Protocol [HF-Protocol v1.2.0]

* General support for all defined features has been implemented.

### 2. Core Services & Interfaces [HF-Services v1.2.0]

#### 2.1 Device Management Service [6.1]

| __Reference__ | __Commands & Attributes__            | __Type__ | __Client__     | __Server__  |
| ------------- | ------------------------------------ | :------: | -------------- | ----------- |
| 6.1.2.1       | Number of Entries                    | A        | Not Applicable | Implemented |
| 6.1.5.1       | Register device                      | C        | Implemented    | Implemented |
| 6.1.5.2       | De-register device                   | C        | Implemented    | Implemented |
| 6.1.5.3       | Start Session Read Registration Info | C        | Implemented    | Implemented |
| 6.1.5.4       | End Session Read Registration Info   | C        | Implemented    | Implemented |
| 6.1.5.5       | Get Entries                          | C        | Implemented    | Implemented |

#### 2.2 Bind Management Service [6.2]

| __Reference__ | __Commands & Attributes__                          | __Type__ | __Client__      | __Server__      |
| ------------- | -------------------------------------------------- | :------: | --------------  | -------------   |
| 6.2.2.1       | Number of Entries                                  | A        | Not Applicable  | Implemented     |
| 6.2.5.1       | Add Bind                                           | C        | Implemented     | Not Implemented |
| 6.2.5.2       | Remove Bind                                        | C        | Implemented     | Not Implemented |
| 6.2.5.3       | Remove Bind by SRC Device Address                  | C        | Not Implemented | Not Implemented |
| 6.2.5.4       | Remove Bind by SRC Device Address and Unit ID      | C        | Not Implemented | Not Implemented |
| 6.2.5.5       | Remove Bind by DST Address                         | C        | Not Implemented | Not Implemented |
| 6.2.5.6       | Remove Bind by DST Address and Unit ID             | C        | Not Implemented | Not Implemented |
| 6.2.5.7       | Start Session Read Bind Info                       | C        | Implemented     | Implemented     |
| 6.2.5.8       | End Session Read Bind Info                         | C        | Implemented     | Implemented     |
| 6.2.5.9       | Get Bind Entries by Index                          | C        | Implemented     | Implemented     |
| 6.2.5.10      | Get Bind Entries by SRC Device Address             | C        | Not Implemented | Not Implemented |
| 6.2.5.11      | Get Bind Entries by SRC Device Address and Unit ID | C        | Not Implemented | Not Implemented |
| 6.2.5.12      | Get Bind Entries by DST Address                    | C        | Not Implemented | Not Implemented |
| 6.2.5.13      | Get Bind Entries by DST Address and Unit ID        | C        | Not Implemented | Not Implemented |

#### 2.3 Group Management Service [6.3]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------  | -------------   |
| 6.3.2.1       | Number of Groups          | A        | Not Applicable  | Not Implemented |
| 6.3.5.1       | Create Group              | C        | Not Implemented | Not Implemented |
| 6.3.5.2       | Delete Group              | C        | Not Implemented | Not Implemented |
| 6.3.5.3       | Add to Group              | C        | Not Implemented | Not Implemented |
| 6.3.5.4       | Remove from Group         | C        | Not Implemented | Not Implemented |
| 6.3.5.5       | Get Group Info            | C        | Not Implemented | Not Implemented |

#### 2.4 Identify Device Interface [6.4]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------  | -------------   |
| 6.4.3.1       | Identification            | C        | Not Implemented | Not Implemented |

#### 2.5 Device Information Service [6.5]

| __Reference__ | __Commands & Attributes__              | __Type__ | __Client__     | __Server__      |
| ------------- | -------------------------------------- | :------: | -------------- | --------------- |
| 6.5.1.1       | Core Release version                   | A        | Not Applicable | Implemented     |
| 6.5.1.2       | Profile Release version                | A        | Not Applicable | Implemented     |
| 6.5.1.3       | Interface Release version              | A        | Not Applicable | Implemented     |
| 6.5.1.4       | Extra Capabilities                     | A        | Not Applicable | Implemented     |
| 6.5.1.5       | Minimum Sleep Time                     | A        | Not Applicable | Not Implemented |
| 6.5.1.6       | Actual Response Time [Paging Interval] | A        | Not Applicable | Not Implemented |
| 6.5.1.7       | Application version                    | A        | Not Applicable | Not Implemented |
| 6.5.1.8       | EMC                                    | A        | Not Applicable | Implemented     |
| 6.5.1.9       | RFPI/ IPUI                             | A        | Not Applicable | Not Implemented |
| 6.5.1.10      | Manufacturer Name                      | A        | Not Applicable | Not Implemented |
| 6.5.1.11      | Location Length                        | A        | Not Applicable | Not Implemented |
| 6.5.1.12      | Device Enable                          | A        | Not Applicable | Not Implemented |
| 6.5.1.13      | Friendly Name                          | A        | Not Applicable | Not Implemented |
| 6.5.1.14      | Device Unique Identifier [UID]         | A        | Not Applicable | Implemented     |
| 6.5.1.15      | Device Serial Number                   | A        | Not Applicable | Not Implemented |

#### 2.6 Attribute Reporting Service [6.6]

| __Reference__ | __Commands & Attributes__    | __Type__ | __Client__      | __Server__      |
| ------------- | ---------------------------- | :------: | --------------- | --------------- |
| 6.6.2.1       | Number of Reports            | A        | Not Applicable  | Implemented     |
| 6.6.2.2       | Number of Periodic Reports   | A        | Not Applicable  | Implemented     |
| 6.6.2.3       | Number of Event Reports      | A        | Not Applicable  | Implemented     |
| 6.6.4.1       | Periodic Report Notification | C        | Implemented     | Implemented     |
| 6.6.4.2       | Event Report Notification    | C        | Implemented     | Implemented     |
| 6.6.5.1       | Create Periodic Report       | C        | Implemented     | Implemented     |
| 6.6.5.2       | Create Event Report          | C        | Implemented     | Implemented     |
| 6.6.5.3       | Add Periodic Report Entry    | C        | Implemented     | Implemented     |
| 6.6.5.4       | Add Event Report Entry       | C        | Implemented     | Implemented     |
| 6.6.5.5       | Delete Report                | C        | Implemented     | Implemented     |
| 6.6.5.6       | Get Periodic Report Entries  | C        | Not Implemented | Not Implemented |
| 6.6.5.7       | Get Event Report Entries     | C        | Not Implemented | Not Implemented |

#### 2.7 Tamper Interface [6.7]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 6.7.1.1       | State                     | A        | Not Implemented | Not Implemented |
| 6.7.3.1       | Tamper Alert On           | C        | Not Implemented | Not Implemented |
| 6.7.3.2       | Tamper Alert Off          | C        | Not Implemented | Not Implemented |

#### 2.8 Tamper Interface [6.8]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 6.8.1.1       | Time                      | A        | Not Applicable  | Not Implemented |

#### 2.9 Power Interface [6.9]

| __Reference__ | __Commands & Attributes__         | __Type__ | __Client__      | __Server__      |
| ------------- | --------------------------------- | :------: | --------------- | --------------- |
| 6.9.1.1       | Mains Voltage                     | A        | Not Applicable  | Not Implemented |
| 6.9.1.2       | Mains Frequency                   | A        | Not Applicable  | Not Implemented |
| 6.9.1.3       | Mains Alarms                      | A        | Not Applicable  | Not Implemented |
| 6.9.1.4       | Mains Minimum Voltage Threshold   | A        | Not Applicable  | Not Implemented |
| 6.9.1.5       | Mains Maximum Voltage Threshold   | A        | Not Applicable  | Not Implemented |
| 6.9.1.6       | Mains Voltage Dwell Trip Point    | A        | Not Applicable  | Not Implemented |
| 6.9.1.7       | Battery Voltage                   | A        | Not Applicable  | Not Implemented |
| 6.9.1.8       | Battery Manufacturer              | A        | Not Applicable  | Not Implemented |
| 6.9.1.9       | Battery Type                      | A        | Not Applicable  | Not Implemented |
| 6.9.1.10      | Battery AHr Rating                | A        | Not Applicable  | Not Implemented |
| 6.9.1.11      | Battery Cell Quantity             | A        | Not Applicable  | Not Implemented |
| 6.9.1.12      | Battery Rated Voltage             | A        | Not Applicable  | Not Implemented |
| 6.9.1.13      | Battery Status                    | A        | Not Applicable  | Not Implemented |
| 6.9.1.14      | Battery Minimum Voltage Threshold | A        | Not Applicable  | Not Implemented |
| 6.9.1.15      | Battery Maximum Voltage Threshold | A        | Not Applicable  | Not Implemented |
| 6.9.1.16      | Battery Charge Level              | A        | Not Applicable  | Not Implemented |
| 6.9.1.17      | Battery Minimum Charge Level      | A        | Not Applicable  | Not Implemented |
| 6.9.1.18      | Battery Maximum Charge Level      | A        | Not Applicable  | Not Implemented |
| 6.9.1.19      | Power Source                      | A        | Not Applicable  | Not Implemented |

#### 2.10 RSSI [6.10]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 6.10.1.1      | RSSI                      | A        | Not Applicable  | Not Implemented |

#### 2.11 Keep Alive Interface [6.11]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 6.11.1.1      | Interval                  | A        | Not Applicable  | Not Implemented |
| 6.11.3.1      | I am Alive                | C        | Not Applicable  | Not Implemented |

#### 2.12 Keep Alive Interface [6.12]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 6.12.3.1      | New Version Available     | C        | Not Applicable  | Not Implemented |
| 6.12.4.1      | Check Vesion              | C        | Not Implemented | Not Applicable  |
| 6.12.4.2      | Upgrade Complete          | C        | Not Implemented | Not Applicable  |

### 3. Profiles [HF-Profiles v1.2.0]

| __Reference__ | __Profile__                          | __Status__  |
| ------------- | ------------------------------------ | ----------- |
| 5.1.1         | Simple OnOff Switchable              | Implemented |
| 5.1.2         | Simple On-Off Switch                 | Implemented |
| 5.1.3         | Simple Level Controllable            | Implemented |
| 5.1.4         | Simple Level Control                 | Implemented |
| 5.1.5         | Simple Level Controllable Switchable | Implemented |
| 5.1.6         | Simple Level Control switch          | Implemented |
| 5.1.7         | AC Outlet                            | Implemented |
| 5.1.8         | AC Outlet with Simple Power Metering | Implemented |
| 5.1.9         | Simple Light                         | Implemented |
| 5.1.10        | Dimmable Light                       | Implemented |
| 5.1.11        | Dimmer Switch                        | Implemented |
| 5.1.12        | Simple Door Lock                     | Implemented |
| 5.1.13        | Simple Door Bell                     | Implemented |
| 5.1.14        | Simple Power Meter                   | Implemented |
| 5.1.15        | Simple Temperature Sensor            | Implemented |
| 5.1.16        | Simple Humidity Sensor               | Implemented |
| 5.2.1         | Simple Detector                      | Implemented |
| 5.2.2         | Door Open Close Detector             | Implemented |
| 5.2.3         | Window Open Close Detector           | Implemented |
| 5.2.4         | Motion Detector                      | Implemented |
| 5.2.5         | Smoke Detector                       | Implemented |
| 5.2.6         | Gas Detector                         | Implemented |
| 5.2.7         | Flood Detector                       | Implemented |
| 5.2.8         | Glass Break Detector                 | Implemented |
| 5.2.9         | Vibration Detector                   | Implemented |
| 5.2.10        | Siren                                | Implemented |
| 5.1.11        | Alertable                            | Implemented |
| 5.3.1         | Simple Pendant                       | Implemented |
| 5.4.1         | User Interface                       | Implemented |
| 5.4.2         | Generic Application Logic            | Implemented |

### 4. Interfaces [HF-Interfaces v1.2.0]

#### 4.1 Alert [5.1]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 5.1.1.1       | State                     | A        | Not Applicable  | Implemented     |
| 5.1.1.2       | Enable                    | A        | Not Applicable  | Implemented     |
| 5.1.3.1       | Status                    | C        | Implemented     | Implemented     |

#### 4.2 On-Off [5.2]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 5.2.1.1       | State                     | A        | Not Applicable  | Implemented     |
| 5.2.4.1       | On                        | C        | Implemented     | Implemented     |
| 5.2.4.2       | Off                       | C        | Implemented     | Implemented     |
| 5.2.4.3       | Toggle                    | C        | Implemented     | Implemented     |

#### 4.3 Level Control [5.3]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 5.3.1.1       | Current Level             | A        | Not Applicable  | Implemented     |
| 5.3.4.1       | Set Level                 | C        | Implemented     | Implemented     |

#### 4.4 Simple Power Meter [5.4]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 5.4.1.1       | Energy                    | A        | Not Applicable  | Implemented     |
| 5.4.1.2       | Energy at Last Reset      | A        | Not Applicable  | Implemented     |
| 5.4.1.3       | Time at Last Reset        | A        | Not Applicable  | Implemented     |
| 5.4.1.4       | Instantaneous Power       | A        | Not Applicable  | Implemented     |
| 5.4.1.5       | Average Power             | A        | Not Applicable  | Implemented     |
| 5.4.1.6       | Average Power Interval    | A        | Not Applicable  | Implemented     |
| 5.4.1.7       | Voltage                   | A        | Not Applicable  | Implemented     |
| 5.4.1.8       | Current                   | A        | Not Applicable  | Implemented     |
| 5.4.1.9       | Frequency                 | A        | Not Applicable  | Implemented     |
| 5.4.1.10      | Power Factor              | A        | Not Applicable  | Implemented     |
| 5.4.1.11      | Report Interval           | A        | Not Applicable  | Implemented     |
| 5.4.3.1       | Report                    | C        | Implemented     | Implemented     |
| 5.4.4.1       | Measurment Reset          | C        | Not Implemented | Not Implemented |

#### 4.5 Simple Temperature [5.5]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 5.5.1.1       | Measured Temperature      | A        | Not Applicable  | Implemented     |
| 5.5.1.2       | Min. Measurable Temp.     | A        | Not Applicable  | Implemented     |
| 5.5.1.3       | Max. Measurable Temp.     | A        | Not Applicable  | Implemented     |
| 5.5.1.4       | Tolerance                 | A        | Not Applicable  | Implemented     |

#### 4.6 Simple Humidity [5.6]

| __Reference__ | __Commands & Attributes__ | __Type__ | __Client__      | __Server__      |
| ------------- | ------------------------- | :------: | --------------- | --------------- |
| 5.6.1.1       | Measured Humidity         | A        | Not Applicable  | Implemented     |
| 5.6.1.2       | Tolerance                 | A        | Not Applicable  | Implemented     |

## Bug Fixes

  * See Changelog file.

## Known Issues and Problems

See the Todo List in the doxygen documentation for the software release.

