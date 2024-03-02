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
size_t	ft_strlen(const char *s);
//
void	add_to_buffer(char **buffer, char *temp_buffer, ssize_t *bytes_read, int fd);
int	new_line_check(char *temp_buffer, int bytes_read);

char	*print_line(char **buffer, char *temp_buffer, ssize_t bytes_read);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		temp_buffer[BUFFER_SIZE];
	char		*temp_buffer2;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || !fd || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	while (!new_line_check(temp_buffer, bytes_read) && bytes_read != 0)
		add_to_buffer(&buffer, temp_buffer, &bytes_read, fd);
	temp_buffer2 = print_line(&buffer, temp_buffer, bytes_read);
	return (temp_buffer2);
	// return ();

}

char	*print_line(char **buffer, char *temp_buffer, ssize_t bytes_read)
{
	char	*line;
	ssize_t	buffer_len;
	ssize_t	i;

	i = 0;
	while (temp_buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, temp_buffer, i + 1);
	buffer_len = ft_strlen(&(temp_buffer[i + 1]));
	if (!*buffer)
		{
			*buffer = (char *)malloc(buffer_len * sizeof(char));
		}
	ft_memcpy(*buffer, &(temp_buffer[i + 1]), buffer_len);
	return (line);
}

void	add_to_buffer(char **buffer, char *temp_buffer, ssize_t *bytes_read, int fd)
{
	char	*secondary_buffer;
	int		i;

	if (!*buffer)
	{
		*buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (!*buffer)
			return ;
		ft_memcpy(*buffer, temp_buffer, BUFFER_SIZE);
	}
	*bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	secondary_buffer = ft_strjoin(*buffer, temp_buffer);
	*buffer = (char *)malloc(ft_strlen(secondary_buffer) * sizeof(char));
	if (!*buffer)
			return ;
	ft_memcpy(*buffer, secondary_buffer, ft_strlen(secondary_buffer));
	free(secondary_buffer);
}

int	new_line_check(char *temp_buffer, int bytes_read)
{
	int	i;
	int	new_line;

	i = 0;
	while (i < bytes_read)
	{
		if (temp_buffer[i] == '\n')
			return(new_line = 1);
		i++;
	}
	return(new_line = 0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != 3)
		i++;
	return (i);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		join_i;
	int		source_i;
	int		len_s1;
	int		len_s2;
	char	*joined_str;

	join_i = 0;
	source_i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined_str = (char *)malloc(len_s1 + len_s2);
	if (!joined_str)
		return (NULL);
	while (join_i < len_s1)
	{
		joined_str[join_i++] = s1[source_i++];
	}
	source_i = 0;
	while (join_i < len_s1 + len_s2)
	{
		joined_str[join_i++] = s2[source_i++];
	}
	free((char *)s1);
	return (joined_str);
}

int	main()
{
	int	a = open("/Users/aleks/Desktop/42/get_next_line/1.txt", O_RDONLY);
	for (int i = 0; i < 3; i++)
	{
		char *m = get_next_line(a);
		printf("%s", m);
	}
	close(a);
}