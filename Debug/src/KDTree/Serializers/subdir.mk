################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/Serializers/KDtreeSerializer.cpp \
../src/KDTree/Serializers/NodeSerializer.cpp 

OBJS += \
./src/KDTree/Serializers/KDtreeSerializer.o \
./src/KDTree/Serializers/NodeSerializer.o 

CPP_DEPS += \
./src/KDTree/Serializers/KDtreeSerializer.d \
./src/KDTree/Serializers/NodeSerializer.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/Serializers/%.o: ../src/KDTree/Serializers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/alemarra/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


