 # mdr1986ve1t bootloader
 This is demo application for mdr1986ve1t bootloader<br>
 demo_app for "LDM-HELPER-K1986BE1QI ver.2.12" board<br>

dirs:<br>
bootloader - bootloader project<br>
demo_app - demo application project<br>
util - python utility for writing firmware<br>

 # Build
 make
 
# How to use
After the build, there will be a bootloader_and_app.hex file in the build directory. This file is used as initial firwmare. Program it with jtag or 1986VE1WSD.exe. Then make changes to the "demo_app" project and the resulting firmware can be programmed using the "prog.py" utility.