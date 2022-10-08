SRCS			=	main.c \
					parser/parser.c \
					utils/error.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c 

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib
LIBFT			= ./libft
NAME			= cub3D

all:			$(NAME)

$(NAME):		 $(OBJS)
				make -C ${LIBFT}
				gcc  -o ${CFLAGS} -L./libft ${NAME} ${OBJS} 

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				$(RM) $(OBJS) $

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re