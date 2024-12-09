# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbakker <jbakker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 16:59:22 by jbakker       #+#    #+#                  #
#    Updated: 2024/12/09 22:14:49 by jbakker       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC := cc
DIR := objs/
EXTRAFLAGS := -Wall -Wextra -Werror -g

SRCS := fdf.c map.c matrix.c parse_points.c prebuild_matrices.c screen.c keyboard.c mouse.c

BINS := $(addprefix ${DIR}, ${SRCS:.c=.o})

MODULES := mlx_linux libft

all: ${NAME}

${NAME}: ${BINS}
	@make -C libft
	@make -C mlx_linux
	@${CC} ${EXTRAFLAGS} ${BINS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz ./libft/libft.a -o ${NAME}

${DIR}%.o: %.c fdf.h
	@mkdir -p ${DIR}
	@${CC} ${EXTRAFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus: all

clean:
	@make -C libft clean
	@make -C mlx_linux clean
	@rm -rf ${DIR}

fclean:
	@make -C libft fclean
	@make -C mlx_linux clean
	@rm -f ${NAME}
	@rm -rf ${DIR}

re: fclean all

.PHONY: all bonus clean fclean re libft