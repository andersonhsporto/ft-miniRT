NAME	= miniRT

CC		=	gcc
CFLAGS	=	-Wall -Wextra -O2 -g #-Werror
INCLUDE =	-I ./src/include
MLX		=   -lmlx -lXext -lX11
HEADER	= 	./src/includes/minirt.h

SRC		= $(addprefix ./src/, \
		0_matrix_operations_1.c 0_matrix_operations_2.c \
		cam.c computations.c cylinder.c intersections.c \
		light.c minirt.c plane.c sphere.c \
)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:%.c=%.o)

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	rm -rf $(NAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -lm -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf ./a.out

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

test:
	make
	./miniRT teste.rt