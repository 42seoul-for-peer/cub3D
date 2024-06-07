/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:47:46 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/08 23:46:41 by hyeunkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			idx;
	unsigned char	*s1;
	unsigned char	*s2;

	idx = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (idx < n)
	{
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		else
			idx++;
	}
	return (0);
}
