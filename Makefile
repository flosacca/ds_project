# --------------------------------

SRCDIR := src
LIBDIR := $(SRCDIR)/lib
BUILD := build
OBJDIR := obj
BUILDDIRS := $(addprefix $(BUILD)/,$(OBJDIR) input output)

TARGET := main
SRCS = $(filter-out $(SRCDIR)/main.cc,$(wildcard $(SRCDIR)/*.cc))
OBJS = $(patsubst $(SRCDIR)/%.cc,$(OBJDIR)/%.o,$(SRCS))
LIBS = $(wildcard $(LIBDIR)/*.h)
HEADERS :=

FLAGS := -std=c++14 -O3 -static

# --------------------------------

EXENAME := $(TARGET)
TARGET := $(BUILD)/$(TARGET).exe
OBJDIR := $(BUILD)/$(OBJDIR)
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
	cd $(BUILD) && gdb $(EXENAME)

mkdir:
	mkdir -p $(BUILDDIRS)
	[ -e $(BUILD)/dic ] || cp -r dic $(BUILD)

run:
	cd $(BUILD) && ./$(EXENAME)

# --------------------------------
