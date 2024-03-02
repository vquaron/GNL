/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/23 03:15:15 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

size_t	ft_strend(char *line);
char	*ft_get_line(int fd, char **result);
char	*ft_line_check(int fd, char *read_res);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

char	*get_next_line(int fd)
{
	char 	*result;
	static size_t	i;

	ft_get_line(fd, &result);

	return (result);
}

char	*ft_get_line(int fd, char **result)
{
	char 	*read_result;
	int		read_check;
	size_t	i;


	read_result = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!read_result)
		return (NULL);
	read_check = read(fd, (char *)read_result, BUFFER_SIZE);
	if (read_check < 0)
		return (NULL);

	ft_line_check(fd, read_result);
	printf("%s", read_result);
}

char	*ft_line_check(int fd, char *read_res)
{
	if (ft_strend(read_res) == 1)
		return (read_res);
	return (ft_get_line(fd, &read_res));
}

size_t	ft_strend(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
		{
			if (line[i] == '\n')
				return (1);
			i++;
		}
	return (0);
}

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	src_len;
// 	size_t	copy_len;

// 	src_len = ft_strlen(src);
// 	if (dstsize == 0)
// 		return (src_len);
// 	copy_len = dstsize - 1;
// 	if (copy_len > src_len)
// 		copy_len = src_len;
// 	ft_memcpy(dst, src, copy_len);
// 	dst[copy_len] = '\0';
// 	return (src_len);
// }

int	main()
{
	int	a = open("/Users/aleks/Desktop/42/get_next_line/1.txt", O_RDONLY);
	char *m = get_next_line(a);
	close(a);
	// printf("%s", m);
}