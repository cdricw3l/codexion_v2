include ../config.mk
NAME=integration_test

TEST_SRCS= $(wildcard *.c) $(wildcard ../../src/*/*.c)
TEST_OBJS= $(TEST_SRCS:.c=.o)

test: $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(TEST_OBJS) -o $(NAME)

