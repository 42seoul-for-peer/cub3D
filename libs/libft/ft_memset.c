/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:24:41 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/08 21:07:29 by hyeunkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int val, size_t size)
{
	size_t	idx;
	char	*temp;

	idx = 0;
	temp = (char *)dst;
	while (idx < size)
	{
		temp[idx] = (char)val;
		idx++;
	}
	return (dst);
}
