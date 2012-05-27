################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/Key/Infinity.cpp 

OBJS += \
./src/KDTree/Key/Infinity.o 

CPP_DEPS += \
./src/KDTree/Key/Infinity.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/Key/%.o: ../src/KDTree/Key/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/saasbook/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


