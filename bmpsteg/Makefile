#=-- General ------------------------------------------------------------------

V	= 0
OPT	= -O2

CFILES	= main.c image.c err.c action.c
BINFILE	= ppmsteg

SRCDIR	:= src
OBJDIR	:= obj
BINDIR	:= bin
DEPDIR 	:= deps

SRCS	:= $(CFILES:%=$(SRCDIR)/%)
OBJS	:= $(CFILES:%.c=$(OBJDIR)/%.o)
DEPS	:= $(CFILES:%.c=$(DEPDIR)/%.d)
BUILDDIRS = $(OBJDIR) $(BINDIR) $(DEPDIR)

V	?= 0
ifeq ($(V),0)
Q	:= @
endif

#=-- Compiler & Linker config -------------------------------------------------
CC	= gcc
LD	= gcc
CFLAGS	+= -ansi
CFLAGS	+= $(OPT)
LDFLAGS	+= #...
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

#=-- Rules --------------------------------------------------------------------

all: $(BINDIR)/$(BINFILE)

$(BINDIR)/$(BINFILE): $(OBJS) $(DEPS)
	@printf "  LD\t$<\n"
	@mkdir -p $(dir $@)
	$(Q)$(LD) $(LDLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o $(DEPDIR)/%.d: $(SRCDIR)/%.c
	@printf "  CC\t$<\n"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DEPDIR)
	$(Q)$(CC) $(DEPFLAGS) $(CFLAGS) -o $@ -c $<
	
clean:
	@printf "  RM\t$(BUILDDIRS)\n"
	$(Q)rm -rf $(BUILDDIRS)

%.d: ;

i:
	@printf "$(SRCS)\n"
	@printf "$(OBJS)\n"
	@printf "$(DEPS)\n"

.PHONY: i all clean
