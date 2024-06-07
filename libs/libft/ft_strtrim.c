/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:26:59 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/19 17:03:05 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strltrim(char const *s1, char const *set)
{
	size_t	idx;
	char	*result;

	idx = 0;
	if (!s1)
		return (NULL);
	while (s1[idx] && ft_strchr(set, s1[idx]))
		idx++;
	result = ft_strdup(&s1[idx]);
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_strrtrim(char const *s1, char const *set)
{
	size_t	idx;
	char	*result;

	if (!s1)
		return (NULL);
	if (!*s1)
		idx = 0;
	else
		idx = ft_strlen(s1) - 1;
	while (s1[idx] && ft_strchr(set, s1[idx]))
		idx--;
	result = ft_calloc(idx + 2, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, idx + 2);
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*lresult;
	char	*rresult;

	lresult = ft_strltrim(s1, set);
	if (!lresult)
		return (0);
	rresult = ft_strrtrim(lresult, set);
	free(lresult);
	return (rresult);
}
