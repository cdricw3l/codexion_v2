include ../config.mk
NAME=unit_test

TEST_SRCS= $(wildcard *.c) $(wildcard ../../src/*/*.c)
TEST_OBJS= $(TEST_SRCS:.c=.o)

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -g $(TEST_OBJS) -o $(NAME)

