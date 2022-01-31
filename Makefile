CFLAGS=-Wall -Wextra
TARGET=esame_24_01_2022
SRCS=esame_24_01_2022.c
OBJS=$(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@
	 

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	
.PHONY:clean
clean:
	-$(RM) $(TARGET) $(OBJS)
