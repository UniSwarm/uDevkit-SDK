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

DATE=$(LANG="en_US.utf8" TZ="Etc/GMT-2" date +'%B %d, %Y, %H:%M %p')
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
echo -e "HEADER += ${DRIVER}.h" >> ${DRIVER}/${DRIVER}.mk
echo -e "" >> ${DRIVER}/${DRIVER}.mk
echo -e "ifeq (\$(ARCHI),\$(filter \$(ARCHI),dspic33ep dspic33fj))" >> ${DRIVER}/${DRIVER}.mk
echo -e " SRC += ${DRIVER}_dspic.c" >> ${DRIVER}/${DRIVER}.mk
echo -e " HEADER += ${DRIVER}_dspic.h" >> ${DRIVER}/${DRIVER}.mk
echo -e "endif" >> ${DRIVER}/${DRIVER}.mk
echo -e "" >> ${DRIVER}/${DRIVER}.mk
echo -e "endif" >> ${DRIVER}/${DRIVER}.mk

# .h
echo -e "/**" > ${DRIVER}/${DRIVER}.h
echo -e " * @file ${DRIVER}.h" >> ${DRIVER}/${DRIVER}.h
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${DRIVER}/${DRIVER}.h
echo -e " * @copyright Robotips 2016" >> ${DRIVER}/${DRIVER}.h
echo -e " *" >> ${DRIVER}/${DRIVER}.h
echo -e " * @date ${DATE} " >> ${DRIVER}/${DRIVER}.h
echo -e " * " >> ${DRIVER}/${DRIVER}.h
echo -e " * @brief ${DESC}" >> ${DRIVER}/${DRIVER}.h
echo -e " */" >> ${DRIVER}/${DRIVER}.h
echo -e "" >> ${DRIVER}/${DRIVER}.h
echo -e "#ifndef ${DRIVER_UPPER}_H" >> ${DRIVER}/${DRIVER}.h
echo -e "#define ${DRIVER_UPPER}_H" >> ${DRIVER}/${DRIVER}.h
echo -e "" >> ${DRIVER}/${DRIVER}.h
echo -e "#include \"driver/device.h\"" >> ${DRIVER}/${DRIVER}.h
echo -e "" >> ${DRIVER}/${DRIVER}.h
echo -e "#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)" >> ${DRIVER}/${DRIVER}.h
echo -e " #include \"${DRIVER}_dspic.h\"" >> ${DRIVER}/${DRIVER}.h
echo -e "#else" >> ${DRIVER}/${DRIVER}.h
echo -e " #error Unsuported ARCHI" >> ${DRIVER}/${DRIVER}.h
echo -e "#endif" >> ${DRIVER}/${DRIVER}.h
echo -e "" >> ${DRIVER}/${DRIVER}.h
echo -e "" >> ${DRIVER}/${DRIVER}.h
echo -e "" >> ${DRIVER}/${DRIVER}.h
echo -e "#endif // ${DRIVER_UPPER}_H" >> ${DRIVER}/${DRIVER}.h

# _dspic.c
echo -e "/**" > ${DRIVER}/${DRIVER}_dspic.c
echo -e " * @file ${DRIVER}_dspic.c" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " * @copyright Robotips 2016" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " *" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " * @date ${DATE} " >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " * " >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " * @brief ${DESC}" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e " */" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e "" >> ${DRIVER}/${DRIVER}_dspic.c
echo -e "#include \"${DRIVER}_dspic.h\"" >> ${DRIVER}/${DRIVER}_dspic.c

# _dspic.h
echo -e "/**" > ${DRIVER}/${DRIVER}_dspic.h
echo -e " * @file ${DRIVER}_dspic.h" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " * @copyright Robotips 2016" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " *" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " * @date ${DATE} " >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " * " >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " * @brief ${DESC}" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e " */" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "#ifndef ${DRIVER_UPPER}_DSPIC_H" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "#define ${DRIVER_UPPER}_DSPIC_H" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "#include \"${DRIVER}_dspic.h\"" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "" >> ${DRIVER}/${DRIVER}_dspic.h
echo -e "#endif // ${DRIVER_UPPER}_DSPIC_H" >> ${DRIVER}/${DRIVER}_dspic.h

# include.h
echo -e "#include \"../../support/driver/${DRIVER}/${DRIVER}.h\"" > ../../include/driver/${DRIVER}.h
