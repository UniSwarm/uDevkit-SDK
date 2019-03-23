Device dsPIC33CH128MP506
Hwtool SIM
Program "build/dspic33c.elf"
Reset MCLR
Sleep 100

set oscillator.frequencyunit Kilo
set oscillator.frequency 1

# set breakpoint at 0x108
#Break simulator.c:53
#Break *0x108

Run
print TMR1
Wait 5000

#write TMR1 1
print TMR1
Quit
