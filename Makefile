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

RINCS	=	-I /Users/$(USER)/.brew/opt/readline/include

RLIBS	=	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib

SRCS_P	=	srcs/parser/parse_command.c \
			srcs/parser/parse_dollar.c \
			srcs/parser/parse_error.c \
			srcs/parser/parse_init.c \
			srcs/parser/parse_quote.c \
			srcs/parser/parse_dollar_env.c \
			srcs/parser/parse_redir_pipe.c \
			srcs/parser/parse_split.c \
			srcs/parser/parse_utils.c \
			srcs/parser/parsing.c \

SRCS_E	=	srcs/execute/execute.c \
			srcs/execute/init.c \
			srcs/execute/pipe.c \
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

SRCS_U	=	srcs/utils/signal.c \
			srcs/utils/error.c

SRCS	=	srcs/main.c $(SRCS_P) $(SRCS_E) $(SRCS_B) $(SRCS_U)

OBJS 	=	$(SRCS:.c=.o)

LDIR	=	srcs/libft

LIBFT 	=	$(LDIR)/libft.a


%.o		:	%.c
			$(CC) $(CFLAGS) $(RINCS) -c $< -o $@

all 	:	
			make -C $(LDIR) 
			make $(NAME)

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(RLIBS) $(OBJS) $(LIBFT) -o $(NAME) 

clean   :	
			make -C $(LDIR) clean
			$(RM) $(OBJS)

fclean  :	clean
			$(RM) $(LIBFT) $(NAME) 

re		:	fclean all

.PHONY  :	all clean fclean re bonus