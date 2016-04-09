
include $(RTPROG)/support/support.mk

OBJECTS := $(SRC:.c=.o)

$(PROJECT).elf : $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(PROJECT).elf  $< -T p$(DEVICE).gld

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@
