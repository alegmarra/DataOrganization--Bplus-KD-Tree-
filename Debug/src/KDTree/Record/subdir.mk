################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/Record/Formacion.cpp \
../src/KDTree/Record/FranjaHoraria.cpp \
../src/KDTree/Record/ID.cpp \
../src/KDTree/Record/Infinity.cpp \
../src/KDTree/Record/IntKey.cpp \
../src/KDTree/Record/Key.cpp \
../src/KDTree/Record/KeyFactory.cpp \
../src/KDTree/Record/StringKey.cpp 

OBJS += \
./src/KDTree/Record/Formacion.o \
./src/KDTree/Record/FranjaHoraria.o \
./src/KDTree/Record/ID.o \
./src/KDTree/Record/Infinity.o \
./src/KDTree/Record/IntKey.o \
./src/KDTree/Record/Key.o \
./src/KDTree/Record/KeyFactory.o \
./src/KDTree/Record/StringKey.o 

CPP_DEPS += \
./src/KDTree/Record/Formacion.d \
./src/KDTree/Record/FranjaHoraria.d \
./src/KDTree/Record/ID.d \
./src/KDTree/Record/Infinity.d \
./src/KDTree/Record/IntKey.d \
./src/KDTree/Record/Key.d \
./src/KDTree/Record/KeyFactory.d \
./src/KDTree/Record/StringKey.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/Record/%.o: ../src/KDTree/Record/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/alemarra/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


