CC=gcc
#CFLAGS=-Wall -Werror -Wextra -g
CFLAGS=-g
TYPE ?= unit
MEMORY_CHECK ?= 0
MEMORY_LOG= ../valgrind_report/memory.log



ifeq ($(shell uname),Darwin)
	MEMORY_CHECK_ARG= leaks -atExit --
else
	ifeq ($(MEMORY_CHECK),1)
		MEMORY_CHECK_ARG= valgrind  --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=$(MEMORY_LOG)
	else ifeq($(MEMORY_CHECK),2)
		MEMORY_CHECK_ARG= valgrind  --tool=helgrind --track-lockorders=yes --log-file=$(MEMORY_LOG)
	endif
endif

%.o:%.c 
	$(CC) -c $(CFLAGS)  $< -o $@

run:
ifeq ($(MEMORY_CHECK),0)
	./$(NAME)
else
	@echo "memory check actif"
	$(MEMORY_CHECK_ARG) ./$(NAME)
endif

clean:
	@rm -f  $(TEST_OBJS) $(MEMORY_LOG)

fclean: clean
	@rm -f $(NAME)

.PHONY: clean fclean