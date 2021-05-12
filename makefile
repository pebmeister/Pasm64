.SUFFIXES:
    MAKEFLAGS += -r

CC = gcc
RM = rm
LEX = flex
YACC = bison
MKDIR = mkdir
OBJ_DIR = obj/

CFLAGS = -c
LINKFLAGS =
LEXFLAGS = -L
YACCFLAGS = -d
RMFLAGS = -f
MKFLAGS = -p

# the build target executable:
TARGET = pasm64.exe

# objs
OBJS = $(OBJ_DIR)pasm64.tab.o \
	$(OBJ_DIR)pasm64.flex.o \
	$(OBJ_DIR)pasm64.o \
	$(OBJ_DIR)symbol.o \
	$(OBJ_DIR)node.o \
	$(OBJ_DIR)opcodes.o \
	$(OBJ_DIR)genlist.o \
	$(OBJ_DIR)genoutput.o \
	$(OBJ_DIR)error.o \
	$(OBJ_DIR)str.o \
	$(OBJ_DIR)dictionary.o \
	$(OBJ_DIR)file.o \
	$(OBJ_DIR)mem.o \
	$(OBJ_DIR)main.o
 
INLUDES = genlist.h genoutput.h error.h pasm64.h node.h opcodes.h symbol.h pasm64.tab.h str.h dictionary.h file.h mem.h

all: $(TARGET)

$(OBJ_DIR)pasm64.o: pasm64.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)pasm64.o pasm64.c

$(OBJ_DIR)symbol.o: symbol.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)symbol.o symbol.c

$(OBJ_DIR)node.o: node.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)node.o node.c

$(OBJ_DIR)opcodes.o: opcodes.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)opcodes.o opcodes.c

$(OBJ_DIR)genlist.o: genlist.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)genlist.o genlist.c

$(OBJ_DIR)genoutput.o: genoutput.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)genoutput.o genoutput.c

$(OBJ_DIR)main.o: main.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)main.o main.c

$(OBJ_DIR)dictionary.o: dictionary.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)dictionary.o dictionary.c

$(OBJ_DIR)file.o: file.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)file.o file.c

$(OBJ_DIR)error.o: error.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)error.o error.c

$(OBJ_DIR)str.o: str.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)str.o str.c

$(OBJ_DIR)mem.o: mem.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)mem.o mem.c

$(OBJ_DIR)pasm64.tab.o: pasm64.tab.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)pasm64.tab.o pasm64.tab.c

$(OBJ_DIR)pasm64.flex.o: pasm64.flex.c $(INLUDES)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)pasm64.flex.o pasm64.flex.c

pasm64.tab.c: pasm64.y
	$(YACC) $(YACCFLAGS) -opasm64.tab.c pasm64.y

pasm64.tab.h: pasm64.y
	$(YACC) $(YACCFLAGS) -opasm64.tab.c pasm64.y

pasm64.flex.c: pasm64.l
	$(LEX) $(LEXFLAGS) -opasm64.flex.c pasm64.l

$(TARGET): $(OBJ_DIR) $(OBJS)
	$(CC) $(LINKFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR):
	$(MKDIR) $(MKFLAGS) $(OBJ_DIR)

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)*.o
	$(RM) $(RMFLAGS) *.tab.c
	$(RM) $(RMFLAGS) *.tab.h
	$(RM) $(RMFLAGS) *.flex.c
	$(RM) $(RMFLAGS) $(TARGET)
	$(RM) $(RMFLAGS) *.output
	$(RM) $(RMFLAGS) ~*

