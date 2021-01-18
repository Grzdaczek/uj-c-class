IMG = Lenna.ppm
PREFIX = t.

LOG = @printf "  GEN\t$@\n"
TAIL = -resize 1024 512 512 0 -compose test/$(IMG)
HEAD = $(Q)$(BINDIR)/$(BINFILE) -i test/$(IMG) -o test/$(PREFIX)$@.ppm

OPTIONLESS = invert dither sharpen

test: all $(OPTIONLESS) blur scale contrast

test.clean:
	$(Q)rm -rf $(prefix)*

$(OPTIONLESS):
	$(LOG)
	$(HEAD) -$@ $(TAIL)

blur:
	$(LOG)
	$(HEAD) -$@ 10 $(TAIL)

scale:
	$(LOG)
	$(HEAD) -$@ 1024 1024 $(TAIL)

contrast:
	$(LOG)
	$(HEAD) -$@ 1.5 $(TAIL)

.PHONY: $(BIN) test