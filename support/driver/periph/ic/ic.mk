ifndef IC_DRIVER
IC_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += ic.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev))
 SRC += ic_pic24e_dspic33e.c
 HEADER += ic_pic24e_dspic33e.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj dspic30f dspic33fj))
 SRC += ic_pic24f_dspic33f_dspic30f.c
 HEADER += ic_pic24f_dspic33f_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += ic_pic32.c
 HEADER += ic_pic32.h
endif

endif
