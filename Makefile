# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 17:02:16 by omougel           #+#    #+#              #
#    Updated: 2024/03/08 13:35:56 by omougel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all libft clean fclean re bonus

NAME = pipex
BONUS_NAME = pipex_bonus

SRCS_FILES = pipex.c\
			 parsing.c\
			 child_execution.c

BONUS_FILES = pipex_bonus.c\
			 parsing_bonus.c\
			 child_execution_bonus.c

INCLUDES = include/pipex.h

LIBFT_DIR = libft/
SRCS_DIR = srcs/
BONUS_DIR = bonus/
OBJS_DIR = .objects/
BONUS_OBJS_DIR = .bonus_objects/

SRCS = $(addprefix ${SRCS_DIR},${SRCS_FILES})
BONUS_SRCS = $(addprefix ${BONUS_DIR},${BONUS_FILES})
OBJS = $(patsubst %.c, ${OBJS_DIR}%.o, ${SRCS})
BONUS_OBJS = $(patsubst %.c, ${BONUS_OBJS_DIR}%.o, ${BONUS_SRCS}) 

CFLAGS = -Wall -Wextra -Werror
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
	rm -rf ${BONUS_OBJS_DIR}
	@echo "${BOLD}${RED}$@ done!${END}"

fclean: clean
	${MAKE} -C ${LIBFT_DIR} fclean
	rm -f ${NAME}
	rm -f ${BONUS_NAME}
	@echo "${BOLD}${RED}$@ done!${END}"

re: fclean all

bonus: ${BONUS_OBJS} ${LIBFT}
	cc ${CFLAGS} ${BONUS_OBJS} ${LIBFT} -o ${BONUS_NAME}
	@echo "${BOLD}${GREEN}$@ done!${END}"

${BONUS_OBJS_DIR}%.o: %.c ${INCLUDES} Makefile
	mkdir -p $(shell dirname $@)
	cc ${CFLAGS} -c $< -o $@

RED = \033[31m
GREEN = \033[32m
BOLD = \033[1m
END = \033[0m
