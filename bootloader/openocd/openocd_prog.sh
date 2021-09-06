# from https://forum.milandr.ru/viewtopic.php?f=33&t=216&start=90

FIRMWARE=$1
openocd -s tcl \
-f openocd/jlink.cfg \
-f openocd/1986ve1t.cfg \
-c "init" \
-c "reset halt" \
-c "program ${FIRMWARE} verify exit"
