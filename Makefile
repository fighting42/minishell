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

SRCS_P	=	

SRCS_E	=	execute/execute.c

SRCS	=	main.c $(SRCS_P) $(SRCS_E)

OBJS 	=	$(SRCS:.c=.o)

MKLIB	=	make -C libft

LIBFT 	=	libft/libft.a

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