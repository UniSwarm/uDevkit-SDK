#!/bin/bash

if [ -z "$1" ]; then 
	echo "You need to specify the name"
	exit
fi

if [ -z "$2" ]; then 
	echo "You need to specify a description as param 2"
	exit
fi

mkdir $1

DATE=$(LANG=en_US.utf8 date +'%B %d, %Y, %H:%M %p')
echo $DATE
DESC=$2
DRIVER=$1
DRIVER_UPPER=$(echo $DRIVER | tr '[:lower:]' '[:upper:]')
echo ${DRIVER_UPPER}

# mk
echo -e "ifndef ${DRIVER_UPPER}_DRIVER" > ${DRIVER}/${DRIVER}.mk
echo -e "${DRIVER_UPPER}_DRIVER=" >> ${DRIVER}/${DRIVER}.mk
echo -e "" >> ${DRIVER}/${DRIVER}.mk
echo -e "vpath %.c \$(DRIVERPATH)" >> ${DRIVER}/${DRIVER}.mk
echo -e "" >> ${DRIVER}/${DRIVER}.mk
echo -e "SRC += ${DRIVER}.c" >> ${DRIVER}/${DRIVER}.mk
echo -e "HEADER += ${DRIVER}.h" >> ${DRIVER}/${DRIVER}.mk
echo -e "" >> ${DRIVER}/${DRIVER}.mk
echo -e "ifeq (\$(ARCHI),\$(filter \$(ARCHI),dspic33ep dspic33fj))" >> ${DRIVER}/${DRIVER}.mk
echo -e " SRC += ${DRIVER}_dspic.c" >> ${DRIVER}/${DRIVER}.mk
echo -e " HEADER += ${DRIVER}_dspic.h" >> ${DRIVER}/${DRIVER}.mk
echo -e "endif" >> ${DRIVER}/${DRIVER}.mk
echo -e "" >> ${DRIVER}/${DRIVER}.mk
echo -e "endif" >> ${DRIVER}/${DRIVER}.mk

# .c
echo -e "/**\n" \
" * @file ${DRIVER}.c\n" \
" * @author Sebastien CAUX (sebcaux)\n" \
" * @copyright Robotips 2016\n" \
" *\n" \
" * @date ${DATE} \n" \
" * \n" \
" * @brief ${DESC}\n" \
" */\n" \
"\n" \
"#include \"${DRIVER}.h\"" > ${DRIVER}/${DRIVER}.c

# .h
echo -e "/**\n" \
" * @file ${DRIVER}.h\n" \
" * @author Sebastien CAUX (sebcaux)\n" \
" * @copyright Robotips 2016\n" \
" *\n" \
" * @date ${DATE} \n" \
" * \n" \
" * @brief ${DESC}\n" \
" */\n" \
"\n" \
"#ifndef ${DRIVER_UPPER}_H\n" \
"#define ${DRIVER_UPPER}_H\n" \
"\n" \
"#include \"board.h\"\n" \
"#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)\n" \
" #include \"${DRIVER}_dspic.h\"\n" \
"#else\n" \
" #error Unsuported ARCHI\n" \
"#endif\n" \
"\n" \
"#endif // ${DRIVER_UPPER}_H" > ${DRIVER}/${DRIVER}.h

# _dspic.c
echo -e "/**\n" \
" * @file ${DRIVER}_dspic.c\n" \
" * @author Sebastien CAUX (sebcaux)\n" \
" * @copyright Robotips 2016\n" \
" *\n" \
" * @date ${DATE} \n" \
" * \n" \
" * @brief ${DESC}\n" \
" */\n" \
"\n" \
"#include \"${DRIVER}_dspic.h\"" > ${DRIVER}/${DRIVER}_dspic.c

# _dspic.h
echo -e "/**\n" \
" * @file ${DRIVER}_dspic.h\n" \
" * @author Sebastien CAUX (sebcaux)\n" \
" * @copyright Robotips 2016\n" \
" *\n" \
" * @date ${DATE} \n" \
" * \n" \
" * @brief ${DESC}\n" \
" */\n" \
"\n" \
"#ifndef ${DRIVER_UPPER}_DSPIC_H\n" \
"#define ${DRIVER_UPPER}_DSPIC_H\n" \
"\n" \
"\n" \
"#endif // ${DRIVER_UPPER}_DSPIC_H" > ${DRIVER}/${DRIVER}_dspic.h

# include.h
echo -e "#include \"../../support/driver/${DRIVER}/${DRIVER}.h\"" > ../../include/driver/${DRIVER}.h
