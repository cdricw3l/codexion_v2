NAME=codexion
CC=gcc
CFLAGS= -g
#CFLAGS=-Wall -Werror -Wextra -g

SRC=src
DISPLAY=display
ERRORS=errors
PARSING=parsing
UTILS=utils
INIT=init
HEAP=heap
REQUEST=request
TIME=time
UTILS=utils

SRCS=	src/codexion.c \
		src/parsing/parsing.c \
		src/init/clean_scheduler.c \
		src/init/clean_sim.c \
		src/init/init_coders.c \
		src/init/init_dongles.c \
		src/init/init_monitoring.c \
		src/init/init_scheduler.c \
		src/init/init_sim.c \
		src/init/init_utils.c \
		src/thread_managment/thread_managment.c \
		src/routines/coder.c \
		src/routines/monitoring.c \
		src/routines/scheduler.c \
		src/heap/heap_clear.c \
		src/heap/heap_get_node.c \
		src/heap/heap_init.c \
		src/heap/heap_new_node.c \
		src/heap/heap_pop.c \
		src/heap/heap_push.c \
		src/heap/heap_swap_node.c \
		src/request/request_clear_queue.c \
		src/request/request_destroy_queue.c \
		src/request/request_display.c \
		src/request/request_get_last_node.c \
		src/request/request_get_queue_size.c \
		src/request/request_init_queue.c \
		src/request/request_push.c \
		src/request/request_pop.c \
		src/time/time.c \
		src/utils/utils_1.c \
		src/utils/utils_2.c \
		src/display/display.c \
		src/errors/error.c

OBJECT_SRCS= $(SRCS:.c=.o)
MEMORY_CHECK ?=0
MEMORY_LOG= memory.log

#### TEST VARIABLE ###
TEST_FOLDER= test
TYPE ?= unit
######################

%.o:%.c 
	@$(CC) -c $(CFLAGS)  $< -o $@

$(NAME): $(OBJECT_SRCS)
	@$(CC) $(CFLAGS) $(OBJECT_SRCS) -o $(NAME)

ARG=5 5000 200 100 100 10 1 fifo

ifeq ($(shell uname),Darwin)
	MEMORY_CHECK_ARG= leaks -atExit --
else
	ifeq ($(MEMORY_CHECK),1)
		MEMORY_CHECK_ARG= valgrind  --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=$(MEMORY_LOG)
	else ifeq ($(MEMORY_CHECK),2)
		MEMORY_CHECK_ARG= valgrind  --tool=helgrind  --track-lockorders=yes --log-file=$(MEMORY_LOG)
	endif
endif

run: $(NAME)
ifeq ($(MEMORY_CHECK),0)
	./$(NAME) $(ARG)
else
	$(MEMORY_CHECK_ARG) ./$(NAME) $(ARG)
endif

clean:
	make -C $(TEST_FOLDER) clean
	rm -f $(OBJECT_SRCS)

fclean: clean
	make -C $(TEST_FOLDER) fclean
	rm -f $(NAME)


test:
	make -C $(TEST_FOLDER) TYPE=$(TYPE) MEMORY_CHECK=$(MEMORY_CHECK) test


.PHONY: clean fclean test