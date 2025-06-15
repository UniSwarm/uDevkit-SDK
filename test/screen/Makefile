UDEVKIT = ../..

FACE?=BEAR
ifeq ($(FACE),BEAR)
  PICTURES += picture_bear.png
  CCFLAGS += -DBEAR
endif
ifeq ($(FACE),RABBIT)
  PICTURES += picture_rabbit.png
  CCFLAGS += -DRABBIT
endif
ifeq ($(FACE),INSECT)
  PICTURES += picture_insect.png
  CCFLAGS += -DINSECT
endif
ifeq ($(FACE),PICTURE)
  PICTURES += picture.png
  CCFLAGS += -DSIMPLEPICTURE
endif

PROJECT = testproj
BOARD = a6screenboard
OUT_PWD = build_$(FACE)

DRIVERS += timer
MODULES += gui network
NETWORK_DRIVERS = a6

SRC += main.c
FONTS += core14b core18b Lucida_Console10

all : hex

include $(UDEVKIT)/udevkit.mk
