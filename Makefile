# --------------------------------

SRCDIR := src
LIBDIR := $(SRCDIR)/lib
BUILD := build
OBJDIR := obj
BUILDDIRS := $(addprefix $(BUILD)/,$(OBJDIR) input output)

TARGET := main
OBJS := dom file splitter
LIBS :=
HEADERS :=

FLAGS := -std=c++11 -O2 -static

# --------------------------------

EXENAME := $(TARGET)
TARGET := $(BUILD)/$(TARGET).exe
OBJDIR := $(BUILD)/$(OBJDIR)
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

clean:
	rm -r build

debug:
	gdb $(TARGET)

mkdir:
	mkdir -p $(BUILDDIRS)
	[ -e $(BUILD)/dic ] || cp -r dic $(BUILD)

run:
	cd $(BUILD) && ./$(EXENAME)

# --------------------------------
