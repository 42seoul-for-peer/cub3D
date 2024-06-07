/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:23:18 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/01/08 18:49:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	get_digit(size_t num, char base)
{
	int		digit;
	size_t	base_num;

	digit = 0;
	base_num = 10;
	if (base == LOW_HEX_SYM || base == UP_HEX_SYM || base == ADDRESS)
		base_num = 16;
	while (num != 0)
	{
		digit++;
		num /= base_num;
	}
	return (digit);
}

void	l_to_arr(size_t num, int digit, char **res, char base)
{
	int		idx;
	size_t	remain;
	size_t	base_num;

	idx = 0;
	base_num = 10;
	if (base == LOW_HEX_SYM || base == UP_HEX_SYM || base == ADDRESS)
		base_num = 16;
	while (idx < digit)
	{
		remain = num % base_num;
		if (base == UP_HEX_SYM)
			(*res)[digit - idx - 1] = BASE[remain + 16];
		else
			(*res)[digit - idx - 1] = BASE[remain];
		num /= base_num;
		idx++;
	}
	(*res)[digit] = 0;
}

char	*ft_ltoa_base(size_t num, char base)
{
	int		digit;
	char	*result;

	if (num == 0)
		digit = 1;
	else
		digit = get_digit(num, base);
	result = (char *)malloc(sizeof(char) * (digit + 1));
	if (!result)
		return (NULL);
	l_to_arr(num, (int) digit, &result, base);
	return (result);
}
