/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_field_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:54:46 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/07 19:21:00 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*set_field(t_option *option)
{
	char	*field;
	int		pad_len;

	if (option->width < option->arg_len)
		option->width = option->arg_len;
	field = (char *)malloc(sizeof(char) * (option->width + 1));
	if (!field)
		return (NULL);
	ft_memset(field, option->pad_char, option->width);
	field[option->width] = 0;
	if (option->flag & PRECISION)
	{
		pad_len = option->width - option->precision;
		if (pad_len >= 0)
		{
			if (option->flag & LEFT_ALIGN)
				ft_memset(field + option->sign_len, '0', option->precision);
			else
				ft_memset(field + pad_len, '0', option->precision);
		}
	}
	return (field);
}

void	set_precision_width_num(t_option *option, char *arg_str)
{
	if (option->flag & PRECISION)
	{
		if (*arg_str == '0' && option->precision == 0)
			option->arg_len = 0;
		if (option->precision < option->arg_len)
			option->precision = option->arg_len;
		if (option->width < option->precision + option->sign_len)
			option->width = option->precision + option->sign_len;
	}
	else if (option->width < option->arg_len + option->sign_len)
		option->width = option->arg_len + option->sign_len;
}

void	set_left_align(t_option option, char *arg, char **field)
{
	int	pad_len;

	ft_memcpy(*field, option.sign, option.sign_len);
	if (option.flag & PRECISION)
	{
		pad_len = option.precision - option.arg_len;
		ft_memcpy((*field) + option.sign_len + pad_len, arg, option.arg_len);
	}
	else
		ft_memcpy((*field) + option.sign_len, arg, option.arg_len);
}

void	set_right_align(t_option option, char *arg, char **field)
{
	int	pad_len;
	int	arg_start;

	arg_start = option.width - option.arg_len;
	ft_memcpy((*field) + arg_start, arg, option.arg_len);
	if (option.flag & ZERO_PAD)
		ft_memcpy(*field, option.sign, option.sign_len);
	else
	{
		if (option.flag & PRECISION)
			pad_len = option.width - option.precision - option.sign_len;
		else
			pad_len = option.width - option.arg_len - option.sign_len;
		ft_memcpy((*field) + pad_len, option.sign, option.sign_len);
	}
}

void	set_align(t_option opt, char *arg, char **field)
{
	if (opt.flag & LEFT_ALIGN)
		set_left_align(opt, arg, field);
	else
		set_right_align(opt, arg, field);
}
