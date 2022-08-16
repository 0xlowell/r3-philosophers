# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzima <marvin@42lausanne.ch>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 11:50:59 by lzima             #+#    #+#              #
#    Updated: 2022/08/08 11:51:13 by lzima            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# COLORS

GREEN	= \033[1;32m
RED 	= \033[1;31m
ORANGE	= \033[1;33m
BUILD	= \e[38;5;225m
SEP		= \e[38;5;120m
DUCK	= \e[38;5;227m
RESET	= \033[0m

# COLORS


SRCS_DIR		= ./src/
SRCS_FILES		= main.c main_utils.c utils.c parsing.c print.c

SRCS			:= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}

O_DIR			= ./objs/

OBJS_FILES		:= ${SRCS_FILES:.c=.o}

OBJS			:= ${patsubst %, ${O_DIR}%, ${OBJS_FILES}}

HEADS_DIR		= ./includes/

NAME			= philo


MAKELIB			= ${MAKE} -C
CC				= gcc
AR				= ar rcs
MKDIR			= mkdir
RM				= rm -rf

CFLAGS			= -Wall -Wextra -Werror -g3 -pthread -fsanitize=address

TSEP			= ${SEP}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=${RESET}



all:			${NAME}

${NAME}:		${O_DIR} ${OBJS}
			@printf "\n"

			@printf "${GREEN} 💻 Successfully compiled ${NAME} .o's${RESET} ✅\n"

				@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
			@printf "${GREEN} 💻 Successfully created ${NAME} executable${RESET} ✅\n"

${O_DIR}:
				@${MKDIR} ${O_DIR}
			@printf "\n${BUILD}${O_DIR} Directory Created 📎${RESET}\n\n"

${O_DIR}%.o:${SRCS_DIR}%.c
				@${CC} ${CFLAGS} -I${HEADS_DIR} -o $@ -c $<
				@printf "\e[1K\r${BUILD} 🚧 $@ from $<${RESET}"

clean :
				@${RM} ${O_DIR}
				@printf "${RED} 🧹 Deleted ${NAME} .o's${RESET} ❌\n"

fclean :
				@${RM} ${O_DIR}
				@printf "${RED} 🧹 Deleted ${NAME} .o's${RESET} ❌\n"
				@${RM} ${NAME} ${NAME}.dSYM
				@printf "${RED} 💥 Deleted ${NAME} files${RESET} ❌\n"

re : 			fclean all

norm :
				@printf "${DUCK} 🐥 Checking Norm for ${NAME}${RESET}\n"
				@norminette ${SRCS}
				@norminette ${HEADS_DIR}

.PHONY : all clean fclean re norm
