CC = cc
NAME = philo
CODE_DIR = ./ 
CFILE = $(wildcard ./*.c)
OBJ = $(patsubst %.c,%.o,$(CFILE))
FLAG = -Wall -Wextra -Werror -I.
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAG) -o $@ -c $<

clean: 
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re