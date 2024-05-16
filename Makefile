EXEC= soren.out
SOURCE=$(wildcard src/*.c)
OBJ=$(subst .c,.o,$(subst src,bin,$(SOURCE)))

CC = gcc
CC_FLAGS= -c

all: obj_folder $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@

bin/%.o: src/%.c src/%.h
	$(CC) $< $(CC_FLAGS) -o $@

bin/main.o: src/main.c $(SOURCE)
	$(CC) $< $(CC_FLAGS) -o $@

obj_folder:
	@ mkdir -p bin

clean:
	@ rm -rf bin/*.o $(EXEC) *~
	@ rmdir bin

.PHONY: all clean