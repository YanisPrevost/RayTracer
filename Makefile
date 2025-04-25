##
## EPITECH PROJECT, 2024
## RayTracer
## File description:
## Makefile
##

NAME = raytracer
CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -ldl -lsfml-graphics -lsfml-window -lsfml-system -pthread -lconfig++
PLUGINS_DIR = ./Plugins
PRIMITIVES_DIR = $(PLUGINS_DIR)/Primitives
LIGHTS_DIR = $(PLUGINS_DIR)/Lights
MATERIALS_DIR = $(PLUGINS_DIR)/Materials
SRC_BASE = src
MATH_FILES = $(SRC_BASE)/Points/Point3D.cpp \
			$(SRC_BASE)/Vectors/Vector3D.cpp \
			$(SRC_BASE)/Rays/Ray.cpp

SRC_DIRS = $(SRC_BASE) \
           $(SRC_BASE)/Camera \
           $(SRC_BASE)/Points \
           $(SRC_BASE)/Rays \
           $(SRC_BASE)/Utils \
		   $(SRC_BASE)/Scene \
		   $(SRC_BASE)/Builders \
		   $(SRC_BASE)/Builders/Sphere \
		   $(SRC_BASE)/Builders/Plane \
		   $(SRC_BASE)/Decorator \
           $(SRC_BASE)/Vectors \
           $(SRC_BASE)/Interfaces \
           $(SRC_BASE)/Display	\
		   $(SRC_BASE)/Visualization	\
		   $(SRC_BASE)/Parsing

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)
INCLUDES = -I$(SRC_BASE)
SHAPES_LIBS = libsphere.so \
               libplane.so \

all: prepare_libs $(SHAPES_LIBS) $(NAME)

prepare_libs:
	mkdir -p $(PRIMITIVES_DIR)
	mkdir -p $(LIGHTS_DIR)
	mkdir -p $(MATERIALS_DIR)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

libsphere.so: $(SRC_BASE)/Primitives/Sphere/Sphere.cpp $(MATH_FILES)
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $(PRIMITIVES_DIR)/$@ $^ $(INCLUDES)

libplane.so: $(SRC_BASE)/Primitives/Plane/Plane.cpp $(MATH_FILES)
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $(PRIMITIVES_DIR)/$@ $^ $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIBS_DIR)
	rm -rf $(PRIMITIVES_DIR)
	rm -rf $(LIGHTS_DIR)
	rm -rf $(MATERIALS_DIR)
	rm -f *.ppm

re: fclean all

.PHONY: all prepare_libs clean fclean re
