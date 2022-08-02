NAME	=	miniRT

CC		=	gcc
CFLAGS	=	-O2 -Wall -Wextra -g #-Werror
INCLUDE =	-I ./src/includes -I ./libs/libft
LIBFT	=	-L ./libs/libft -lft
MLX		=   -lmlx -lXext -lX11
HEADER	= 	./src/includes/minirt.h

MATRIX	= $(addprefix 0_matrix/, \
		0_calculate_orientation.c \
		0_matrix_operations_1.c 0_matrix_operations_2.c \
		0_matrix_operations_3.c \
		0_normal_rotation.c 0_transform.c \
		0_sub_matrix.c \
		0_matrix_operations_4.c\
)

FILE	= $(addprefix 1_file/, \
		0_check_file.c 1_start_file.c 2_init_file.c \
		3_ambient.c 4_0_camera.c 4_1_cam_utils.c \
		5_light.c 6_sphere.c \
		7_plane.c 8_cylinder.c \
)

UTILITY = $(addprefix 2_utility/, \
		0_aid.c 1_char_double.c 2_strparser.c 3_linked.c \
		4_hooks.c 5_0_free.c 5_1_free_list.c 5_2_there_file_error.c \
)

IMAGE	= $(addprefix 3_image/, \
		0_mlx.c ray.c hit.c \
)

REFACTOR	= $(addprefix 4_refactor/, \
		1_0_light.c 1_1_shadow.c \
		2_0_sphere.c 2_1_cylinder.c 2_1_0_cy_intersec.c \
		2_2_plane.c  \
		matrix_inverter.c cam.c \
		computations.c intersections.c \
		render.c  vector.c \
)

SRC		= $(addprefix ./src/files/, \
		$(MATRIX) $(FILE) $(UTILITY) $(IMAGE) $(REFACTOR) \
		minirt.c 1_init.c 2_error.c 3_if_error.c\
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

leak:
	make
	valgrind --leak-check=full --show-leak-kinds=all ./miniRT teste.rt