################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Exceptions/FileErrorException.cpp \
../src/Exceptions/FileNotSetException.cpp \
../src/Exceptions/InvalidIntSizeException.cpp \
../src/Exceptions/InvalidKeyException.cpp \
../src/Exceptions/InvalidOperationException.cpp \
../src/Exceptions/InvalidTargetException.cpp \
../src/Exceptions/NonExistingDimensionException.cpp 

OBJS += \
./src/Exceptions/FileErrorException.o \
./src/Exceptions/FileNotSetException.o \
./src/Exceptions/InvalidIntSizeException.o \
./src/Exceptions/InvalidKeyException.o \
./src/Exceptions/InvalidOperationException.o \
./src/Exceptions/InvalidTargetException.o \
./src/Exceptions/NonExistingDimensionException.o 

CPP_DEPS += \
./src/Exceptions/FileErrorException.d \
./src/Exceptions/FileNotSetException.d \
./src/Exceptions/InvalidIntSizeException.d \
./src/Exceptions/InvalidKeyException.d \
./src/Exceptions/InvalidOperationException.d \
./src/Exceptions/InvalidTargetException.d \
./src/Exceptions/NonExistingDimensionException.d 


# Each subdirectory must supply rules for building sources it contributes
src/Exceptions/%.o: ../src/Exceptions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/saasbook/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


