/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:05:30 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/08 21:25:13 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	get_flag(t_option *option, char **format)
{
	while (**format && (**format == ' ' || **format == '+' \
			|| **format == '0' || **format == '-' || **format == '#'))
	{
		if (**format == ' ')
			option->flag |= SIGN_SPACE;
		else if (**format == '+')
			option->flag |= SIGN_PLUS;
		else if (**format == '0')
			option->flag |= ZERO_PAD;
		else if (**format == '-')
			option->flag |= LEFT_ALIGN;
		else if (**format == '#')
			option->flag |= ALT_FORM;
		(*format)++;
	}
	if (option->flag & SIGN_PLUS)
		option->flag &= ~SIGN_SPACE;
	if (option->flag & LEFT_ALIGN)
		option->flag &= ~ZERO_PAD;
}

void	get_width(t_option *option, char **format)
{
	while (ft_isdigit(**format))
	{
		option->width = option->width * 10 + **format - '0';
		(*format)++;
	}
}

void	get_precision(t_option *option, char **format)
{
	if (**format == '.')
	{
		option->flag |= PRECISION;
		(*format)++;
	}
	while (ft_isdigit(**format))
	{
		option->precision = option->precision * 10 + **format - '0';
		(*format)++;
	}
	if (option->flag & PRECISION)
		option->flag &= ~ZERO_PAD;
}

t_option	get_option(char **format)
{
	t_option	option;

	ft_memset(&option, 0, sizeof(t_option));
	get_flag(&option, format);
	get_width(&option, format);
	get_precision (&option, format);
	if ((option.flag & PRECISION) == 0)
		option.precision = 1;
	option.pad_char = ' ';
	return (option);
}

void	parse_format(va_list p_arg, char **format, int *len)
{
	t_option	option;

	(*format)++;
	option = get_option(format);
	if (option.width < 0 || option.precision < 0)
	{
		*len = ERROR_GENERAL;
		return ;
	}
	if (**format == '%' || **format == 'c')
		*len = set_char(p_arg, **format, option);
	else if (**format == 's')
		*len = set_str(p_arg, option);
	else if (**format == 'd' || **format == 'i')
		*len = set_int(p_arg, **format, option);
	else if (**format == 'u' || **format == 'x' || **format == 'X')
		*len = set_uint(p_arg, **format, option);
	else if (**format == 'p')
		*len = set_addr(p_arg, **format, option);
	(*format)++;
}
