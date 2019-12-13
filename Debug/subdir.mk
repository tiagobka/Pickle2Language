################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Pass1Visitor.cpp \
../Pass2Visitor.cpp \
../Pcl2.cpp 

OBJS += \
./Pass1Visitor.o \
./Pass2Visitor.o \
./Pcl2.o 

CPP_DEPS += \
./Pass1Visitor.d \
./Pass2Visitor.d \
./Pcl2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/tiago/eclipse-workspace/Pickle2" -I"/home/tiago/eclipse-workspace/Pickle2/target/generated-sources/antlr4" -I/usr/local/include/antlr4-runtime -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


