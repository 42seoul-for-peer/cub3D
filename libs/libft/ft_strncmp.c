/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:35:28 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/13 14:04:37 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			idx;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (!size)
		return (0);
	idx = 0;
	while (idx < size && (s1[idx] || s2[idx]))
	{
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		idx++;
	}
	return (0);
}
