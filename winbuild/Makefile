#DIRECTORIES
SRCDIR = ../src
INCDIR = ../include
WINSFMLINCLUDE = include/SFML/include
OBJDIR = ../obj
OUTDIR = ../bin
OUTFILE = Miner.exe
LIBDIR = include/SFML/lib
IMGUI = $(INCDIR)/imgui
IMGUI_SFML = $(INCDIR)/imgui-sfml
IMGUI_DIR = imgui
IMGUI_SFML_DIR = imgui-sfml

WINDIR = win


CC = x86_64-w64-mingw32-g++
INCLUDES = -I$(INCDIR)/ -I$(WINSFMLINCLUDE)/ -I$(IMGUI)/ -I$(IMGUI_SFML)/
CCFLAGS = -c -DSFML_STATIC -Wall $(INCLUDES) -Wno-unused-variable

LIB_SFML = -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-network-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -lopenal32 -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32

LINK = -static -static-libgcc -static-libstdc++ -L$(LIBDIR) $(LIB_SFML)

# OBJECTS TO BE BUILT
SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/$(WINDIR)/%.o, $(SOURCES))

# IMGUI Sources
SOURCES_IMGUI = $(IMGUI)/imgui.cpp $(IMGUI)/imgui_draw.cpp $(IMGUI)/imgui_widgets.cpp $(IMGUI)/imgui_demo.cpp
SOURCES_IMGUI_SFML = $(IMGUI_SFML)/imgui-SFML.cpp

OBJ_IMGUI = $(patsubst $(IMGUI)/%.cpp, $(OBJDIR)/$(WINDIR)/$(IMGUI_DIR)/%.o, $(SOURCES_IMGUI)) $(patsubst $(IMGUI_SFML)/%.cpp, $(OBJDIR)/$(WINDIR)/$(IMGUI_SFML_DIR)/%.o, $(SOURCES_IMGUI_SFML))

all: dirs release
	zip -FSr $(OUTDIR)/$(WINDIR)/MinerGame.zip $(OUTDIR)/$(WINDIR)/Miner.exe $(OUTDIR)/$(WINDIR)/resource

dirs:
	mkdir -p $(OBJDIR)/$(WINDIR)
	mkdir -p $(OUTDIR)/$(WINDIR)
	mkdir -p $(OBJDIR)/$(WINDIR)/$(IMGUI_DIR)
	mkdir -p $(OBJDIR)/$(WINDIR)/$(IMGUI_SFML_DIR)
	
	cp -r ../resource $(OUTDIR)/$(WINDIR)/

release: $(OBJECTS) $(OBJ_IMGUI)
	$(CC) $(OBJECTS) $(OBJ_IMGUI) -o $(OUTDIR)/$(WINDIR)/$(OUTFILE) $(LINK)

clean:
	rm -rf $(OBJDIR)/$(WINDIR)/* || true
	rm -rf $(OUTDIR)/$(WINDIR)/* || true

$(OBJDIR)/$(WINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CCFLAGS) $< -o $@
	
$(OBJDIR)/$(WINDIR)/$(IMGUI_DIR)/%.o: $(IMGUI)/%.cpp
	$(CC) $(CCFLAGS) $< -o $@
	
$(OBJDIR)/$(WINDIR)/$(IMGUI_SFML_DIR)/%.o: $(IMGUI_SFML)/%.cpp
	$(CC) $(CCFLAGS) $< -o $@