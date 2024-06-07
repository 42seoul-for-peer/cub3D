/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:21:33 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/11/17 21:29:04 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	int		len;
	int		idx;

	if (!str)
		str = str + 1;
	len = ft_strlen(str);
	result = ft_calloc(1, len + 1);
	if (!result)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		result[idx] = str[idx];
		idx++;
	}
	return (result);
}
