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
FILE_NAME = periph/${DRIVER}/${DRIVER}.mk
echo -e "ifndef ${DRIVER_UPPER}_DRIVER" > ${FILE_NAME}
echo -e "${DRIVER_UPPER}_DRIVER=" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "vpath %.c \$(DRIVERPATH)" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "HEADER += ${DRIVER}.h" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "ifeq (\$(ARCHI),\$(filter \$(ARCHI),pic24ep pic24f pic24fj pic24hj dspic30f dspic33ep dspic33ev dspic33fj))" >> ${FILE_NAME}
echo -e " SRC += ${DRIVER}_pic24dspic33.c" >> ${FILE_NAME}
echo -e " HEADER += ${DRIVER}_pic24dspic33.h" >> ${FILE_NAME}
echo -e "endif" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "endif" >> ${FILE_NAME}

# .h
FILE_NAME = periph/${DRIVER}/${DRIVER}.h
echo -e "/**" > ${FILE_NAME}
echo -e " * @file ${DRIVER}.h" >> ${FILE_NAME}
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${FILE_NAME}
echo -e " * @copyright Robotips 2016" >> ${FILE_NAME}
echo -e " *" >> ${FILE_NAME}
echo -e " * @date ${DATE} " >> ${FILE_NAME}
echo -e " * " >> ${FILE_NAME}
echo -e " * @brief ${DESC}" >> ${FILE_NAME}
echo -e " */" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#ifndef ${DRIVER_UPPER}_H" >> ${FILE_NAME}
echo -e "#define ${DRIVER_UPPER}_H" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#include \"driver/device.h\"" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#if defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33fj)" >> ${FILE_NAME}
echo -e " #include \"${DRIVER}_pic24dspic33.h\"" >> ${FILE_NAME}
echo -e "#else" >> ${FILE_NAME}
echo -e " #error Unsuported ARCHI" >> ${FILE_NAME}
echo -e "#endif" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#endif // ${DRIVER_UPPER}_H" >> ${FILE_NAME}

# _dspic.c
FILE_NAME = periph/${DRIVER}/${DRIVER}_pic24dspic33.c
echo -e "/**" > ${FILE_NAME}
echo -e " * @file ${DRIVER}_pic24dspic33.c" >> ${FILE_NAME}
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${FILE_NAME}
echo -e " * @copyright Robotips 2016" >> ${FILE_NAME}
echo -e " *" >> ${FILE_NAME}
echo -e " * @date ${DATE} " >> ${FILE_NAME}
echo -e " * " >> ${FILE_NAME}
echo -e " * @brief ${DESC}" >> ${FILE_NAME}
echo -e " */" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#include \"${DRIVER}_pic24dspic33.h\"" >> ${FILE_NAME}

# _dspic.h
FILE_NAME = periph/${DRIVER}/${DRIVER}_pic24dspic33.h
echo -e "/**" > ${FILE_NAME}
echo -e " * @file ${DRIVER}_dspic.h" >> ${FILE_NAME}
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${FILE_NAME}
echo -e " * @copyright Robotips 2016" >> ${FILE_NAME}
echo -e " *" >> ${FILE_NAME}
echo -e " * @date ${DATE} " >> ${FILE_NAME}
echo -e " * " >> ${FILE_NAME}
echo -e " * @brief ${DESC}" >> ${FILE_NAME}
echo -e " */" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#ifndef ${DRIVER_UPPER}_DSPIC_H" >> ${FILE_NAME}
echo -e "#define ${DRIVER_UPPER}_DSPIC_H" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#include \"${DRIVER}_pic24dspic33.h\"" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "" >> ${FILE_NAME}
echo -e "#endif // ${DRIVER_UPPER}_DSPIC_H" >> ${FILE_NAME}

# include.h
echo -e "#include \"../../support/driver/periph/${DRIVER}/${DRIVER}.h\"" > ../../include/driver/${DRIVER}.h
