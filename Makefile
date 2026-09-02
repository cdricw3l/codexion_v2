NAME=codexion
CC=gcc
CFLAGS=-Wall -Werror -Wextra -g

SRC=src
DISPLAY=display
ERRORS=errors
PARSING=parsing
UTILS=utils

SRCS=	$(SRC)/$(NAME).c \
		$(SRC)/$(DISPLAY)/display.c \
		$(SRC)/$(ERRORS)/error.c \
		$(SRC)/$(PARSING)/parsing.c \
		$(SRC)/$(UTILS)/utils.c

OBJECT_SRCS= $(SRCS:.c=.o)
MEMORY_CHECK ?=0

#### TEST VARIABLE ###
TEST_FOLDER= test
TYPE ?= unit
######################

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT_SRCS)
	$(CC) $(CFLAGS) $(OBJECT_SRCS) -o $(NAME)

ARG=20 500 200 100 100 10 10 fifo
run: $(NAME)
	./$(NAME) $(ARG)

clean:
	make -C $(TEST_FOLDER) clean
	rm -f $(OBJECT_SRCS)

fclean: clean
	make -C $(TEST_FOLDER) fclean
	rm -f $(NAME)


test:
	make -C $(TEST_FOLDER) TYPE=$(TYPE) MEMORY_CHECK=$(MEMORY_CHECK) test


.PHONY: clean fclean test