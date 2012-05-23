################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/ID.cpp \
../src/KDTree/KD.cpp \
../src/KDTree/Key.cpp \
../src/KDTree/Record.cpp 

OBJS += \
./src/KDTree/ID.o \
./src/KDTree/KD.o \
./src/KDTree/Key.o \
./src/KDTree/Record.o 

CPP_DEPS += \
./src/KDTree/ID.d \
./src/KDTree/KD.d \
./src/KDTree/Key.d \
./src/KDTree/Record.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/%.o: ../src/KDTree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/saasbook/tpDatos/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


