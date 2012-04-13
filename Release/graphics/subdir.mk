################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../graphics/Camera.cpp \
../graphics/Shader.cpp \
../graphics/ShaderManager.cpp \
../graphics/ShaderProgram.cpp 

OBJS += \
./graphics/Camera.o \
./graphics/Shader.o \
./graphics/ShaderManager.o \
./graphics/ShaderProgram.o 

CPP_DEPS += \
./graphics/Camera.d \
./graphics/Shader.d \
./graphics/ShaderManager.d \
./graphics/ShaderProgram.d 


# Each subdirectory must supply rules for building sources it contributes
graphics/%.o: ../graphics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


