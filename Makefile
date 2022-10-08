SRCS			=	main.c parser/parser.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		 $(OBJS)
				gcc  -o ${NAME} ${OBJS} 

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

clean:
				$(RM) $(OBJS) $

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re