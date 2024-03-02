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

//
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);
//

char    *get_next_line(int fd)
{
    static char     buffer[BUFFER_SIZE];
    static size_t   buffer_size;
    ssize_t         bytes_read;
    size_t          i;
    char            *line;

    buffer_size = BUFFER_SIZE;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (buffer[buffer_size - 1] != '\n') 
    {
        bytes_read = read(fd, buffer, buffer_size);
        if (bytes_read == 0)
            break ;
        if (bytes_read < 0)
            return (NULL);
        buffer_size += bytes_read;
    }
    for (i = 0; i < buffer_size; i++) 
    {
        if (buffer[i] == '\n') 
        {
            line = (char *)malloc(i + 1);
            if (!line)
                return (NULL);
            ft_memcpy(line, buffer, i);
            line[i] = '\n';
            buffer_size -= (i + 1);
            ft_memmove(buffer, buffer + i + 1, buffer_size);
            return (line);
        }
    }
    line = (char *)malloc(buffer_size + 1);
    if (!line)
        return (NULL);
    ft_memcpy(line, buffer, buffer_size);
    line[buffer_size] = '\n';
    buffer_size = 0;
    return (line);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_data;
	char	*src_data;

	if (!dst && !src)
		return (dst);
	i = 0;
	dst_data = (char *)dst;
	src_data = (char *)src;
	while (i < n)
	{
		dst_data[i] = src_data[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_temp;
	const char	*src_temp;

	dst_temp = (char *)dst;
	src_temp = (const char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst <= src || dst >= src + len)
		while (len--)
			*dst_temp++ = *src_temp++;
	else
	{
		dst_temp += len - 1;
		src_temp += len - 1;
		while (len--)
			*dst_temp-- = *src_temp--;
	}
	return (dst);
}

int	main()
{
	int	a = open("/Users/aleks/Desktop/42/get_next_line/1.txt", O_RDONLY);
	for (int i = 0; i < 2; i++)
	{
		char *m = get_next_line(a);
		printf("%s", m);
		free(m);
	}
	close(a);
}