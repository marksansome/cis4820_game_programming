
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
	src/meteor.c \
	src/projectile.c \
	src/utility.c \
	src/valley.c \
	src/visible.c

all: clean $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LINK_FLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) -c $(COMPILE_FLAGS) $< -o $@

testworld: $(EXE)
	./a1 -testworld

a1_old:
	gcc src/** -o a1 $(COMPILE_FLAGS) $(LINK_FLAGS)

clean :
	-rm -f $(EXE)
	-rm -f $(OBJS)
