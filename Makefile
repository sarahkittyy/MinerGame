SRCDIR = src
INCDIR = include
OBJDIR = obj
OUTDIR = bin
OUTFILE = a.out

DEBUGDIR = debug
RELEASEDIR = release

CC = g++
CCFLAGS_RELEASE = -c -Wall -I$(INCDIR) -I$(IMGUI) -I$(IMGUI_SFML) -Wno-unused-variable 
CCFLAGS_DEBUG = $(CCFLAGS_RELEASE) -g -DDEBUG_MODE

LIB_SFML = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system
LIB = -lstdc++ -std=c++17 -lGL
LIB_RELEASE = $(LIB) $(LIB_SFML)
LIB_DEBUG = $(LIB) $(patsubst -lsfml-%, -lsfml-%-d, $(LIB_SFML))

IMGUI = $(INCDIR)/imgui
IMGUI_SFML = $(INCDIR)/imgui-sfml

LINKFLAGS_RELEASE = -o $(OUTDIR)/$(RELEASEDIR)/$(OUTFILE)
LINKFLAGS_DEBUG = -o $(OUTDIR)/$(DEBUGDIR)/$(OUTFILE)

SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
OBJ_RELEASE = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/$(RELEASEDIR)/%.o, $(SOURCES)) $(OBJ_RELEASE_IMGUI) $(OBJ_RELEASE_IMGUI_SFML)
OBJ_DEBUG = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/$(DEBUGDIR)/%.o, $(SOURCES)) $(OBJ_DEBUG_IMGUI) $(OBJ_DEBUG_IMGUI_SFML)

IMGUI_DIR = imgui
IMGUI_SFML_DIR = imgui-sfml

SOURCES_IMGUI = $(IMGUI)/imgui.cpp $(IMGUI)/imgui_draw.cpp $(IMGUI)/imgui_widgets.cpp $(IMGUI)/imgui_demo.cpp
SOURCES_IMGUI_SFML = $(IMGUI_SFML)/imgui-SFML.cpp

OBJ_DEBUG_IMGUI = $(patsubst $(IMGUI)/%.cpp, $(OBJDIR)/$(DEBUGDIR)/$(IMGUI_DIR)/%.o, $(SOURCES_IMGUI))
OBJ_RELEASE_IMGUI = $(patsubst $(IMGUI)/%.cpp, $(OBJDIR)/$(RELEASEDIR)/$(IMGUI_DIR)/%.o, $(SOURCES_IMGUI))

OBJ_DEBUG_IMGUI_SFML = $(patsubst $(IMGUI_SFML)/%.cpp, $(OBJDIR)/$(DEBUGDIR)/$(IMGUI_SFML_DIR)/%.o, $(SOURCES_IMGUI_SFML))
OBJ_RELEASE_IMGUI_SFML = $(patsubst $(IMGUI_SFML)/%.cpp, $(OBJDIR)/$(RELEASEDIR)/$(IMGUI_SFML_DIR)/%.o, $(SOURCES_IMGUI_SFML))

all: release

clean:
	rm -rf $(OUTDIR)/$(RELEASEDIR)/* || true
	rm -rf $(OUTDIR)/$(DEBUGDIR)/* || true
	rm -rf $(OBJDIR)/$(RELEASEDIR)/* || true
	rm -rf $(OBJDIR)/$(DEBUGDIR)/* || true
	make -C winbuild clean
	@printf "\nCleaned!\n";
	
release: dirs $(OBJ_RELEASE) %(OBJ_RELEASE_IMGUI)
	$(CC) $(LINKFLAGS_RELEASE) $(LIB_RELEASE) $(OBJ_RELEASE)
	
debug: dirs $(OBJ_DEBUG) $(OBJ_DEBUG_IMGUI)
	$(CC) $(LINKFLAGS_DEBUG) $(LIB_DEBUG) $(OBJ_DEBUG)
	
win: dirs
	make -C winbuild
	
dirs:
	mkdir -p $(OUTDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(OUTDIR)/$(DEBUGDIR)
	mkdir -p $(OUTDIR)/$(RELEASEDIR)
	mkdir -p $(OBJDIR)/$(DEBUGDIR)
	mkdir -p $(OBJDIR)/$(RELEASEDIR)
	mkdir -p $(OBJDIR)/$(DEBUGDIR)/$(IMGUI_DIR)
	mkdir -p $(OBJDIR)/$(RELEASEDIR)/$(IMGUI_DIR)
	mkdir -p $(OBJDIR)/$(DEBUGDIR)/$(IMGUI_SFML_DIR)
	mkdir -p $(OBJDIR)/$(RELEASEDIR)/$(IMGUI_SFML_DIR)
	
	mkdir -p $(patsubst $(SRCDIR)/%, $(OBJDIR)/$(DEBUGDIR)/%, $(shell find src/ -type d))
	mkdir -p $(patsubst $(SRCDIR)/%, $(OBJDIR)/$(RELEASEDIR)/%, $(shell find src/ -type d))
	
	ln -rsf resource bin/debug/ &> /dev/null
	ln -rsf resource bin/release/ &> /dev/null
	
$(OBJDIR)/$(RELEASEDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS_RELEASE) $< -o $@
	
$(OBJDIR)/$(DEBUGDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS_DEBUG) $< -o $@
	
$(OBJDIR)/$(RELEASEDIR)/$(IMGUI_DIR)/%.o: $(INCDIR)/$(IMGUI_DIR)/%.cpp
	$(CC) $(CCFLAGS_RELEASE) $< -o $@
	
$(OBJDIR)/$(DEBUGDIR)/$(IMGUI_DIR)/%.o: $(INCDIR)/$(IMGUI_DIR)/%.cpp
	$(CC) $(CCFLAGS_DEBUG) $< -o $@
	
$(OBJDIR)/$(RELEASEDIR)/$(IMGUI_SFML_DIR)/%.o: $(INCDIR)/$(IMGUI_SFML_DIR)/%.cpp
	$(CC) $(CCFLAGS_RELEASE) $< -o $@
	
$(OBJDIR)/$(DEBUGDIR)/$(IMGUI_SFML_DIR)/%.o: $(INCDIR)/$(IMGUI_SFML_DIR)/%.cpp
	$(CC) $(CCFLAGS_DEBUG) $< -o $@