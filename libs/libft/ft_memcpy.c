/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:05 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/19 13:06:02 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	char	*temp_d;
	char	*temp_s;
	size_t	idx;

	idx = 0;
	temp_d = (char *)dst;
	temp_s = (char *)src;
	while (idx < size && (dst || src))
	{
		temp_d[idx] = temp_s[idx];
		idx++;
	}
	return (dst);
}
