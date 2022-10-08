SRCS			=	main.c \
					utils/utils.c \
					parser/parser.c parser/parse_textures.c\
					gnl/get_next_line.c gnl/get_next_line_utils.c 

OBJS			= $(SRCS:.c=.o)
HEADER			= cube3d.h

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I. -g 
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib
LIBFT			= ./libft
NAME			= cub3D

all:			$(NAME)

$(NAME):		$(OBJS)
				make -C ${LIBFT}
				$(CC) ${CFLAGS} -o ${NAME} ${OBJS} -L${LIBFT} -lft 

# $(MLX):
# 				@$(MAKE) -C mlx
# 				@mv mlx/$(MLX) .
%.o: %.c  */*.h $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
				make clean -C ${LIBFT}
				$(RM) $(OBJS) $

fclean:			clean
				make fclean -C ${LIBFT}
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re