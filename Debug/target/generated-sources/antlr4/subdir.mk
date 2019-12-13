################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../target/generated-sources/antlr4/Pcl2BaseVisitor.cpp \
../target/generated-sources/antlr4/Pcl2Lexer.cpp \
../target/generated-sources/antlr4/Pcl2Parser.cpp \
../target/generated-sources/antlr4/Pcl2Visitor.cpp 

OBJS += \
./target/generated-sources/antlr4/Pcl2BaseVisitor.o \
./target/generated-sources/antlr4/Pcl2Lexer.o \
./target/generated-sources/antlr4/Pcl2Parser.o \
./target/generated-sources/antlr4/Pcl2Visitor.o 

CPP_DEPS += \
./target/generated-sources/antlr4/Pcl2BaseVisitor.d \
./target/generated-sources/antlr4/Pcl2Lexer.d \
./target/generated-sources/antlr4/Pcl2Parser.d \
./target/generated-sources/antlr4/Pcl2Visitor.d 


# Each subdirectory must supply rules for building sources it contributes
target/generated-sources/antlr4/%.o: ../target/generated-sources/antlr4/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/tiago/eclipse-workspace/Pickle2" -I"/home/tiago/eclipse-workspace/Pickle2/target/generated-sources/antlr4" -I/usr/local/include/antlr4-runtime -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


