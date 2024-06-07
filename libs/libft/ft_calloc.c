/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:43:11 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/11/18 14:23:28 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*temp;
	size_t	len;
	size_t	max;

	max = ~0;
	if (count && (max / count < size))
		return (NULL);
	len = count * size;
	temp = malloc(len);
	if (!temp)
		return (NULL);
	temp = ft_memset(temp, 0, len);
	return (temp);
}
