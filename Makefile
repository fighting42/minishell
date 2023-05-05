# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 16:32:28 by yejinkim          #+#    #+#              #
#    Updated: 2023/03/29 16:32:28 by yejinkim         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CFLAGS	=	-Wall -Wextra -Werror -g

RFLAGS	=	-lreadline \
			-L /Users/$(USER)/.brew/opt/readline/lib \
			-I /Users/$(USER)/.brew/opt/readline/include

SRCS_P	=	srcs/parser/parse_command.c \
			srcs/parser/parse_split.c \
			srcs/parser/parse_utils.c \
			srcs/parser/parsing.c \

SRCS_E	=	srcs/execute/execute.c \
			srcs/execute/init.c \
			srcs/execute/pipe.c \
			srcs/execute/test.c \
			srcs/execute/redirection.c
	
SRCS_B	=	srcs/builtin/builtin.c \
			srcs/builtin/env_utils.c \
			srcs/builtin/ft_echo.c \
			srcs/builtin/ft_cd.c \
			srcs/builtin/ft_pwd.c \
			srcs/builtin/ft_export.c \
			srcs/builtin/ft_unset.c \
			srcs/builtin/ft_env.c \
			srcs/builtin/ft_exit.c

SRCS	=	srcs/main.c $(SRCS_P) $(SRCS_E) $(SRCS_B)

OBJS 	=	$(SRCS:.c=.o)

MKLIB	=	make -C srcs/libft

LIBFT 	=	srcs/libft/libft.a

all 	:	$(NAME)

$(NAME) :	$(OBJS)
			$(MKLIB)
			$(CC) $(CFLAGS) $(RFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

clean   :	
			$(RM) $(OBJS)
			$(MKLIB) clean

fclean  :	clean
			$(RM) $(NAME) $(LIBFT)

re		:	fclean all

.PHONY  :	all clean fclean re bonus