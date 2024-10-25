/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droura-s <droura-s@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:49:07 by droura-s          #+#    #+#             */
/*   Updated: 2024/10/10 10:49:33 by droura-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_jump(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '\n')
			return (i);
		i++;
	}
	if (ptr[i] == '\n')
		return (i);
	return (-1);
}

char	*ft_calloc_bzero(size_t nmemb, size_t size)
{
	char	*array;

	array = malloc(nmemb * size);
	if (!array)
		return (array);
	array[(nmemb * size) - 1] = '\0';
	return (array);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	idx;
	size_t	s_len;
	size_t	size;
	char	*substr;

	idx = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		size = 1;
	else if ((s_len - start + 1) <= len)
		size = s_len - start + 1;
	else
		size = len + 1;
	substr = ft_calloc_bzero(size, sizeof(char));
	if (!substr)
		return (substr);
	while (s[idx] != '\0' && (idx + start) < s_len && idx < len)
	{
		substr[idx] = s[idx + start];
		idx++;
	}
	substr[idx] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	size_t	s1_len;
	size_t	s2_len;
	size_t	idx;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strjoin = ft_calloc_bzero(s1_len + s2_len + 1, sizeof(char));
	if (!strjoin)
		return (0);
	idx = 0;
	while (idx < s1_len + s2_len)
	{
		if (idx < s1_len)
			strjoin[idx] = s1[idx];
		else
			strjoin[idx] = s2[idx - s1_len];
		idx++;
	}
	return (strjoin);
}
