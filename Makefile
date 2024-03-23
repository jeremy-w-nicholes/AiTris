CXX = g++
CXXFLAGS = -Wall -I$(WORKSPACE_FOLDER)/raylib/src -g 
# Linking with RPATH
LDFLAGS = -L$(WORKSPACE_FOLDER)/raylib/src -Wl,-rpath,$(WORKSPACE_FOLDER)/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/releases

WORKSPACE_FOLDER = .

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC = AiTris

all: debug

debug: CXXFLAGS += -DDEBUG 
debug: $(DEBUG_DIR)/$(EXEC)

release: $(RELEASE_DIR)/$(EXEC)

$(DEBUG_DIR)/$(EXEC): $(OBJECTS)
	@echo "Linking the executable..."
	@$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS) && echo "Build succeeded" || echo "Build failed, check the errors above"

$(RELEASE_DIR)/$(EXEC): $(OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o $(DEBUG_DIR)/$(EXEC) $(RELEASE_DIR)/$(EXEC)
