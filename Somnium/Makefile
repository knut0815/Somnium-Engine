CC := clang++
WEBCC := emcc -O2
OSXLDFLAGS:= -framework OpenGL -lm -l glfw -l GLEW -L ./Dependencies/portaudio/lib -l portaudio
LDFLAGS:= -l GL -lm -l glfw -l GLEW -l freetype -L ./Dependencies/portaudio/lib 
CPPFLAGS := -Wall -g -std=c++11 -Wextra `pkg-config --cflags glfw3 glew freetype2`
CXXFLAGS:=  -I Dependencies/GLEW/include -I Dependencies/GLFW/include -I Dependencies/portsf/include -I Dependencies/freetype/include
SRC_DIR:=.
OBJ_DIR:=Objects
OBJ_DIR_WEB:=Objects
SUB_DIRS := $(shell find $(SRC_DIR) -type d | sed 's|^./||; s|\.||')
TARGET := SOMNIUM_BUILD
TARGETOSX := SOMNIUMOSX
TARGETWEB := SOMNIUM_web.js

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS:=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
WEBOBJS:=$(patsubst %.cpp,$(OBJ_DIR)/%.bc,$(SRCS))

Debugx64:all

all: pre-build main-build

osx: pre-build main-build-OSX

web: pre-build main-build-web

pre-build:
	mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))

main-build:$(TARGET)

main-build-OSX:$(TARGETOSX)

main-build-web:$(TARGETWEB)

$(TARGETOSX):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(OSXLDFLAGS)

$(TARGETWEB):$(WEBOBJS)
	$(WEBCC) $(WEBOBJS) -o $(TARGET).js $(LDFLAGS)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o:%.cpp
	$(CC) $(CPPFLAGS) $< -c -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.bc:%.cpp
	$(WEBCC) $(CPPFLAGS) $< -c -o $@ $(CXXFLAGS)

CXXFLAGS += -MMD 
-include $(OBJS:.o=.d)


clean:
	rm SOMNIUM_BUILD.* &
	rm -r $(OBJ_DIR)
