-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: project

project: project.c main_program.c 
	gcc -Ldl -o project $(LIBS)

clean: 
	$(RM) project

-include ../makefile.targets
