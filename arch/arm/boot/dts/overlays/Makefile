# Overlays for the Odroid platform

DTC ?= dtc
DTCO_FLAGS ?= \
	-Wno-unit_address_vs_reg \
	-@

OBJ := $(patsubst %.dts, %.dtbo, $(wildcard *.dts))

dtbo-y := \
	spidev1-overlay.dtbo \
	i2c1-overlay.dtbo \
	i2c5-overlay.dtbo \
	hktft32-overlay.dtbo \
	hktft35-overlay.dtbo \
	hktft-cs-ogst-overlay.dtbo

%.dtbo: %.dts
	@echo "  DTCO    $@"
	@$(DTC) $(DTCO_FLAGS) -I dts -O dtb -o $@ $^

dtbos: $(dtbo-y)

all: $(dtbos)

clean:
	@rm -rf *.dtbo

.PHONY: all clean dtbos

always += $(dtbo-y)
