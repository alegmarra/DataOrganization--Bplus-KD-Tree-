################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/Query/Condition.cpp 

OBJS += \
./src/KDTree/Query/Condition.o 

CPP_DEPS += \
./src/KDTree/Query/Condition.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/Query/%.o: ../src/KDTree/Query/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/alemarra/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


