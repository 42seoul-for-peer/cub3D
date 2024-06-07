/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:15:03 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/16 10:19:06 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	size_t	idx;

	idx = 0;
	while (str[idx])
	{
		f(idx, str + idx);
		idx++;
	}
	return ((void *)str);
}
