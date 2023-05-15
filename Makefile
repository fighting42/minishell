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

RINC	=	-I /Users/$(USER)/.brew/opt/readline/include

RLIB	=	-L /Users/$(USER)/.brew/opt/readline/lib

# RINC	=	-I/opt/homebrew/opt/readline/include

# RLIB	=	-L/opt/homebrew/opt/readline/lib

SRCS_P	=	srcs/parser/parse_command.c \
			srcs/parser/parse_command_env.c \
			srcs/parser/parse_dollar.c \
			srcs/parser/parse_dollar_env.c \
			srcs/parser/parse_error.c \
			srcs/parser/parse_error_2.c \
			srcs/parser/parse_free.c \
			srcs/parser/parse_init.c \
			srcs/parser/parse_quote.c \
			srcs/parser/parse_quote_utils.c \
			srcs/parser/parse_redir_pipe.c \
			srcs/parser/parse_split.c \
			srcs/parser/parse_utils.c \
			srcs/parser/parsing.c \

SRCS_E	=	srcs/execute/execute.c \
			srcs/execute/init.c \
			srcs/execute/pipe.c \
			srcs/execute/redirection.c  \
			srcs/execute/heredoc.c

SRCS_B	=	srcs/builtin/builtin.c \
			srcs/builtin/env_utils1.c \
			srcs/builtin/env_utils2.c \
			srcs/builtin/ft_echo.c \
			srcs/builtin/ft_cd.c \
			srcs/builtin/ft_pwd.c \
			srcs/builtin/ft_export.c \
			srcs/builtin/ft_unset.c \
			srcs/builtin/ft_env.c \
			srcs/builtin/ft_exit.c

SRCS_U	=	srcs/utils/signal.c \
			srcs/utils/error.c \
			srcs/utils/get_next_line.c \
			srcs/utils/ft_strjoin_free.c \
			srcs/utils/env_heredoc.c \
			srcs/utils/env_heredoc_utils.c \
			srcs/utils/free_utils.c

SRCS	=	srcs/main.c $(SRCS_P) $(SRCS_E) $(SRCS_B) $(SRCS_U)

OBJS 	=	$(SRCS:.c=.o)

LDIR	=	srcs/libft

LIBFT 	=	$(LDIR)/libft.a


%.o		:	%.c
			$(CC) $(CFLAGS) $(RINC) -c $< -o $@

all 	:	
			make -C $(LDIR) 
			make $(NAME)

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(RLIB) $(OBJS) $(LIBFT) -o $(NAME) -lreadline 

clean   :	
			make -C $(LDIR) clean
			$(RM) $(OBJS)

fclean  :	clean
			$(RM) $(LIBFT) $(NAME) 

re		:	fclean all

.PHONY  :	all clean fclean re bonus
