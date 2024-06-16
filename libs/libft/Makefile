# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 12:49:20 by hyeunkim          #+#    #+#              #
#    Updated: 2024/06/16 17:24:52 by hyeunkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = libft.a
# **************************************************************************** #
CFLAGS = -Wall -Wextra -Werror -MMD -MP #-O0 -g3 -fsanitize=address
# **************************************************************************** #
RESET = \033[0m

BOLD = \033[1m

RED = \033[31m
GREEN = \033[32m

Q = @
# **************************************************************************** #
src_man = ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_isspace.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\

src_bonus = ft_lstnew_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstadd_back_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c\

gnl_src = get_next_line.c\
		get_next_line_utils.c\

GNL_DIR = ./gnl

ft_printf_src = ft_printf_bonus.c\
				ft_ltoa_base.c\
				ft_parse_format_bonus.c\
				manage_field_bonus.c\
				set_conversion_bonus.c\
				set_option_bonus.c\

FT_PRINTF_DIR = ./ftprintf

SRCS = $(src_man) $(src_bonus)\
		$(addprefix $(GNL_DIR)/,$(gnl_src))\
		$(addprefix $(FT_PRINTF_DIR)/,$(ft_printf_src))\

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

-include $(DEPS)
# **************************************************************************** #
all : $(NAME)

$(NAME) : $(OBJS)
	$(Q) ar rcs $@ $^
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)LIBFT$(RESET) OK"

%.o : %.c
	$(Q) $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus : $(NAME)

clean :
	$(Q) $(RM) $(DEPS)
	$(Q) $(RM) $(OBJS)
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)LIBFT$(RESET) object files OK"

fclean : clean
	$(Q) $(RM) $(NAME)
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)LIBFT$(RESET) OK"


re : fclean
	$(Q) make all

.PHONY : clean fclean re all bonus
