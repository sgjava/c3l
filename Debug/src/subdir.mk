################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/baseline.c \
../src/ciadec.c \
../src/ciagk.c \
../src/ciagkc.c \
../src/ciagks.c \
../src/ciaglkc.c \
../src/ciagrkc.c \
../src/graphics.c \
../src/grbezier.c \
../src/grellip.c \
../src/grline.c \
../src/keydemo.c \
../src/rtcgd.c \
../src/rtcgr.c \
../src/rtcgt.c \
../src/rtcsm.c \
../src/rtcsr.c \
../src/screen.c \
../src/sid.c \
../src/vdcand.c \
../src/vdcbmp.c \
../src/vdcchrm.c \
../src/vdccpym.c \
../src/vdcdemo1.c \
../src/vdcdemo2.c \
../src/vdcfmem.c \
../src/vdcin.c \
../src/vdcmchr.c \
../src/vdcor.c \
../src/vdcout.c \
../src/vdcscr.c \
../src/vdcsr.c \
../src/vic.c \
../src/vicbmp.c \
../src/vicdemo1.c \
../src/vicdemo2.c \
../src/vicdemo3.c \
../src/vicdemo4.c \
../src/vicscr.c \
../src/vicspr.c 

C_DEPS += \
./src/baseline.d \
./src/ciadec.d \
./src/ciagk.d \
./src/ciagkc.d \
./src/ciagks.d \
./src/ciaglkc.d \
./src/ciagrkc.d \
./src/graphics.d \
./src/grbezier.d \
./src/grellip.d \
./src/grline.d \
./src/keydemo.d \
./src/rtcgd.d \
./src/rtcgr.d \
./src/rtcgt.d \
./src/rtcsm.d \
./src/rtcsr.d \
./src/screen.d \
./src/sid.d \
./src/vdcand.d \
./src/vdcbmp.d \
./src/vdcchrm.d \
./src/vdccpym.d \
./src/vdcdemo1.d \
./src/vdcdemo2.d \
./src/vdcfmem.d \
./src/vdcin.d \
./src/vdcmchr.d \
./src/vdcor.d \
./src/vdcout.d \
./src/vdcscr.d \
./src/vdcsr.d \
./src/vic.d \
./src/vicbmp.d \
./src/vicdemo1.d \
./src/vicdemo2.d \
./src/vicdemo3.d \
./src/vicdemo4.d \
./src/vicscr.d \
./src/vicspr.d 

OBJS += \
./src/baseline.o \
./src/ciadec.o \
./src/ciagk.o \
./src/ciagkc.o \
./src/ciagks.o \
./src/ciaglkc.o \
./src/ciagrkc.o \
./src/graphics.o \
./src/grbezier.o \
./src/grellip.o \
./src/grline.o \
./src/keydemo.o \
./src/rtcgd.o \
./src/rtcgr.o \
./src/rtcgt.o \
./src/rtcsm.o \
./src/rtcsr.o \
./src/screen.o \
./src/sid.o \
./src/vdcand.o \
./src/vdcbmp.o \
./src/vdcchrm.o \
./src/vdccpym.o \
./src/vdcdemo1.o \
./src/vdcdemo2.o \
./src/vdcfmem.o \
./src/vdcin.o \
./src/vdcmchr.o \
./src/vdcor.o \
./src/vdcout.o \
./src/vdcscr.o \
./src/vdcsr.o \
./src/vic.o \
./src/vicbmp.o \
./src/vicdemo1.o \
./src/vicdemo2.o \
./src/vicdemo3.o \
./src/vicdemo4.o \
./src/vicscr.o \
./src/vicspr.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/baseline.d ./src/baseline.o ./src/ciadec.d ./src/ciadec.o ./src/ciagk.d ./src/ciagk.o ./src/ciagkc.d ./src/ciagkc.o ./src/ciagks.d ./src/ciagks.o ./src/ciaglkc.d ./src/ciaglkc.o ./src/ciagrkc.d ./src/ciagrkc.o ./src/graphics.d ./src/graphics.o ./src/grbezier.d ./src/grbezier.o ./src/grellip.d ./src/grellip.o ./src/grline.d ./src/grline.o ./src/keydemo.d ./src/keydemo.o ./src/rtcgd.d ./src/rtcgd.o ./src/rtcgr.d ./src/rtcgr.o ./src/rtcgt.d ./src/rtcgt.o ./src/rtcsm.d ./src/rtcsm.o ./src/rtcsr.d ./src/rtcsr.o ./src/screen.d ./src/screen.o ./src/sid.d ./src/sid.o ./src/vdcand.d ./src/vdcand.o ./src/vdcbmp.d ./src/vdcbmp.o ./src/vdcchrm.d ./src/vdcchrm.o ./src/vdccpym.d ./src/vdccpym.o ./src/vdcdemo1.d ./src/vdcdemo1.o ./src/vdcdemo2.d ./src/vdcdemo2.o ./src/vdcfmem.d ./src/vdcfmem.o ./src/vdcin.d ./src/vdcin.o ./src/vdcmchr.d ./src/vdcmchr.o ./src/vdcor.d ./src/vdcor.o ./src/vdcout.d ./src/vdcout.o ./src/vdcscr.d ./src/vdcscr.o ./src/vdcsr.d ./src/vdcsr.o ./src/vic.d ./src/vic.o ./src/vicbmp.d ./src/vicbmp.o ./src/vicdemo1.d ./src/vicdemo1.o ./src/vicdemo2.d ./src/vicdemo2.o ./src/vicdemo3.d ./src/vicdemo3.o ./src/vicdemo4.d ./src/vicdemo4.o ./src/vicscr.d ./src/vicscr.o ./src/vicspr.d ./src/vicspr.o

.PHONY: clean-src

