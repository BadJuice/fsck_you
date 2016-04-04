##
## Makefile
##
## by Thomas Murgia
## login	<thomasmurgi@hotmail.fr>
##
## Started on Mon Apr 04 10:11:06 2016 Thomas Murgia
## Last update Mon Apr 04 10:11:06 2016 Thomas Murgia
##

## if you're using clang, f**k you!
CC	= gcc
RM	= rm -rf
NAME	= fsck_you
SRCS	= fsck_you.c
OBJS	= $(SRCS:.c=.o)
OFLD	= obj
## it's better to compile with nazi flags. Trust me, I'm a doctor.
FLAGS	= -O1 -g3 -ansi -Wall -Wextra -pedantic

all	: $(NAME)

$(NAME)	: $(OBJS)
	  $(CC) -o $(NAME) $(SRCS) $(FLAGS)
	  mv $(OBJS) $(OFLD)

clean	:
	  $(RM) $(OBJS)

fclean	: clean
	  $(RM) $(NAME)

re	: fclean all
