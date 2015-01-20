#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 15:15:50 by ftaffore          #+#    #+#              #
#    Updated: 2015/01/18 16:24:19 by chery            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	mod1

CC			=	g++

RM			=	rm -rf

INCLUDES	=	-I includes \
				-I $(HOME)/Library/Frameworks/SDL2.framework/Headers \
				-I $(HOME)/Library/Frameworks/SDL2_image.framework/Headers \
				-I $(HOME)/Library/Frameworks/SDL2_ttf.framework/Headers

LIBS		=	$(HOME)/Library/Frameworks/SDL2.framework/SDL2 \
				$(HOME)/Library/Frameworks/SDL2_image.framework/SDL2_image \
				$(HOME)/Library/Frameworks/SDL2_ttf.framework/SDL2_ttf \
				-framework GLUT -framework OpenGL -framework Cocoa

CFLAGS		=	-Wno-deprecated-declarations -Werror -Wall -Wextra

SRCS		=	main.cpp
				
OBJS		=	$(SRCS:.cpp=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) -o $@ $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES)

.cpp.o		:
				$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
