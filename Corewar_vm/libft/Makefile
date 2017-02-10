NAME =	libft.a

SRCS =	ft_printf.c \
		ft_dprintf.c \
		ft_asprintf.c \
		ft_general_print.c\
		pf_conv.c \
		pf_conv_bonus_b.c \
		pf_conv_c.c \
		pf_conv_d.c \
		pf_conv_invalid.c \
		pf_conv_majc.c \
		pf_conv_majd.c \
		pf_conv_majo.c \
		pf_conv_majs.c \
		pf_conv_maju.c \
		pf_conv_majx.c \
		pf_conv_majxl.c \
		pf_conv_n.c \
		pf_conv_o.c \
		pf_conv_p.c \
		pf_conv_percent.c \
		pf_conv_s.c \
		pf_conv_u.c \
		pf_conv_x.c \
		pf_conv_xl.c \
		pf_flag_hash.c \
		pf_flag_min_width.c \
		pf_flag_plus.c \
		pf_flag_precision.c \
		pf_flag_space.c \
		pf_flags.c \
		pf_flags_check.c \
		pf_fn.c \
		pf_buf.c \
		pf_malloc_put.c \
		ft_putnbr_base.c \
		ft_putlnbr_base.c \
		pf_nb_base_int.c 

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft_fcts/libft.a $(OBJS)
	@cp libft_fcts/libft.a $(NAME)
	@ar r $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJS): %.o: %.c
	@gcc -Wall -Wextra -Werror -I includes -c $<

libft_fcts/libft.a:
	@make -C libft_fcts

clean:
	@rm -f $(OBJS)
	@make fclean -C libft_fcts

fclean: clean
	@rm -f $(NAME)

re: fclean all
