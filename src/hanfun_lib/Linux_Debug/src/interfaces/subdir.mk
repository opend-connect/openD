################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/interfaces/alert.cpp \
../src/interfaces/alert_client.cpp \
../src/interfaces/alert_server.cpp \
../src/interfaces/level_control.cpp \
../src/interfaces/level_control_client.cpp \
../src/interfaces/level_control_server.cpp \
../src/interfaces/on_off.cpp \
../src/interfaces/on_off_client.cpp \
../src/interfaces/on_off_server.cpp \
../src/interfaces/simple_humidity_client.cpp \
../src/interfaces/simple_humidity_server.cpp \
../src/interfaces/simple_power_meter.cpp \
../src/interfaces/simple_power_meter_client.cpp \
../src/interfaces/simple_power_meter_server.cpp \
../src/interfaces/simple_temperature_client.cpp \
../src/interfaces/simple_temperature_server.cpp 

OBJS += \
./src/interfaces/alert.o \
./src/interfaces/alert_client.o \
./src/interfaces/alert_server.o \
./src/interfaces/level_control.o \
./src/interfaces/level_control_client.o \
./src/interfaces/level_control_server.o \
./src/interfaces/on_off.o \
./src/interfaces/on_off_client.o \
./src/interfaces/on_off_server.o \
./src/interfaces/simple_humidity_client.o \
./src/interfaces/simple_humidity_server.o \
./src/interfaces/simple_power_meter.o \
./src/interfaces/simple_power_meter_client.o \
./src/interfaces/simple_power_meter_server.o \
./src/interfaces/simple_temperature_client.o \
./src/interfaces/simple_temperature_server.o 

CPP_DEPS += \
./src/interfaces/alert.d \
./src/interfaces/alert_client.d \
./src/interfaces/alert_server.d \
./src/interfaces/level_control.d \
./src/interfaces/level_control_client.d \
./src/interfaces/level_control_server.d \
./src/interfaces/on_off.d \
./src/interfaces/on_off_client.d \
./src/interfaces/on_off_server.d \
./src/interfaces/simple_humidity_client.d \
./src/interfaces/simple_humidity_server.d \
./src/interfaces/simple_power_meter.d \
./src/interfaces/simple_power_meter_client.d \
./src/interfaces/simple_power_meter_server.d \
./src/interfaces/simple_temperature_client.d \
./src/interfaces/simple_temperature_server.d 


# Each subdirectory must supply rules for building sources it contributes
src/interfaces/%.o: ../src/interfaces/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DHF_APP_EXT_REG -DDLG_HF_NO_ASSERT -I../inc -I../apps -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -std=c++11 -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


