NAME	=	ft_ssl
LIB		=	libft/libft.a
SRC		=	new_des.c ft_ssl_main.c base64.c
OBJ		=	$(SRC:.c=.o)
FLAGS	=	-Wall -Wextra -Werror -g3

all:	$(NAME)

$(NAME):	$(SRC) $(OBJ) ft_ssl.h
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L. $(LIB) 

$(OBJ):		$(SRC) $(LIB)
	gcc -c $(SRC) -g3

$(LIB):		libft/*.c
	make -C libft

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

tests: test1 test0 test2 test3 test4

test1:	test.c
	gcc -o run1 test.c

test0:	test1.c
	gcc -o run0 test1.c

test2:	test2.c
	gcc -o run2 test2.c

test3:	test3.c
	gcc -o run3 test3.c

test4:	test4.c
	gcc -o run4 test4.c

testclean:
	rm -f run0 run1 run2 run3 run4