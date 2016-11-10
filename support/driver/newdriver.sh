#!/bin/bash

if [ -z "$1" ]; then
	echo "You need to specify the name"
	exit
fi

if [ -z "$2" ]; then
	echo "You need to specify a description as param 2"
	exit
fi

mkdir periph/$1

DATE=$(LANG="en_US.utf8" TZ="Etc/GMT-2" date +'%B %d, %Y, %H:%M %p')
echo $DATE
DESC=$2
DRIVER=$1
DRIVER_UPPER=$(echo $DRIVER | tr '[:lower:]' '[:upper:]')
echo ${DRIVER_UPPER}

# mk
FILENAME=periph/${DRIVER}/${DRIVER}.mk
echo -e "ifndef ${DRIVER_UPPER}_DRIVER" > ${FILENAME}
echo -e "${DRIVER_UPPER}_DRIVER=" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "vpath %.c \$(DRIVERPATH)" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "HEADER += ${DRIVER}.h" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "ifeq (\$(ARCHI),\$(filter \$(ARCHI),pic24ep pic24f pic24fj pic24hj dspic30f dspic33ep dspic33ev dspic33fj))" >> ${FILENAME}
echo -e " ARCHI_SRC += ${DRIVER}_pic24_dspic30_dspic33.c" >> ${FILENAME}
echo -e " HEADER += ${DRIVER}_pic24_dspic30_dspic33.h" >> ${FILENAME}
echo -e "endif" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "endif" >> ${FILENAME}

# .h
FILENAME=periph/${DRIVER}/${DRIVER}.h
echo -e "/**" > ${FILENAME}
echo -e " * @file ${DRIVER}.h" >> ${FILENAME}
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${FILENAME}
echo -e " * @copyright Robotips 2016" >> ${FILENAME}
echo -e " *" >> ${FILENAME}
echo -e " * @date ${DATE} " >> ${FILENAME}
echo -e " * " >> ${FILENAME}
echo -e " * @brief ${DESC}" >> ${FILENAME}
echo -e " */" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#ifndef ${DRIVER_UPPER}_H" >> ${FILENAME}
echo -e "#define ${DRIVER_UPPER}_H" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#include \"driver/device.h\"" >> ${FILENAME}
echo -e "" >> ${FILENAME}

echo -e "// ====== device assignation ======" >> ${FILENAME}
echo -e "rt_dev_t ${DRIVER}_getFreeDevice();" >> ${FILENAME}
echo -e "void ${DRIVER}_releaseDevice(rt_dev_t device);" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "// ==== device enable/disable =====" >> ${FILENAME}
echo -e "int ${DRIVER}_enable(rt_dev_t device);" >> ${FILENAME}
echo -e "int ${DRIVER}_disable(rt_dev_t device);" >> ${FILENAME}

echo -e "" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24fv) || defined(ARCHI_pic24hj) \\" >> ${FILENAME}
echo -e " || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj)" >> ${FILENAME}
echo -e " #include \"${DRIVER}_pic24_dspic30_dspic33.h\"" >> ${FILENAME}
echo -e "#else" >> ${FILENAME}
echo -e " #error Unsuported ARCHI" >> ${FILENAME}
echo -e "#endif" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#endif // ${DRIVER_UPPER}_H" >> ${FILENAME}

# _dspic.c
FILENAME=periph/${DRIVER}/${DRIVER}_pic24_dspic30_dspic33.c
echo -e "/**" > ${FILENAME}
echo -e " * @file ${DRIVER}_pic24_dspic30_dspic33.c" >> ${FILENAME}
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${FILENAME}
echo -e " * @copyright Robotips 2016" >> ${FILENAME}
echo -e " *" >> ${FILENAME}
echo -e " * @date ${DATE} " >> ${FILENAME}
echo -e " * " >> ${FILENAME}
echo -e " * @brief ${DESC} for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV," >> ${FILENAME}
echo -e " * PIC24F, PIC24FJ, PIC24EP and PIC24HJ" >> ${FILENAME}
echo -e " */" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#include \"${DRIVER}.h\"" >> ${FILENAME}

# _dspic.h
FILENAME=periph/${DRIVER}/${DRIVER}_pic24_dspic30_dspic33.h
echo -e "/**" > ${FILENAME}
echo -e " * @file ${DRIVER}_pic24_dspic30_dspic33.h" >> ${FILENAME}
echo -e " * @author Sebastien CAUX (sebcaux)" >> ${FILENAME}
echo -e " * @copyright Robotips 2016" >> ${FILENAME}
echo -e " *" >> ${FILENAME}
echo -e " * @date ${DATE} " >> ${FILENAME}
echo -e " * " >> ${FILENAME}
echo -e " * @brief ${DESC} for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV," >> ${FILENAME}
echo -e " * PIC24F, PIC24FJ, PIC24EP and PIC24HJ" >> ${FILENAME}
echo -e " */" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#ifndef ${DRIVER_UPPER}_DSPIC_H" >> ${FILENAME}
echo -e "#define ${DRIVER_UPPER}_DSPIC_H" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "" >> ${FILENAME}
echo -e "#endif // ${DRIVER_UPPER}_DSPIC_H" >> ${FILENAME}

# include.h
echo -e "#include \"../../support/driver/periph/${DRIVER}/${DRIVER}.h\"" > ../../include/driver/${DRIVER}.h
