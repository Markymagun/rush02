NAME = rush-02
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
       validate.c \
       parse_dict.c \
       parse_utils.c \
       logic_adapt.c \
       print.c \
       print_helpers.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
