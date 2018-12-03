################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../hello.cfg 

CMD_SRCS += \
../CC1350_LAUNCHXL_TIRTOS.cmd 

C_SRCS += \
../CC1350_LAUNCHXL.c \
../CC1350_LAUNCHXL_fxns.c \
../Task4.c \
../ccfg.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./CC1350_LAUNCHXL.d \
./CC1350_LAUNCHXL_fxns.d \
./Task4.d \
./ccfg.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./CC1350_LAUNCHXL.obj \
./CC1350_LAUNCHXL_fxns.obj \
./Task4.obj \
./ccfg.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"CC1350_LAUNCHXL.obj" \
"CC1350_LAUNCHXL_fxns.obj" \
"Task4.obj" \
"ccfg.obj" 

C_DEPS__QUOTED += \
"CC1350_LAUNCHXL.d" \
"CC1350_LAUNCHXL_fxns.d" \
"Task4.d" \
"ccfg.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../CC1350_LAUNCHXL.c" \
"../CC1350_LAUNCHXL_fxns.c" \
"../Task4.c" \
"../ccfg.c" 


