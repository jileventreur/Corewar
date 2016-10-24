# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darabi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 18:19:45 by darabi            #+#    #+#              #
#    Updated: 2015/12/12 17:01:27 by darabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strcpy.c ft_strdup.c \
	   ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	   ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strcmp.c \
	   ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	   ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_issign.c\
	   ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	   ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	   ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	   ft_itoa.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_int_size.c ft_recursive_power.c ft_swap.c ft_strrev.c ft_list_last.c \
	   ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
	   ft_lstnew.c ft_puttab.c get_next_line.c \
	   ft_watoi.c ft_strwdup.c \
	   ft_printf.c \
		precision.c mask_unicode.c width.c null_char.c wstr_precision.c\
		flags.c type_flags.c checking_for.c n_func.c\
		applying.c conversion.c zero_conv.c\
		ft_alloc.c to_str.c  ft_del_str.c\
		color_part_two.c ft_watoi.c\
		h_test.c jz_test.c l_test.c basic_test.c \
		ft_itoa_ll.c reverse.c ft_strwdup.c color.c ft_strncpy_wchar.c

OBJECT = $(SRCS:.c=.o)

$(NAME):
		gcc -c -g $(SRCS) -I ./
		ar rc $(NAME) $(OBJECT)
		ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
