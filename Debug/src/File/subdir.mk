################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/File/Abstract.cpp \
../src/File/Record.cpp \
../src/File/Sequential.cpp 

OBJS += \
./src/File/Abstract.o \
./src/File/Record.o \
./src/File/Sequential.o 

CPP_DEPS += \
./src/File/Abstract.d \
./src/File/Record.d \
./src/File/Sequential.d 


# Each subdirectory must supply rules for building sources it contributes
src/File/%.o: ../src/File/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/bort/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

