/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 04:18:58 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/11/18 15:30:25 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t max_len)
{
	char	*sub_str;
	size_t	str_len;

	str_len = ft_strlen(str);
	if (max_len > str_len)
		max_len = str_len;
	if (start + max_len > str_len)
		max_len = str_len - start;
	if (!str || start > str_len)
		return ((char *)ft_calloc(1, 1));
	sub_str = ft_calloc(max_len + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, (char *)(str + start), max_len + 1);
	return (sub_str);
}
