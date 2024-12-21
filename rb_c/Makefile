NAME = rbtest

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -rf

SRCS = rbtest.c \
	   rb.c \
	   queue.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all -v

all		: $(NAME)
%.o		: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean	:
	$(RM) $(OBJS)
fclean	: clean
	$(RM) $(NAME)
re		: fclean all

valgrind:
	  valgrind $(VALGRIND_FLAGS) ./rbtest

.PHONY	:	all clean fclean re valgrind
