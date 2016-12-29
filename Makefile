CXX := g++
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TARGET_ProvedRez := $(BINDIR)/ProvedRez
FILTEROUT_ProvedRez := $(BUILDDIR)/PLT2VTK.o $(BUILDDIR)/VTK2PLT.o
TARGET_PLT2VTK := $(BINDIR)/PLT2VTK
FILTEROUT_PLT2VTK := $(BUILDDIR)/ProvedRez.o $(BUILDDIR)/VTK2PLT.o
TARGET_VTK2PLT := $(BINDIR)/VTK2PLT
FILTEROUT_VTK2PLT := $(BUILDDIR)/ProvedRez.o $(BUILDDIR)/PLT2VTK.o

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS_ProvedRez := $(filter-out $(FILTEROUT_ProvedRez), $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o)))
OBJECTS_PLT2VTK := $(filter-out $(FILTEROUT_PLT2VTK), $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o)))
OBJECTS_VKT2PLT := $(filter-out $(FILTEROUT_VTK2PLT), $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o)))

CXXFLAGS = -O2 -std=c++11 -g -Wall
LIB :=
INC := -I include

all: $(TARGET_ProvedRez) $(TARGET_PLT2VTK) $(TARGET_VTK2PLT)

$(TARGET_ProvedRez): $(OBJECTS_ProvedRez)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET_ProvedRez) $(LIB)"; $(CXX) $^ -o $(TARGET_ProvedRez) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CFLAGS) $(INC) -c -o $@ $<

$(TARGET_PLT2VTK): $(OBJECTS_PLT2VTK)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET_PLT2VTK) $(LIB)"; $(CXX) $^ -o $(TARGET_PLT2VTK) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CFLAGS) $(INC) -c -o $@ $<

$(TARGET_VTK2PLT): $(OBJECTS_VKT2PLT)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET_VTK2PLT) $(LIB)"; $(CXX) $^ -o $(TARGET_VTK2PLT) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) $(CFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET_ProvedRez) $(TARGET_PLT2VTK) $(TARGET_VTK2PLT)"; $(RM) -r $(BUILDDIR) $(TARGET_ProvedRez) $(TARGET_PLT2VTK) $(TARGET_VTK2PLT)

.PHONY: clean
