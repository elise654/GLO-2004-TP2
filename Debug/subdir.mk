################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Adresse.cpp \
../Annuaire.cpp \
../ArbreGenealogique.cpp \
../Personne.cpp \
../TP2.cpp 

OBJS += \
./Adresse.o \
./Annuaire.o \
./ArbreGenealogique.o \
./Personne.o \
./TP2.o 

CPP_DEPS += \
./Adresse.d \
./Annuaire.d \
./ArbreGenealogique.d \
./Personne.d \
./TP2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


