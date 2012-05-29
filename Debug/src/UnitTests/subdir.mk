################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UnitTests/ConditionTest.cpp \
../src/UnitTests/FileBlocksTest.cpp \
../src/UnitTests/KeyTest.cpp \
../src/UnitTests/NodeTest.cpp \
../src/UnitTests/QueryTest.cpp \
../src/UnitTests/SerializersTest.cpp \
../src/UnitTests/Test.cpp 

OBJS += \
./src/UnitTests/ConditionTest.o \
./src/UnitTests/FileBlocksTest.o \
./src/UnitTests/KeyTest.o \
./src/UnitTests/NodeTest.o \
./src/UnitTests/QueryTest.o \
./src/UnitTests/SerializersTest.o \
./src/UnitTests/Test.o 

CPP_DEPS += \
./src/UnitTests/ConditionTest.d \
./src/UnitTests/FileBlocksTest.d \
./src/UnitTests/KeyTest.d \
./src/UnitTests/NodeTest.d \
./src/UnitTests/QueryTest.d \
./src/UnitTests/SerializersTest.d \
./src/UnitTests/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/UnitTests/%.o: ../src/UnitTests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/alemarra/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


