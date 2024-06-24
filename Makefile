# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 21:19:13 by hyeunkim          #+#    #+#              #
#    Updated: 2024/06/24 15:22:52 by hyeunkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
MLX = mlx
# **************************************************************************** #
LIB_DIR = ./libs/libft

CFLAGS = -Wall -Wextra -Werror -MMD -MP
CPPFLAGS = -I$(LIB_DIR)

LDFLAGS = -L$(LIB_DIR) -framework OpenGL -framework AppKit
LDLIBS = -lft -lmlx
# **************************************************************************** #
ifdef DEBUG
	CFLAGS += -O0 -g3 -fsanitize=address
endif
# alias md = "make DEBUG=1"
# **************************************************************************** #
RESET = \033[0m

BOLD = \033[1m

RED = \033[31m
GREEN = \033[32m
GRAY = \033[90m

Q = @
# **************************************************************************** #
COMP_SRCS = $(if $(filter bonus, $(MAKECMDGOAL)),$(SRCS_B),$(SRCS_M))
OBJS = $(COMP_SRCS:.c=.o)
DEPS = $(COMP_SRCS:.c=.d)
-include $(DEPS)
# **************************************************************************** #
MAN_DIR = ./mandatory

src_m = cub3d.c\
		checker.c\
		checker_util.c\
		init.c\
		set_map_data.c\
		validate_scene.c\
		ray_loop.c\
		draw.c\
		calc.c\
		action.c\
		util.c\
		error.c\

SRCS_M = $(addprefix $(MAN_DIR)/,$(src_m))
OBJS_M = $(SRCS_M:.c=.o)
DEPS_M = $(SRCS_M:.c=.d)
# **************************************************************************** #
BON_DIR = ./bonus

src_b = \

SRCS_B = $(addprefix $(BON_DIR)/,$(src_b))
OBJS_B = $(SRCS_B:.c=.o)
DEPS_B = $(SRCS_B:.c=.d)
# **************************************************************************** #
TEST_DIR = ./test

src_t = test_main.c\

SRCS_T = $(addprefix $(TEST_DIR)/,$(src_t))
OBJS_T = $(SRCS_T:.c=.o)
DEPS_T = $(SRCS_T:.c=.d)
# **************************************************************************** #
.PHONY : all clean fclean re bonus

all : $(NAME)

%.o : %.c
	$(Q) $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(Q) $(MAKE) .mandatory

clean :
	$(Q) $(MAKE) -C $(LIB_DIR) clean
	$(Q) $(RM) $(wildcard $(MAN_DIR)/*.o) $(wildcard $(MAN_DIR)/*.d)
	$(Q) $(RM) $(wildcard $(BON_DIR)/*.o) $(wildcard $(BON_DIR)/*.d)
	$(Q) $(RM) $(wildcard $(TEST_DIR)/*.o) $(wildcard $(TEST_DIR)/*.d)
	$(Q) $(RM) .mandatory .bonus
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)cub3D$(RESET) object files OK"

fclean : clean
	$(Q) $(MAKE) -C $(LIB_DIR) fclean
	$(Q) $(RM) $(NAME)
	$(Q) echo "\t$(RED)$@$(RESET) $(BOLD)cub3D$(RESET) OK"

re : fclean
	$(Q) $(MAKE) -C $(LIB_DIR)
	$(Q) $(MAKE) $(NAME)

.mandatory : $(OBJS_M)
	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
	$(Q) $(MAKE) -C $(LIB_DIR)
	$(Q) $(RM) .bonus $(OBJS_B) $(DEPS_B)
	$(Q) touch $@
	$(Q) $(CC) $(CFLAGS) $(OBJS_M) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)cub3D$(RESET) mandatory OK"

.bonus : $(OBJS_B)
	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
	$(Q) $(MAKE) -C $(LIB_DIR) all
	$(Q) $(RM) .mandatory $(OBJS_M) $(DEPS_M)
	$(Q) touch $@
	$(Q) $(CC) $(CFLAGS) $(OBJS_B) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)cub3D$(RESET) bonus OK"
# **************************************************************************** #
test_exe : $(OBJS_T)
	$(Q) echo "$(GRAY)---------------- start compiling ----------------$(RESET)"
	$(Q) $(CC) $(CFLAGS) $(OBJS_T) $(LDFLAGS) $(LDLIBS) -o $@
	$(Q) echo "\t$(GREEN)make$(RESET) $(BOLD)test case$(RESET) OK"