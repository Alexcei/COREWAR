NAME = corewar

LIB_DIR = ./ft_printf/

LIBFT = $(LIB_DIR)libftprintf.a

SRC = main.c check.c file_get_content.c insert_params.c is_valid.c memory.c player.c\
      util.c inst_1-4.c inst_12-16.c inst_5-8.c inst_9-12.c


OBJ = $(SRC:.c=.o)

INCLUDE = ./

CC = gcc

#FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all