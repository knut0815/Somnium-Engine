CC := clang++
LDFLAGS:= -l GL -lm -l glfw -l GLEW
CPPFLAGS := -Wall -g -std=c++11
CXXFLAGS:=  -I Dependencies/GLEW/include -I Dependencies/GLFW/include
SRC_DIR:=Somnium
OBJ_DIR:=Objects
SUB_DIRS := $(shell find $(SRC_DIR) -type d)
TARGET := SOMNIUM

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS:=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all:pre-build main-build

pre-build:
	mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))

main-build:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o:%.cpp
	$(CC) $(CPPFLAGS)  $< -c -o $@ $(CXXFLAGS)

CXXFLAGS += -MMD
-include $(OBJS:.o=.d)

clean:
	rm -r $(OBJ_DIR)
	rm SOMNIUM
