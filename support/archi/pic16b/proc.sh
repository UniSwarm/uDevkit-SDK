#/bin/bash

#PATHPIC='/cygdrive/c/Users/sebas/Desktop/edc/'
PATHPIC='/home/seb/Documents/pic_file'
PATHXC16='/opt/microchip/xc16/v1.31'

# grep edc:AuxCodeSector *.PIC |sed -e's/\([^:]*\)\.PIC:.*edc:beginaddr="\([0-9xA-Fa-f]\+\)".*edc:endaddr="\([0-9xA-Fa-f]\+\)".*"\/>/\1-\2-\3/'
# grep "edc:CodeSector.*edc:regionid=\"program\"" *.PIC |sed -e's/\([^:]*\)\.PIC:.*edc:beginaddr="\([0-9xA-Fa-f]\+\)".*edc:endaddr="\([0-9xA-Fa-f]\+\)".*\/>/\2:\3:\1/'|sed -e 's/0x0*\([0-9a-fA-F]*\)/0x\U\1\E/g'|sort
# grep "<edc:DataSpace" *.PIC |sed -e's/\([^:]*\)\.PIC:.*edc:xbeginaddr="\([0-9xA-Fa-f]\+\)".*edc:xendaddr="\([0-9xA-Fa-f]\+\)".*/\2:\3:\1/'|sed -e 's/0x0*\([0-9a-fA-F]*\)/0x00000\U\1\E/g;s/0x0*\([0-9A-F]\{6,\}\)$/x0\1/'|sort

# $1 name $2 expression
function count {
    egrep -rc ${PATHPIC}/dsPIC30 ${PATHPIC}/dsPIC33 -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.PIC//' -e's/DSPIC/dsPIC/' |sort -t$':' -n -k2 -k1 > $1.txt
}

# $1 name $2 expression
function countxc16 {
    egrep -rc ${PATHXC16}/support/*/h -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.h//' -e's/^p24/PIC24/' -e's/^p3/dsPIC3/' |grep PIC |grep -v xxx|sort -t$':' -n -k2 -k1 > $1.txt
}

# gpio functions
function countgpio {
    egrep -rc ${PATHPIC}/dsPIC30 ${PATHPIC}/dsPIC33 -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.PIC//' -e's/DSPIC/dsPIC/' |sort > $1.txt
}
function printports {
    OTHERPORT=$1
    PORTCOUNT=0
    for i in {A..L}
    do
        PORT=$(echo ${OTHERPORT}|sed -e's/\([0-1]\):.*/\1/')
        OTHERPORT=$(echo ${OTHERPORT}|sed -e's/[0-1]:\(.*\)/\1/')
        if [ "$PORT" == "1" ]
        then
            CONTENT+='\n  #defined GPIO_HAVE_PORT'${i}
            PORTCOUNT=$((PORTCOUNT+1))
        fi
    done
    CONTENT+='\n  #defined GPIO_COUNT '${PORTCOUNT}
}
function gpioget {
    echo "A"
    countgpio gpioA "SFRDef.*PORTA.*\""
    cp gpioA.txt gpio.txt
    for i in {B..L}
    do
        echo ${i}
        countgpio gpio${i} "SFRDef.*PORT${i}.*\""
        join -1 1 -2 1 -t : gpio.txt gpio${i}.txt > gpiom.txt
        cp gpiom.txt gpio.txt
    done
    cat gpiom.txt | sort -t: -k2 -k3 -k4 -k5 -k6 -k7 -k8 -k9 -k10 -k11 -k12 -k13 > gpio.txt
    rm gpio?.txt
    
    pgpio_port="00"
    RES=$(cat gpio.txt | sort -t: -k2 -k3 -k4 -k5 -k6 -k7 -k8 -k9 -k10 -k11 -k12 -k13)
    for dev in ${RES}
    do
        device=$(echo ${dev}|sed -e's/[ds]*PIC\([^:]*\):.*/\1/')
        gpio_port=$(echo ${dev}|sed -e's/[^:]*:\(.*\)/\1/')
        
        echo ${device}
        
        if [ "$gpio_port" != "$pgpio_port" ]
        then
            if ((${COUNT}!=0))
            then
                printports ${pgpio_port}
            fi
            COUNT=0
        fi
        
        if ((${COUNT}==0))
        then
            ((${FIRST}==1)) && CONTENT+='\n#if ' || CONTENT+='\n#elif '
            FIRST=0
        else
            ((${COUNT}%3==0)) && CONTENT+=' \\\n || ' || CONTENT+=' || '
        fi
        CONTENT+='defined(DEVICE_'${device}')'
        COUNT=$((COUNT+1))
        
        pgpio_port=${gpio_port}
    done
    printports ${pgpio_port}
    CONTENT+='\n#endif'
    
    echo -e ${CONTENT} > gpio_pic24_dspic30f_dspic33f.h
}

function memory {
    CONTENT=''
    RES=$(grep -e '<edc:DataSpace.*edc:xbeginaddr' -e '<edc:EDSWindowSector.*beginaddr' ${PATHPIC}/dsPIC33/*.PIC ${PATHPIC}/dsPIC30/*.PIC |sed -e's/.*\/\([^:]*\)\.PIC:.*edc:x*beginaddr="\([0-9xA-Fa-f]\+\)".*edc:x*endaddr="\([0-9xA-Fa-f]\+\)".*/\2:\3:\1/'|sed -e 's/0x0*\([0-9a-fA-F]*\)/0x00000\U\1\E/g;s/0x0*\([0-9A-F]\{4,\}\)/0x\1/g'|sort)
    FIRST=1
    COUNT=0
    for dev in ${RES}
    do
        device=$(echo ${dev}|sed -e's/.*:.*:[DS]*PIC\(.*\)/\1/')
        memstart=$(echo ${dev}|sed -e's/\(0x[0-9A-F]*\):\(0x[0-9A-F]*\):.*/\1/')
        memend=$(echo ${dev}|sed -e's/\(0x[0-9A-F]*\):\(0x[0-9A-F]*\):.*/\2/')
        
        if [ "$memstart" != "$pmemstart" ] || [ "$memend" != "$pmemend" ]
        then
            if ((${COUNT}!=0))
            then
                CONTENT+='\n  #defined MEMSTART '${pmemstart}
                CONTENT+='\n  #defined MEMEND '${pmemend}
            fi
            COUNT=0
        fi
        
        if ((${COUNT}==0))
        then
            ((${FIRST}==1)) && CONTENT+='\n#if ' || CONTENT+='\n#elif '
            FIRST=0
        else
            ((${COUNT}%3==0)) && CONTENT+=' \\\n || ' || CONTENT+=' || '
        fi
        CONTENT+='defined(DEVICE_'${device}')'
        COUNT=$((COUNT+1))
        
        pmemstart=${memstart}
        pmemend=${memend}
    done
    CONTENT+='\n  #defined MEMSTART '${pmemstart}
    CONTENT+='\n  #defined MEMEND '${pmemend}
    CONTENT+='\n#endif'
    
    echo -e ${CONTENT} > mem.txt
}

# $1 name $2 devfilter $3 fileout
function extract {
    NAME_UPPER=$(echo $1 | tr '[:lower:]' '[:upper:]')
    CONTENT=''
    FIRST=1
    for i in {0..32}
    do
        RES=$(cat $1.txt |egrep ":${i}$" |grep -E "$2" | sort)
        if [ -n "${RES}" ]; then
            COUNT=0
            for dev in ${RES}
            do
                if ((${COUNT}==0))
                then
                    ((${FIRST}==1)) && CONTENT+='\n#if ' || CONTENT+='\n#elif '
                    FIRST=0
                else
                    ((${COUNT}%3==0)) && CONTENT+=' \\\n || ' || CONTENT+=' || '
                fi
                device=$(echo ${dev}|sed -e's/[ds]*PIC\(.*\):[0-9]\+/\1/')
                CONTENT+='defined(DEVICE_'${device}')'
                COUNT=$((COUNT+1))
            done
            CONTENT+='\n #define '${NAME_UPPER}'_COUNT '$i
        fi
    done
    CONTENT+='\n#else\n #define '${NAME_UPPER}'_COUNT 0\n#endif\n'
    echo -e ${CONTENT} > $3
}

#count uart "URXEN"
#extract uart "dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "urxen.h"
#count uart "SFRDef.*U[0-9]+MODE"
#extract uart "dsPIC30F[0-9]+A*:" "uart_dspic30f.h"

#count oc "OC[0-9]+CON[1]*\""
#extract oc "dsPIC33E|PIC24E" "oc_24e_33e.h"
#extract oc "dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "oc_30f33fj24f24hj.h"

#count ic "IC[0-9]+CON[1]*\""
#extract ic "dsPIC33E|PIC24E" "ic_24e_33e.h"
#extract ic "dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "ic_30f33fj24f24hj.h"

#count i2c "SFRDef.*I2C[0-9]*CON[1L]*\""
#extract i2c "dsPIC33E|PIC24E|dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "i2c_24_33_30.h"

#countxc16 timer "define[[:space:]]T[0-9]*CON[[:space:]]T[0-9]*CON"
#extract timer "dsPIC33E|PIC24E|dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "timer_24_33_30.h"

#count spi "SFRDef.*SPI[0-9]*CON[1L]*\""
#extract spi "dsPIC33E|PIC24E" "spi_pic24e_dspic33e.h"
#extract spi "dsPIC33FJ|PIC24F|PIC24HJ" "spi_pic24f_dspic33f.h"
#extract spi "dsPIC30F" "spi_dspic30.h"

#count pwm "SFRFieldDef.*PMOD0\""

#gpioget
#extract gpio ".*" "gpio_dspic30.h"

#count can "SFRDef.*C[0-9]CTRL1*\""
#extract can "dsPIC33|PIC24" "can_pic24_dspic33.h"
#extract can "dsPIC30" "can_dspic30.h"

#count rtc "SFRDef.*RCFGCAL\""
#extract rtc "dsPIC33|PIC24" "rtc_pic24_dspic33.h"

grep -rc "PLLPOST" /opt/microchip/xc16/v1.31/support/dsPIC33*/h |grep :0 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.h//' -e's/^p24/PIC24/' -e's/^p3/dsPIC3/' |grep PIC |grep -v xxx|sort -t$':' -n -k2 -k1 > sysclock.txt
extract sysclock ".*" "sysclock.h"


#memory
