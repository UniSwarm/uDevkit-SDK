#/bin/bash

PATHPIC='/cygdrive/e/soft/Microchip/pic_file'

# $1 name $2 expression
function extract {
    egrep -rc ${PATHPIC}/dsPIC30 ${PATHPIC}/dsPIC33 -e $2 |sed -e 's/.*\///' -e's/\([A-Z0-9a-z]+\)/\1/' -e 's/\.PIC//' -e's/DSPIC/dsPIC/' |sort -t$':' -n -k2 -k1 > $1.txt
    NAME_UPPER=$(echo $1 | tr '[:lower:]' '[:upper:]')
    CONTENT=''
    FIRST=1
    for i in {1..16}
    do
        RES=$(cat $1.txt |grep ":${i}"|sort)
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
                device=$(echo ${dev}|cut -d: -f1)
                CONTENT+='defined(DEVICE_'${device}')'
                COUNT=$((COUNT+1))
            done
            CONTENT+='\r\n #define '${NAME_UPPER}'_COUNT '$i
        fi
    done
    CONTENT+='\r\n#else\r\n #define '${NAME_UPPER}'_COUNT 0\r\n#endif\r\n'
    echo -e ${CONTENT} > $1.h
}

#extract oc "OC[0-9]+CON[1]*\""
extract ic "IC[0-9]+CON[1]*\""
