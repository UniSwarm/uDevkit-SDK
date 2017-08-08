#/bin/bash

HEADER_PATH="/opt/microchip/xc32/v1.43/pic32mx/include/proc"

# $1 familly $2 file $3 regexp interrupt
function extract {
    CONTENT=''
    EQUS=''
    REGS=''
	echo ""
	echo "== $1"
	RES=$(cat ${HEADER_PATH}/$2 |sed -e '/'$3'[FEPS]:/,/__I[PCFSEC]\+[0-9]\+bits_t/!d' |sed -ne '/\([[:space:]]'$3'\|bits\)/p' |sed -e's/[ ]*unsigned[ ]*//' -e's/:.*//' -e's/\} __/>/' -e's/bits_t;//')

	for line in ${RES}
	do
		if [[ ${line} == ">"* ]]
		then
			for REG in ${REGS}
			do
				EQUS+="${line:1:${#line}-1} "${REG}'\n'
			done
			REGS=''
		else
			REGS+=${line}' '
		fi
	done

	EQUS=$(echo -e ${EQUS} |sort -k 2)
	while read line; do
		arr=(${line// / })
		if [ -n "$arr" ]; then
			printf "  #define _%-7s %sbits.%s\n" ${arr[1]} ${arr[0]} ${arr[1]}
		fi
	done <<<"$EQUS"
}

#UART
#extract "32MM GPL" "p32mm0016gpl020.h" "U[0-9]\+[RTE]*[XI]*I*"
#extract "32MM GPM" "p32mm0256gpm048.h" "U[0-9]\+[RTE]*[XI]*I*"
#extract "32MK" "p32mk1024mcf100.h" "U[0-9]\+[RTE]*[XI]*I*"
#extract "32MX3" "p32mx330f064l.h" "U[0-9]\+[RTE]*[XI]*I*"
#extract "32MX5" "p32mx575f512l.h" "U[0-9]\+[RTE]*[XI]*I*"
#extract "32MX7" "p32mx795f512h.h" "U[0-9]\+[RTE]*[XI]*I*"
#extract "32MZ" "p32mz2048efh100.h" "U[0-9]\+[RTE]*[XI]*I*"

#timer
#extract "32MM GPL" "p32mm0016gpl020.h" "T[0-9]\+I"
#extract "32MM GPM" "p32mm0256gpm048.h" "T[0-9]\+I"
#extract "32MK" "p32mk1024mcf100.h" "T[0-9]\+I"
#extract "32MX3" "p32mx330f064l.h" "T[0-9]\+I"
#extract "32MX5" "p32mx575f512l.h" "T[0-9]\+I"
#extract "32MX7" "p32mx795f512h.h" "T[0-9]\+I"
#extract "32MZ" "p32mz2048efh100.h" "T[0-9]\+I"

#I2C
extract "32MM GPL" "p32mm0016gpl020.h" "I2C[0-9]\+[MS]*I"
extract "32MM GPM" "p32mm0256gpm048.h" "I2C[0-9]\+[MS]*I"
extract "32MK" "p32mk1024mcf100.h" "I2C[0-9]\+[MS]*I"
extract "32MX3" "p32mx370f512l.h" "I2C[0-9]\+[MS]*I"
extract "32MX4" "p32mx470f512h.h" "I2C[0-9]\+[MS]*I"
extract "32MX5" "p32mx575f512l.h" "I2C[0-9]\+[MS]*I"
extract "32MX7" "p32mx795f512h.h" "I2C[0-9]\+[MS]*I"
extract "32MZ" "p32mz2048efh100.h" "I2C[0-9]\+[MS]*I"
