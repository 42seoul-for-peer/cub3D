/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_option_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 00:32:56 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/07 19:21:05 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	set_option_str(t_option *option, char *arg)
{
	option->flag &= ~(1 + 2 + 4 + 16);
	option->arg_len = ft_strlen(arg);
	if (option->arg_len == 0)
	{
		option->flag &= ~PRECISION;
		option->precision = 0;
	}
	if (option->flag & PRECISION)
		if (option->precision < option->arg_len)
			option->arg_len = option->precision;
	option->flag &= ~PRECISION;
}

void	set_option_int(t_option *option, char *arg)
{
	option->flag &= ~ALT_FORM;
	if (option->flag & SIGN_SPACE)
		option->sign = " ";
	else if (option->flag & SIGN_PLUS)
		option->sign = "+";
	else
		option->sign = "";
	if (option->flag & NEG_VAL)
		option->sign = "-";
	if (option->flag & ZERO_PAD)
		option->pad_char = '0';
	option->sign_len = ft_strlen(option->sign);
	option->arg_len = ft_strlen(arg);
	set_precision_width_num(option, arg);
}

void	set_option_uint(t_option *option, char *arg, char conversion)
{
	if (conversion == 'u' || *arg == '0')
		option->flag &= ~ALT_FORM;
	if (conversion == ADDRESS)
		option->flag |= ALT_FORM;
	if (option->flag & SIGN_PLUS)
		option->sign = "+";
	else if (option->flag & SIGN_SPACE)
		option->sign = " ";
	else if (option->flag & ALT_FORM)
	{
		if (conversion == LOW_HEX_SYM || conversion == ADDRESS)
			option->sign = "0x";
		if (conversion == UP_HEX_SYM)
			option->sign = "0X";
	}
	else
		option->sign = "";
	if (option->flag & ZERO_PAD)
		option->pad_char = '0';
	option->sign_len = ft_strlen(option->sign);
	option->arg_len = ft_strlen(arg);
	set_precision_width_num(option, arg);
}
