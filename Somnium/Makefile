CC := clang++
OSXLDFLAGS:= -framework OpenGL -lm -l glfw -l GLEW -L ./Dependencies/portaudio/lib -l portaudio -L ./Dependencies/portsf/lib/ -l portsf -L ./Dependencies/tinyAudioLibrary/lib/ -l tiny
LDFLAGS:= -l GL -lm -l glfw -l GLEW -L ./Dependencies/portaudio/lib -L ./Dependencies/portsf/lib/ -l portsf -L ./Dependencies/tinyAudioLibrary/lib/ -l tiny
CPPFLAGS := -Wall -g -std=c++11 -Wextra `pkg-config --cflags glfw3 glew`
CXXFLAGS:=  -I Dependencies/GLEW/include -I Dependencies/GLFW/include -I Dependencies/portsf/include -I Dependencies/tinyAudioLibrary/include
SRC_DIR:=.
OBJ_DIR:=Objects
SUB_DIRS := $(shell find $(SRC_DIR) -type d)
TARGET := SOMNIUM.out
TARGETOSX := SOMNIUM_OSX.out

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS:=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

Debugx64:all

all: pre-build main-build

osx: pre-build main-build-OSX

pre-build:
	mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))

main-build:$(TARGET)

main-build-OSX:$(TARGETOSX)

$(TARGETOSX):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(OSXLDFLAGS)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o:%.cpp
	$(CC) $(CPPFLAGS)  $< -c -o $@ $(CXXFLAGS)

CXXFLAGS += -MMD
-include $(OBJS:.o=.d)

clean:
	rm -r $(OBJ_DIR)
	rm SOMNIUM.out
