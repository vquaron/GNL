/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/23 03:15:15 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i] != '\0')
		;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	tmp = (char *)s;
	while (tmp[++i] != '\0')
	{
		if (tmp[i] == (char)c)
			return (&tmp[i]);
	}
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_data;
	char	*src_data;

	i = -1;
	if (!dst && !src)
		return (dst);
	dst_data = (char *)dst;
	src_data = (char *)src;
	while (++i < n)
		dst_data[i] = src_data[i];
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2, ssize_t bytes_read)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*joined_str;

	i = -1;
	len_s1 = ft_strlen(s1);
	len_s2 = bytes_read;
	joined_str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined_str)
		return (NULL);
	ft_memcpy(joined_str, s1, len_s1);
	while (++i < len_s2)
		joined_str[len_s1 + i] = s2[i];
	joined_str[len_s1 + len_s2] = '\0';
	return (joined_str);
}
