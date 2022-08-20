NAME	=	fdf

HDR	= 	fdf.h
SRC	= 	fdf.c \
		read_map.c\
		draw_line.c\
		draw_map.c\
		draw_utilities.c\
		control_action.c\

OBJ	=	$(patsubst %.c, %.o,$(SRC))
FLAGS	=	-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(HDR)
		make -C minilibx_macos
		mv minilibx_macos/libmlx.a .
		gcc $(FLAGS) -L. -lmlx -framework OpenGL -framework Appkit $(OBJ) -I $(HDR) -o $@

%.o : %.c
	gcc $(FLAGS) -I $(HDR) -c $< -o $@

clean :
	@make clean -C minilibx_macos
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)
	@rm -f libmlx.a

re : fclean all

.PHONY : all clean fclean re
