/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:34:12 by hyeunkim          #+#    #+#             */
/*   Updated: 2024/02/19 15:28:40 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *str, char c)
{
	size_t	idx;
	size_t	len;
	size_t	word_cnt;

	idx = 0;
	word_cnt = 0;
	len = ft_strlen(str);
	while (idx < len)
	{
		if (str[idx] != c)
			if (idx == 0 || str[idx - 1] == c)
				word_cnt++;
		idx++;
	}
	return (word_cnt);
}

static char	*str_to_word(char *str, char c)
{
	char	*word;
	size_t	len;
	size_t	idx;

	if (ft_strchr(str, c))
		len = ft_strchr(str, c) - str;
	else
		len = ft_strlen(str);
	idx = 0;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (idx < len)
	{
		word[idx] = str[idx];
		idx++;
	}
	return (word);
}

static char	**return_free(char **str, size_t size)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		free(str[idx]);
		idx++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	size_t	idx;
	size_t	word_cnt;
	char	**result;

	word_cnt = count_word(str, c);
	result = ft_calloc(word_cnt + 1, sizeof(char *));
	if (!result)
		return (NULL);
	idx = 0;
	while (idx < word_cnt)
	{
		if (*str != c)
		{
			result[idx] = str_to_word((char *)str, c);
			if (!result[idx])
				return (return_free(result, idx));
			str += ft_strlen(result[idx]);
			idx++;
		}
		else
			str++;
	}
	return (result);
}
