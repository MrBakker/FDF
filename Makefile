# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbakker <jbakker@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 16:59:22 by jbakker       #+#    #+#                  #
#    Updated: 2024/06/03 13:12:06 by jbakker       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# The mlx_linux library has to be copied into the root of the project folder, since it's not avaliable at the computer itself.

NAME = fdf

CC := cc
DIR := objs/
EXTRAFLAGS := -Wall -Wextra -Werror -g

SRCS := fdf.c map.c matrix.c parse_points.c prebuild_matrices.c screen.c keyboard.c mouse.c

BINS := $(addprefix ${DIR}, ${SRCS:.c=.o})

MODULES := mlx_linux libft

all: ${MODULES} ${NAME}

${MODULES}:
	@mkdir -p $@
	@if [ ! -f "$@/.git" ]; then \
		git submodule update --init --recursive --remote $@; \
	else \
		git submodule update --recursive --remote $@; \
	fi
	@make -C $@

${NAME}: ${BINS}
	@${CC} ${EXTRAFLAGS} ${BINS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz ./libft/libft.a -o ${NAME}

${DIR}%.o: %.c fdf.h
	@mkdir -p ${DIR}
	@${CC} ${EXTRAFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

bonus: all

clean:
	@make -C libft clean
	@rm -rf ${DIR}

fclean:
	@make -C libft fclean
	@rm -f ${NAME}
	@rm -rf ${DIR}

re: fclean all

.PHONY: all bonus clean fclean re libft