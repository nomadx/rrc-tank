################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../entities/AbstractTank.cpp \
../entities/IEntity.cpp \
../entities/TankBody.cpp \
../entities/TankTurret.cpp \
../entities/TestEntity.cpp 

OBJS += \
./entities/AbstractTank.o \
./entities/IEntity.o \
./entities/TankBody.o \
./entities/TankTurret.o \
./entities/TestEntity.o 

CPP_DEPS += \
./entities/AbstractTank.d \
./entities/IEntity.d \
./entities/TankBody.d \
./entities/TankTurret.d \
./entities/TestEntity.d 


# Each subdirectory must supply rules for building sources it contributes
entities/%.o: ../entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


