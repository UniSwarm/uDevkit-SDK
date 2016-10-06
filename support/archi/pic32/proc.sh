#/bin/bash

PATHPIC='/cygdrive/e/soft/Microchip/pic_file'

# $1 name $2 expression
function count {
    egrep -rc ${PATHPIC}/32xxxx -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.PIC//' |sort -t$':' -n -k2 -k1 > $1.txt
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
                    ((${FIRST}==1)) && CONTENT+='\r\n#if ' || CONTENT+='\r\n#elif '
                    FIRST=0
                else
                    ((${COUNT}%3==0)) && CONTENT+=' \\\r\n || ' || CONTENT+=' || '
                fi
                device=$(echo ${dev}|sed -e's/\(.*\):[0-9]\+/\1/')
                CONTENT+='defined(DEVICE_'${device}')'
                COUNT=$((COUNT+1))
            done
            CONTENT+='\r\n #define '${NAME_UPPER}'_COUNT '$i
        fi
    done
    CONTENT+='\r\n#else\r\n #define '${NAME_UPPER}'_COUNT 0\r\n#endif\r\n'
    echo -e ${CONTENT} > $3
}

count uart "U[0-9]+MODE*\""
extract uart "PIC32" "uart_pic32.h"

count oc "OC[0-9]+CON[1]*\""
extract oc "PIC32" "oc_pic32.h"

count ic "IC[0-9]+CON[1]*\""
extract ic "PIC32" "ic_pic32.h"

count i2c "SFRDef.*I2C[0-9]*CON[1L]*\""
extract i2c "PIC32" "i2c_pic32.h"

count spi "SFRDef.*SPI[0-9]*CON*\""
extract spi "PIC32" "spi_pic32.h"

#count timer "SFRDef.*T[0-9]+CON*\""
#extract timer "PIC32" "timer_pic32.h"

#count pwm "SFRFieldDef.*PMOD0\""
