/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:00:29 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/01/08 17:30:30 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

/* ******************************** HEADER ********************************** */
# include <stdarg.h>
# include "../libft.h"

/* ******************************** MACRO *********************************** */
/* num */
# define ERROR_GENERAL (-1)

/* char */
# define LOW_HEX_SYM ('x')
# define UP_HEX_SYM ('X')
# define ADDRESS ('p')

/* string */
# define BASE ("0123456789abcdef0123456789ABCDEF")

/* ************************* USER DEFINED STRUCTURE ************************* */
typedef struct s_option
{
	char	flag;
	char	pad_char;
	int		width;
	int		precision;
	int		arg_len;
	int		sign_len;
	char	*sign;
}	t_option;

/* MACRO FOR STRUCTURE */
# define SIGN_SPACE (1)
# define SIGN_PLUS (2)
# define ZERO_PAD (4)
# define LEFT_ALIGN (8)
# define ALT_FORM (16)
# define PRECISION (32)
# define NEG_VAL (64)

/* ******************************* FUNCTIONS ******************************** */
/* ft_printf_bonus.c */
int		ft_printf(const char *format, ...);
void	ft_print_format(va_list p_arg, const char *format, int *result);

/* ft_parse_format_bonus.c */
void	parse_format(va_list p_arg, char **format, int *len);
void	get_flag(t_option *option, char **format);
void	get_width(t_option *option, char **format);
void	get_precision(t_option *option, char **format);
/* set_conversion_bonus.c */
int		set_char(va_list p_arg, char conversion, t_option options);
int		set_str(va_list p_arg, t_option options);
int		set_int(va_list p_arg, char conversion, t_option options);
int		set_uint(va_list p_arg, char conversion, t_option options);
int		set_addr(va_list p_arg, char conversion, t_option option);

/* set_option_bonus.c */
void	set_option_str(t_option *opt, char *arg);
void	set_option_int(t_option *opt, char *arg_str);
void	set_option_uint(t_option *options, char *arg, char conversion);

/* manage_field_bonus.c */
char	*set_field(t_option *option);
void	set_precision_width_num(t_option *option, char *arg_str);
void	set_left_align(t_option options, char *arg, char **field);
void	set_align(t_option options, char *arg, char **field);

/* ft_ltoa_base.c */
char	*ft_ltoa_base(size_t num, char base);

#endif