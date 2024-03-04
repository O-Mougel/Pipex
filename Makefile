# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 17:02:16 by omougel           #+#    #+#              #
#    Updated: 2024/03/04 09:49:19 by omougel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all libft clean fclean re

NAME = pipex

SRCS_FILES = pipex.c\
			 do_the_pipe.c\
			 fill_pipex.c

INCLUDES = include/pipex.h

LIBFT_DIR = libft/
SRCS_DIR = srcs/
OBJS_DIR = .objects/

SRCS = $(addprefix ${SRCS_DIR},${SRCS_FILES})
OBJS = $(patsubst %.c, ${OBJS_DIR}%.o, ${SRCS})

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT = libft/libft.a

HEADER = include/pipex.h libft/include/libft.h

all: libft ${NAME}
	@echo "${BOLD}${GREEN}${NAME} done!${END}"

${NAME}: ${OBJS} ${LIBFT} 
	cc ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}  

libft:
	${MAKE} -C ${LIBFT_DIR}
	@echo "${BOLD}${GREEN}$@ done!${END}"

${OBJS_DIR}%.o: %.c ${INCLUDES} Makefile
	mkdir -p $(shell dirname $@)
	cc ${CFLAGS} -c $< -o $@

clean:
	${MAKE} -C ${LIBFT_DIR} clean
	rm -rf ${OBJS_DIR}
	@echo "${BOLD}${RED}$@ done!${END}"

fclean: clean
	${MAKE} -C ${LIBFT_DIR} fclean
	rm -f ${NAME}
	@echo "${BOLD}${RED}$@ done!${END}"

re: fclean all

RED = \033[31m
GREEN = \033[32m
BOLD = \033[1m
END = \033[0m
