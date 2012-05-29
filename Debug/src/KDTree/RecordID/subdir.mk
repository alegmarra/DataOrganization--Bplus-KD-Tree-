################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/RecordID/Formacion.cpp \
../src/KDTree/RecordID/FranjaHoraria.cpp \
../src/KDTree/RecordID/ID.cpp \
../src/KDTree/RecordID/Infinity.cpp \
../src/KDTree/RecordID/IntKey.cpp \
../src/KDTree/RecordID/Key.cpp \
../src/KDTree/RecordID/KeyFactory.cpp \
../src/KDTree/RecordID/StringKey.cpp 

OBJS += \
./src/KDTree/RecordID/Formacion.o \
./src/KDTree/RecordID/FranjaHoraria.o \
./src/KDTree/RecordID/ID.o \
./src/KDTree/RecordID/Infinity.o \
./src/KDTree/RecordID/IntKey.o \
./src/KDTree/RecordID/Key.o \
./src/KDTree/RecordID/KeyFactory.o \
./src/KDTree/RecordID/StringKey.o 

CPP_DEPS += \
./src/KDTree/RecordID/Formacion.d \
./src/KDTree/RecordID/FranjaHoraria.d \
./src/KDTree/RecordID/ID.d \
./src/KDTree/RecordID/Infinity.d \
./src/KDTree/RecordID/IntKey.d \
./src/KDTree/RecordID/Key.d \
./src/KDTree/RecordID/KeyFactory.d \
./src/KDTree/RecordID/StringKey.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/RecordID/%.o: ../src/KDTree/RecordID/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/alemarra/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


