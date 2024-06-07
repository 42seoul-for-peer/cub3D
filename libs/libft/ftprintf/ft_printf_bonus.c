/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:22:55 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/01/08 17:30:02 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_print_format(va_list p_arg, const char *format, int *result)
{
	int		len;
	char	*temp;

	temp = (char *)format;
	while (*format && *result != ERROR_GENERAL)
	{
		if (*format == '%')
		{
			parse_format(p_arg, (char **)&format, &len);
			temp = (char *)format;
		}
		else
		{
			while (*format != '%' && *format != 0)
				format++;
			len = write(1, temp, format - temp);
		}
		if (len < 0)
			*result = ERROR_GENERAL;
		else
			*result += len;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	p_arg;
	int		result;

	va_start(p_arg, format);
	result = 0;
	ft_print_format(p_arg, format, &result);
	va_end(p_arg);
	return (result);
}
