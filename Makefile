# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 00:22:02 by maheraul          #+#    #+#              #
#    Updated: 2023/04/16 04:39:37 by maheraul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

NAME_BONUS		=	pipex_bonus

LIBFT			=	libft.a

GNL				=	get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c

PRINTF			=	libftprintf.a

SRCS			=	srcs/main.c \
					srcs/utils.c \
					srcs/pipex.c \
					srcs/redirection.c


SRCS_BONUS		=	bonus/main.c \
					bonus/utils.c \
					bonus/pipex.c \
					bonus/redirection.c


OBJS			=	${SRCS:.c=.o}

OBJS_GNL		=	${GNL:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

HEAD			=	-Iincludes

CC				=	cc

CFLAGS			=	-Iincludes -Ift_printf -Ilibft -Iget_next_line -g3 -Wall -Werror -Wextra

all				:	${NAME}

bonus			: ${NAME_BONUS}

$(NAME): $(OBJS) ${OBJS_GNL}
	@make -C libft
	@make -C ft_printf
	@mv libft/libft.a .
	@mv ft_printf/libftprintf.a .
	cc $(HEAD) $(OBJS)  ${LIBFT} ${OBJS_GNL} ${PRINTF} -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS) ${OBJS_GNL}
	@make -C libft
	@make -C ft_printf
	@mv libft/libft.a .
	@mv ft_printf/libftprintf.a .
	cc $(HEAD) $(OBJS_BONUS) ${OBJS_GNL} ${LIBFT} ${PRINTF} -o $(NAME_BONUS)



clean			:
					make clean -C libft
					make clean -C ft_printf
					rm -rf ${OBJS} $(OBJS_GNL) ${OBJS_BONUS}

fclean			:	clean
					make fclean -C libft
					make fclean -C ft_printf
					rm -rf ${LIBFT}
					rm -rf ${PRINTF}
					rm -rf ${NAME}
					rm -rf ${NAME_BONUS}

re				:	fclean all

.PHONY			:	all clean fclean re bonus
