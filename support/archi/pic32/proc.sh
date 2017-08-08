#/bin/bash

#PATHPIC='/cygdrive/c/Users/sebas/Desktop/edc'
PATHPIC='/home/seb/Documents/pic_file'

# $1 name $2 expression
function count {
    egrep -rc ${PATHPIC}/32xxxx/ -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/PIC\(.*\)\.PIC/\1/' |sort -t$':' -n -k2 -k1 > $1.txt
}

# $1 name $2 devfilter $3 fileout
function extract {
    NAME_UPPER=$(echo $1 | tr '[:lower:]' '[:upper:]')
    CONTENT=''
    FIRST=1
    for i in {1..16}
    do
        RES=$(cat $1.txt |grep ":${i}" |grep -E $2 | sort)
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
                device=$(echo ${dev}|sed -e's/\(.*\):[0-9]\+/\1/')
                CONTENT+='defined(DEVICE_'${device}')'
                COUNT=$((COUNT+1))
            done
            CONTENT+='\n #define '${NAME_UPPER}'_COUNT '$i
        fi
    done
    CONTENT+='\n#else\n #define '${NAME_UPPER}'_COUNT 0\n#endif\n'
    echo -e ${CONTENT} > $3
}

# gpio functions
function countgpio {
    egrep -rc ${PATHPIC}/32xxxx/PIC* -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.PIC//' |sort > $1.txt
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
    countgpio gpioA "SFRDef.*edc:cname=\"PORTA.*\""
    cp gpioA.txt gpio.txt
    for i in {B..L}
    do
        echo ${i}
        countgpio gpio${i} "SFRDef.*edc:cname=\"PORT${i}.*\""
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
    
    echo -e ${CONTENT} > gpio_pic32.h
}

# count uart "SFRDef.*edc:cname=\"U[0-9]+MODE*\""
# extract uart "32MX" "uart_pic32mx.h"
# extract uart "32M[ZMK]" "uart_pic32mz_mm_mk.h"

# count oc "SFRDef.*OC[0-9]+CON[1]*\""
# extract oc "32M" "oc_pic32.h"

# count ic "SFRDef.*IC[0-9]+CON[1]*\""
# extract ic "32M" "ic_pic32.h"

count i2c "SFRDef.*I2C[0-9]*CON[1L]*\""
extract i2c "32M" "i2c_pic32.h"

# count spi "SFRDef.*SPI[0-9]*CON*\""
# extract spi "32M" "spi_pic32.h"

#count timer "SFRDef.*T[0-9]+CON*\""
#extract timer "32M" "timer_pic32.h"

#count pwm "SFRFieldDef.*PMOD0\""

#count gpio "SFRDef.*edc:cname=\"PORT[A-Z]*\""
#gpioget

#count can "SFRDef.*C[0-9]FSTAT\""
#extract can "32M" "can_pic32.h"

#count rtc "SFRDef.*RTCCON\""
#extract rtc "32M" "rtc_pic32.h"

#count qei "SFRDef.*QEI[0-9]STAT\""
#extract qei "32M" "qei_pic32.h"
