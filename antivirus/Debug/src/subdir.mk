################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/antivirus.c \
../src/antivirus1.c \
../src/progresso1.c 

OBJS += \
./src/antivirus.o \
./src/antivirus1.o \
./src/progresso1.o 

C_DEPS += \
./src/antivirus.d \
./src/antivirus1.d \
./src/progresso1.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


