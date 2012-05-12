################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UnitTests/KeyTest.cpp 

OBJS += \
./src/UnitTests/KeyTest.o 

CPP_DEPS += \
./src/UnitTests/KeyTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/UnitTests/%.o: ../src/UnitTests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/saasbook/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


