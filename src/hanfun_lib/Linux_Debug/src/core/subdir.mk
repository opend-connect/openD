################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/core/attribute_reporting.cpp \
../src/core/attribute_reporting_client.cpp \
../src/core/attribute_reporting_server.cpp \
../src/core/bind_management.cpp \
../src/core/bind_management_client.cpp \
../src/core/bind_management_server.cpp \
../src/core/device_information.cpp \
../src/core/device_management.cpp \
../src/core/device_management_client.cpp \
../src/core/device_management_server.cpp \
../src/core/session_management_client.cpp \
../src/core/session_management_server.cpp 

OBJS += \
./src/core/attribute_reporting.o \
./src/core/attribute_reporting_client.o \
./src/core/attribute_reporting_server.o \
./src/core/bind_management.o \
./src/core/bind_management_client.o \
./src/core/bind_management_server.o \
./src/core/device_information.o \
./src/core/device_management.o \
./src/core/device_management_client.o \
./src/core/device_management_server.o \
./src/core/session_management_client.o \
./src/core/session_management_server.o 

CPP_DEPS += \
./src/core/attribute_reporting.d \
./src/core/attribute_reporting_client.d \
./src/core/attribute_reporting_server.d \
./src/core/bind_management.d \
./src/core/bind_management_client.d \
./src/core/bind_management_server.d \
./src/core/device_information.d \
./src/core/device_management.d \
./src/core/device_management_client.d \
./src/core/device_management_server.d \
./src/core/session_management_client.d \
./src/core/session_management_server.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DHF_APP_EXT_REG -DDLG_HF_NO_ASSERT -I../inc -I../apps -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -std=c++11 -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


