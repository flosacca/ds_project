# --------------------------------

TARGET := main
SRCDIR := src
LIBDIR := $(SRCDIR)/lib
BUILD := build
OBJDIR := obj
BUILDDIRS := $(addprefix $(BUILD)/,$(OBJDIR) input output)

SRCS = $(filter-out $(SRCDIR)/main.cc,$(wildcard $(SRCDIR)/*.cc))
LIBS = $(wildcard $(LIBDIR)/*.h)
OBJS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRCS))
HEADERS = $(wildcard $(SRCDIR)/*.h)

FLAGS := -std=c++14 -O3 -static

# --------------------------------

EXENAME := $(TARGET)
TARGET := $(BUILD)/$(TARGET).exe
OBJDIR := $(BUILD)/$(OBJDIR)

FLAGS += -I $(LIBDIR)

# --------------------------------

all: mkdir $(TARGET)

$(BUILD)/%.exe: $(SRCDIR)/%.cc $(LIBS) $(HEADERS) $(OBJS)
	g++ $(FLAGS) -o $@ $< $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(LIBS) $(HEADERS)
	g++ $(FLAGS) -c -o $@ $<

# --------------------------------

.PHONY: all clean debug mkdir run

clean:
	rm -r build

debug:
	cd $(BUILD) && gdb $(EXENAME)

mkdir:
	mkdir -p $(BUILDDIRS)
	[ -e $(BUILD)/dic ] || cp -r dic $(BUILD)

run:
	cd $(BUILD) && ./$(EXENAME)

# --------------------------------
