################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KDTree/Node/InnerNode.cpp \
../src/KDTree/Node/LeafNode.cpp \
../src/KDTree/Node/Node.cpp \
../src/KDTree/Node/Pair.cpp 

OBJS += \
./src/KDTree/Node/InnerNode.o \
./src/KDTree/Node/LeafNode.o \
./src/KDTree/Node/Node.o \
./src/KDTree/Node/Pair.o 

CPP_DEPS += \
./src/KDTree/Node/InnerNode.d \
./src/KDTree/Node/LeafNode.d \
./src/KDTree/Node/Node.d \
./src/KDTree/Node/Pair.d 


# Each subdirectory must supply rules for building sources it contributes
src/KDTree/Node/%.o: ../src/KDTree/Node/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/alemarra/tpDatos/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


