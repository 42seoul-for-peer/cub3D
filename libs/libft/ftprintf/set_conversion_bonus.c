/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_conversion_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:02:04 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/12/07 18:07:48 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	set_char(va_list p_arg, char conversion, t_option option)
{
	int		len;
	char	arg;
	char	*field;

	option.flag &= ~(1 + 2 + 4 + 16 + 32);
	option.arg_len = 1;
	if (conversion == '%')
		arg = '%';
	else
		arg = (char)va_arg(p_arg, int);
	if (arg == 0)
		arg = '\0';
	field = set_field(&option);
	if (!field)
		return (ERROR_GENERAL);
	if (option.flag & LEFT_ALIGN)
		field[0] = arg;
	else
		field[option.width - 1] = arg;
	len = write(1, field, option.width);
	free(field);
	return (len);
}

int	set_str(va_list p_arg, t_option option)
{
	int		len;
	char	*arg;
	char	*field;

	arg = va_arg(p_arg, char *);
	if (!arg)
		arg = "(null)";
	set_option_str(&option, arg);
	field = set_field(&option);
	if (!field)
		return (ERROR_GENERAL);
	set_align(option, arg, &field);
	len = write(1, field, option.width);
	free(field);
	return (len);
}

int	set_int(va_list p_arg, char conversion, t_option option)
{
	int			len;
	long long	arg;
	char		*arg_str;
	char		*field;

	arg = va_arg(p_arg, int);
	if (arg < 0)
	{
		arg_str = ft_ltoa_base(arg * -1, conversion);
		option.flag |= NEG_VAL;
	}
	else
		arg_str = ft_ltoa_base(arg, conversion);
	set_option_int(&option, arg_str);
	field = set_field(&option);
	if (!field)
		return (ERROR_GENERAL);
	set_align(option, arg_str, &field);
	len = write(1, field, option.width);
	free(field);
	free(arg_str);
	return (len);
}

int	set_uint(va_list p_arg, char conversion, t_option option)
{
	int					len;
	unsigned long long	arg;
	char				*arg_str;
	char				*field;

	arg = (unsigned int)va_arg(p_arg, int);
	arg_str = ft_ltoa_base(arg, conversion);
	set_option_uint(&option, arg_str, conversion);
	field = set_field(&option);
	if (!field)
		return (ERROR_GENERAL);
	set_align(option, arg_str, &field);
	len = write(1, field, option.width);
	free(field);
	free(arg_str);
	return (len);
}

int	set_addr(va_list p_arg, char conversion, t_option option)
{
	int					len;
	unsigned long long	arg;
	char				*arg_str;
	char				*field;

	arg = (unsigned long long)va_arg(p_arg, void *);
	arg_str = ft_ltoa_base(arg, conversion);
	set_option_uint(&option, arg_str, conversion);
	field = set_field(&option);
	if (!field)
		return (ERROR_GENERAL);
	set_align(option, arg_str, &field);
	len = write(1, field, option.width);
	free(field);
	free(arg_str);
	return (len);
}
