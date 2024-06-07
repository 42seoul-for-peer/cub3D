/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:19:12 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/13 13:57:19 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int val)
{
	int		len;

	val %= 256;
	len = ft_strlen(str);
	if (!val)
		return ((char *)str + len);
	len -= 1;
	while (len > -1)
	{
		if (str[len] == val)
			return ((char *)str + len);
		else
			len--;
	}
	return (NULL);
}
