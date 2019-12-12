# --------------------------------

BUILD = build
SRCDIR = src
LIBDIR = $(SRCDIR)/lib
OBJDIR = $(BUILD)/obj

TARGET = main
OBJS = dom file splitter
LIBS =
HEADERS =

FLAGS = -std=c++11 -O2 -static

# --------------------------------

EXENAME := $(TARGET)
TARGET := $(BUILD)/$(TARGET).exe
OBJS := $(addprefix $(OBJDIR)/,$(addsuffix .o,$(OBJS)))
LIBS := $(addprefix $(LIBDIR)/,$(addsuffix .h,$(LIBS)))
HEADERS := $(addprefix $(SRCDIR)/,$(HEADERS))

FLAGS += -I $(LIBDIR)

# --------------------------------

all: mkdir $(TARGET)

$(TARGET): $(OBJS) $(HEADERS)

$(BUILD)/%.exe: $(SRCDIR)/%.cc $(LIBS)
	g++ $(FLAGS) -o $@ $< $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(SRCDIR)/%.h $(LIBS)
	g++ $(FLAGS) -c -o $@ $<

# --------------------------------

.PHONY: all clean debug mkdir run

WINBUILD = $(subst /,\,$(BUILD))
WINOBJDIR = $(subst /,\,$(OBJDIR))

clean:
	rm -r build

debug:
	gdb $(TARGET)

mkdir:
	[ -e $(BUILD) ] || mkdir $(BUILD)
	[ -e $(OBJDIR) ] || mkdir $(OBJDIR)
	[ -e build/input ] || mkdir build/input
	[ -e build/output ] || mkdir build/output
	[ -e build/dic ] || cp -r dic build/dic

run:
	cd $(BUILD) && ./$(EXENAME)

# --------------------------------
