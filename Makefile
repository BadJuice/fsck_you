##
## Makefile
##
## by Thomas Murgia
## login	<thomasmurgi@hotmail.fr>
##
## Started on Mon Apr 04 10:11:06 2016 Thomas Murgia
## Last update Wed May 04 22:15:48 2016 Thomas Murgia
##

CC	= gcc
RM	= rm -rf
NAME	= fsck_you
SRCS	= source/fsck_you.c
OBJS	= $(SRCS:.c=.o).
CFLAGS	= -O2 -g3 -ansi -Wall -Wextra -Werror -pedantic -std=c99

all	: $(NAME)

$(NAME)	: $(OBJS)
	  $(CC) -o $(NAME) $(SRCS) $(CFLAGS)

clean	:
	  $(RM) $(OBJS)

fclean	: clean
	  $(RM) $(NAME)

re	: fclean all
