ifndef IC_DRIVER
IC_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += ic.h ic_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev))
 SRC += ic_pic24e_dspic33e.c
 HEADER += ic_pic24e_dspic33e.h
endif
ifeq ($(ARCHI), pic24fj)
 ifeq ($(DEVICE),$(filter $(DEVICE),24FJ16MC101 24FJ16MC102 24FJ32MC101 24FJ32MC102 24FJ32MC104)
  ARCHI_SRC += oc_pic24f_dspic30f_dspic33f.c
  HEADER += oc_pic24f_dspic30f_dspic33f.h
 else
  ARCHI_SRC += oc_pic24e_dspic33e.c
  HEADER += oc_pic24e_dspic33e.h
 endif
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24hj dspic30f dspic33fj))
 SRC += ic_pic24f_dspic30f_dspic33f.c
 HEADER += ic_pic24f_dspic30f_dspic33f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mk pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += ic_pic32.c
 HEADER += ic_pic32.h
endif

endif
