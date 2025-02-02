
# framework information for older version of MACOS
#INCLUDE_FRAMEWORK = -F/System/Library/Frameworks
# frameworks for newer MACOS, where include files are moved 
INCLUDE_FRAMEWORK = -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/

EXE = a1
CC = gcc
LINK_FLAGS = -framework OpenGL -framework GLUT -lm
COMPILE_FLAGS = -Iinclude $(INCLUDE_FRAMEWORK) -Wno-deprecated-declarations

OBJS = $(SRC:.c=.o)
SRC = \
	src/main.c \
	src/base.c \
	src/cloud.c \
	src/data.c \
	src/generation.c \
	src/graphics.c \
	src/hill.c \
	src/linkedList.c \
	src/map.c \
	src/meteor.c \
	src/projectile.c \
	src/team.c \
	src/tower.c \
	src/utility.c \
	src/valley.c \
	src/vehicle.c \
	src/visible.c

all: clean $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LINK_FLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) -c $(COMPILE_FLAGS) $< -o $@

testworld: $(EXE)
	./$(EXE) -testworld

a1_old:
	gcc src/** -o $(EXE) $(COMPILE_FLAGS) $(LINK_FLAGS)

run: all
	./$(EXE)

clean :
	-rm -f $(EXE)
	-rm -f $(OBJS)
