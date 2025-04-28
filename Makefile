##
## EPITECH PROJECT, 2024
## Zero
## File description:
## Makefile
##

CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
LDFLAGS = -ldl -lsfml-graphics -lsfml-window -lsfml-system -lconfig++ -lpthread

SRC_DIR = src
BUILD_DIR = build
PLUGINS_DIR = Plugins

SRCS = $(shell find $(SRC_DIR) -name "*.cpp" -not -path "$(SRC_DIR)/Primitives/*")

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

PRIMITIVE_SRCS = $(SRC_DIR)/Primitives/Sphere/Sphere.cpp
PRIMITIVE_LIBS = $(PLUGINS_DIR)/libSphere.so

TARGET = raytracer

all: directories $(TARGET)
all_with_plugins: directories $(TARGET) plugins

directories:
	@mkdir -p $(BUILD_DIR)/Builder
	@mkdir -p $(BUILD_DIR)/Camera
	@mkdir -p $(BUILD_DIR)/Decorator
	@mkdir -p $(BUILD_DIR)/Parsing
	@mkdir -p $(BUILD_DIR)/Points
	@mkdir -p $(BUILD_DIR)/Rectangle3D
	@mkdir -p $(BUILD_DIR)/Vectors
	@mkdir -p $(BUILD_DIR)/Visualization
	@mkdir -p $(PLUGINS_DIR)

$(TARGET): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@

primitive_%:
	g++ $(CXXFLAGS) -shared -fPIC -o $(PLUGINS_DIR)/lib$*.so $(SRC_DIR)/Primitives/$*/$*.cpp $(SRC_DIR)/Points/Points.cpp $(SRC_DIR)/Vectors/Vector.cpp -I./src

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

fclean: clean
	rm -rf $(PLUGINS_DIR)

clean_ppm:
	rm *.ppm

re: fclean all

.PHONY: all directories clean fclean re