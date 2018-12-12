################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/attributes.cpp \
../src/common.cpp \
../src/debug.cpp \
../src/devices.cpp \
../src/dlg_extra.cpp \
../src/interfaces.cpp \
../src/profiles.cpp \
../src/protocol.cpp \
../src/uids.cpp \
../src/units.cpp 

OBJS += \
./src/attributes.o \
./src/common.o \
./src/debug.o \
./src/devices.o \
./src/dlg_extra.o \
./src/interfaces.o \
./src/profiles.o \
./src/protocol.o \
./src/uids.o \
./src/units.o 

CPP_DEPS += \
./src/attributes.d \
./src/common.d \
./src/debug.d \
./src/devices.d \
./src/dlg_extra.d \
./src/interfaces.d \
./src/profiles.d \
./src/protocol.d \
./src/uids.d \
./src/units.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DHF_APP_EXT_REG -DDLG_HF_NO_ASSERT -I../inc -I../apps -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -std=c++11 -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


