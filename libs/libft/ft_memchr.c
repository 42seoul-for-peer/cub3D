/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:17 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/13 14:48:10 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int val, size_t size)
{
	size_t			idx;
	unsigned char	temp_val;
	unsigned char	*temp_str;

	idx = 0;
	temp_val = (unsigned char) val;
	temp_str = (unsigned char *)str;
	while (idx < size)
	{
		if (temp_str[idx] == temp_val)
			return ((void *)(str + idx));
		idx++;
	}
	return (NULL);
}
