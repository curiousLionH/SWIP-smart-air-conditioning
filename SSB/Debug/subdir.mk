################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../submodule_button.c \
../submodule_buzzer.c \
../submodule_ccu60.c \
../submodule_eru.c \
../submodule_gtm.c \
../submodule_init.c \
../submodule_led.c \
../submodule_mode.c \
../submodule_motor.c \
../submodule_vadc.c 

OBJS += \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./submodule_button.o \
./submodule_buzzer.o \
./submodule_ccu60.o \
./submodule_eru.o \
./submodule_gtm.o \
./submodule_init.o \
./submodule_led.o \
./submodule_mode.o \
./submodule_motor.o \
./submodule_vadc.o 

COMPILED_SRCS += \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./submodule_button.src \
./submodule_buzzer.src \
./submodule_ccu60.src \
./submodule_eru.src \
./submodule_gtm.src \
./submodule_init.src \
./submodule_led.src \
./submodule_mode.src \
./submodule_motor.src \
./submodule_vadc.src 

C_DEPS += \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./submodule_button.d \
./submodule_buzzer.d \
./submodule_ccu60.d \
./submodule_eru.d \
./submodule_gtm.d \
./submodule_init.d \
./submodule_led.d \
./submodule_mode.d \
./submodule_motor.d \
./submodule_vadc.d 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fC:/Projects/02_embedded_mcu/project_0315/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


