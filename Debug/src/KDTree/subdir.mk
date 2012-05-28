################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/InnerNode.cpp \
../src/KDTree/KD.cpp \
../src/KDTree/LeafNode.cpp \
../src/KDTree/Node.cpp \
../src/KDTree/Query.cpp \
../src/KDTree/Record.cpp 

OBJS += \
./src/KDTree/InnerNode.o \
./src/KDTree/KD.o \
./src/KDTree/LeafNode.o \
./src/KDTree/Node.o \
./src/KDTree/Query.o \
./src/KDTree/Record.o 

CPP_DEPS += \
./src/KDTree/InnerNode.d \
./src/KDTree/KD.d \
./src/KDTree/LeafNode.d \
./src/KDTree/Node.d \
./src/KDTree/Query.d \
./src/KDTree/Record.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/%.o: ../src/KDTree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/saasbook/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


