/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:05:07 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/19 14:03:00 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int val)
{
	size_t	len;

	val %= 256;
	len = ft_strlen(str);
	if (!val)
		return ((char *)str + len);
	while (*str)
	{
		if (*str == val)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
