#!/bin/bash
# INTERFACE="/usr/share/openocd/scripts/interface/jlink.cfg" # -f
# TARGET="/usr/share/openocd/scripts/target/mdr32f9q2i.cfg" # -f
# SWD="transport select swd" # -c
# PROG="program my_project.elf verify reset" # -c ("program /path/to/file.elf verify reset exit")
# openocd -f ${INTERFACE} -c "${SWD}" -f ${TARGET}

FIRMWARE=$1
#FIRMWARE="build/bin/pi485_firmware.elf"
openocd -s tcl \
-f openocd/jlink.cfg \
-f openocd/1986ve1t.cfg \
-c "init" \
-c "reset halt" \
-c "program ${FIRMWARE} verify exit"

#Мой скрипт ($1 - имя хекс файла):
#openocd -s tcl \
#-f interface/ftdi/olimex-arm-usb-tiny-h.cfg \
#-f interface/ftdi/olimex-arm-jtag-swd.cfg \
#-f target/1986ве1т.cfg \
#-c "init" \
#-c "reset halt" \
#-c "program $1" \
#-c "reset halt" \
#-c "verify_image $1" \
#-c "exit"

#На всякий случай для 1986ВЕ9х
#openocd -s tcl \
#-f interface/ftdi/olimex-arm-usb-tiny-h.cfg \
#-f interface/ftdi/olimex-arm-jtag-swd.cfg \
#-f target/mdr32f9q2i.cfg \
#-c "init" \
#-c "reset halt" \
#-c "program $1 verify exit"

# from https://forum.milandr.ru/viewtopic.php?f=33&t=216&start=90

# connect to openocd server: telnet localhost 4444
