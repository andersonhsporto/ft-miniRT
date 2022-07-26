NAME	= miniRT

CC		=	clang #trocar para clang ao final
CFLAGS	=	-O2 -Wall -Wextra -g #-Werror
INCLUDE =	-I ./src/includes -I ./libs/libft
LIBFT	=	-L ./libs/libft -lft
MLX		=   -lmlx -lXext -lX11
HEADER	= 	./src/includes/minirt.h

FILE	= $(addprefix 1_file/, \
		0_check_file.c 1_start_file.c 2_init_file.c \
		3_ambient.c 4_0_camera.c 4_1_cam_utils.c \
		5_light.c 6_sphere.c \
		7_plane.c 8_cylinder.c \
		debug.c \
)

UTILITY = $(addprefix 2_utility/, \
		0_aid.c 1_char_double.c 2_strparser.c 3_linked.c \
		4_hooks.c \
)

IMAGE	= $(addprefix 3_image/, \
		0_mlx.c ray.c 42_free.c hit.c \
)

REFACTOR	= $(addprefix 4_refactor/, \
		0_matrix_operations_1.c 0_matrix_operations_2.c cam.c \
		computations.c cylinder.c intersections.c light.c \
		render.c plane.c sphere.c \
)

SRC		= $(addprefix ./src/files/, \
		$(FILE) $(UTILITY) $(IMAGE) $(REFACTOR) \
		minirt.c 1_init.c 2_error.c\
)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:%.c=%.o)

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	rm -rf $(NAME)
	make all -C ./libs/libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -lm -o $(NAME)

clean:
	make clean -C ./libs/libft
	rm -rf $(OBJ)
	rm -rf ./a.out

fclean: clean
	make fclean -C ./libs/libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

test:
	make
	./miniRT teste.rt

valgrind:
	make
	valgrind ./miniRT teste.rt