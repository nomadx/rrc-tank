################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/AbstractState.cpp \
../game/Game.cpp \
../game/GameState.cpp \
../game/Intro.cpp 

OBJS += \
./game/AbstractState.o \
./game/Game.o \
./game/GameState.o \
./game/Intro.o 

CPP_DEPS += \
./game/AbstractState.d \
./game/Game.d \
./game/GameState.d \
./game/Intro.d 


# Each subdirectory must supply rules for building sources it contributes
game/%.o: ../game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


