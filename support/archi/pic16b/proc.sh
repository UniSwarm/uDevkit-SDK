#/bin/bash

PATHPIC='/cygdrive/e/soft/Microchip/pic_file'

# $1 name $2 expression
function count {
    egrep -rc ${PATHPIC}/dsPIC30 ${PATHPIC}/dsPIC33 -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.PIC//' -e's/DSPIC/dsPIC/' |sort -t$':' -n -k2 -k1 > $1.txt
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
                device=$(echo ${dev}|sed -e's/[ds]*PIC\(.*\):[0-9]\+/\1/')
                CONTENT+='defined(DEVICE_'${device}')'
                COUNT=$((COUNT+1))
            done
            CONTENT+='\r\n #define '${NAME_UPPER}'_COUNT '$i
        fi
    done
    CONTENT+='\r\n#else\r\n #define '${NAME_UPPER}'_COUNT 0\r\n#endif\r\n'
    echo -e ${CONTENT} > $3
}

count oc "OC[0-9]+CON[1]*\""
extract oc "dsPIC33E|PIC24E" "oc_24e_33e.h"
extract oc "dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "oc_30f33fj24f24hj.h"

count ic "OC[0-9]+CON[1]*\""
extract ic "dsPIC33E|PIC24E" "ic_24e_33e.h"
extract ic "dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "ic_30f33fj24f24hj.h"

count i2c "SFRDef.*I2C[0-9]*CON[1L]*\""
extract i2c "dsPIC33E|PIC24E|dsPIC30F|dsPIC33FJ|PIC24F|PIC24HJ" "i2c_24_33_30.h"
