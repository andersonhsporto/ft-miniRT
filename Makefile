NAME	= miniRT

CC		=	gcc
CFLAGS	=	-Wall -Wextra -g #-Werror
INCLUDE =	-I ./src/includes -I ./0_libs/0_libft
LIBFT	=	-L ./0_libs/0_libft -lft
MLX		=   -lmlx -lXext -lX11
HEADER	= 	./src/includes/minirt.h

MATRIX	= $(addprefix 0_matrix/, \
		0_matrix.c 1_matrix.c 2_matrix_co.c 3_vector.c 4_vector.c \
)

VECTOR	= $(addprefix 0_vector/, \
		0_operations.c 1_operations.c 2_operations.c 3_unit.c \
)

FILE	= $(addprefix 1_file/, \
		0_check_file.c 1_start_file.c 2_init_file.c \
		3_ambient.c 4_camera.c 5_light.c 6_sphere.c \
		7_plane.c 8_cylinder.c \
		debug.c \
)

UTILITY = $(addprefix 2_utility/, \
		0_aid.c 1_char_double.c 2_strparser.c 3_linked.c \
		4_color.c 5_hooks.c\
)

RAY	= $(addprefix 3_ray/, \
		0_ray.c 1_hit.c \
)

IMAGE	= $(addprefix 4_image/, \
		0_image.c 1_mlx.c 2_hit.c 3_element.c \
)

REFACTOR	= $(addprefix 5_refactor/, \
		0_render.c 1_sphere.c 2_plane.c 3_cylinder.c \
)

SRC		= $(addprefix ./src/files/, \
		$(MATRIX) $(VECTOR) $(FILE) $(UTILITY) $(RAY) $(IMAGE) $(REFACTOR)\
		minirt.c 1_init.c 2_error.c\
)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:%.c=%.o)

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	rm -rf $(NAME)
	make all -C ./0_libs/0_libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -lm -o $(NAME)

clean:
	make clean -C ./0_libs/0_libft
	rm -rf $(OBJ)
	rm -rf ./a.out

fclean: clean
	make fclean -C ./0_libs/0_libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

test:
	make
	./miniRT teste.rt