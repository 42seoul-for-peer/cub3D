/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:52:09 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/26 22:05:00 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	size_t	idx;
	size_t	len_n;

	if (!*needle || !needle)
		return ((char *)haystack);
	if (!*haystack || !haystack)
		return (NULL);
	idx = 0;
	len_n = ft_strlen(needle);
	while (idx + len_n <= size && haystack[idx])
	{
		if (!ft_strncmp(haystack + idx, needle, len_n))
			return ((char *)haystack + idx);
		idx++;
	}
	return (NULL);
}
