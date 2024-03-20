/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/23 03:15:15 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*result;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = read_file(buffer[fd], &bytes_read, fd);
	if (!buffer[fd])
		return (NULL);
	result = get_line(&buffer[fd]);
	if (bytes_read == 0)
		buffer[fd] = NULL;
	return (result);
}

char	*read_file(char *buffer, ssize_t *bytes_read, int fd)
{
	char	read_buffer[BUFFER_SIZE];

	if (!buffer)
	{
		*bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (*bytes_read == 0)
			return (NULL);
		buffer = (char *)malloc(*bytes_read * sizeof(char));
		if (!buffer)
			return (NULL);
		ft_memcpy(buffer, read_buffer, *bytes_read);
	}
	while (!ft_strchr(buffer, '\n'))
	{
		buffer = append_to_buffer(buffer, fd, &bytes_read);
		if (*bytes_read == 0)
			break ;
	}
	return (buffer);
}

char	*append_to_buffer(char *buffer, int fd, ssize_t **bytes_read)
{
	char	read_buffer[BUFFER_SIZE];
	char	*temp_buffer;
	ssize_t	temp_buffer_len;

	**bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (**bytes_read == 0)
		return (buffer);
	temp_buffer = ft_strjoin(buffer, read_buffer, **bytes_read);
	if (!temp_buffer)
	{
		free(buffer);
		return (NULL);
	}
	temp_buffer_len = ft_strlen(temp_buffer);
	free(buffer);
	buffer = (char *)malloc((temp_buffer_len + 1) * sizeof(char));
	if (!buffer)
	{
		free(temp_buffer);
		return (NULL);
	}
	ft_memcpy(buffer, temp_buffer, temp_buffer_len + 1);
	free(temp_buffer);
	return (buffer);
}

char	*get_line(char **buffer)
{
	char	*newline;
	char	*res;
	size_t	len;

	newline = ft_strchr(*buffer, '\n');
	res = NULL;
	if (!newline)
		return (*buffer);
	len = newline - *buffer;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
	{
		free (*buffer);
		return (NULL);
	}
	ft_memcpy(res, *buffer, len + 1);
	*buffer = truncate_buffer(buffer, len + 1);
	return (res);
}

char	*truncate_buffer(char **buffer, size_t i)
{
	char	*truncated_buffer;
	size_t	new_buffer_len;

	new_buffer_len = ft_strlen(&((*buffer)[i]));
	if (new_buffer_len == 0)
		free(*buffer);
	if (new_buffer_len > 0)
	{
		truncated_buffer = (char *)malloc(new_buffer_len * sizeof(char));
		if (!truncated_buffer)
		{
			free(*buffer);
			return (NULL);
		}
		ft_memcpy(truncated_buffer, &((*buffer)[i]), new_buffer_len);
		free(*buffer);
		return (truncated_buffer);
	}
	return (NULL);
}
/*
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int	a1 = open("41_with_nl.txt", O_RDONLY);
	int	a2 = open("42_with_nl.txt", O_RDONLY);
	int	a3 = open("43_with_nl.txt", O_RDONLY);

	char *b;
	b = get_next_line(a1); printf("%s", b); free(b);
	b = get_next_line(a2); printf("%s", b); free(b);
	b = get_next_line(a3); printf("%s", b); free(b);
	b = get_next_line(a1); printf("%s", b); free(b);
	b = get_next_line(a2); printf("%s", b); free(b);
	b = get_next_line(a3); printf("%s", b); free(b);
	
	close(a1);
	close(a2);
	close(a3);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int	a = open("/Users/aleks/Desktop/42
	/get_next_line/alternate_line_nl_with_nl.txt", O_RDONLY);
	for (int i = 0; i < 10; i++)
	{
		char *m = get_next_line(a);
		free(m);
		printf("%s", m);
	}
	close(a);
}

#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int	a = open("/Users/aleks/Desktop/42
	/get_next_line/alternate_line_nl_with_nl.txt", O_RDONLY);
	FILE *b = fopen("output.txt", "r");
	
	char *c;
	while ((c = get_next_line(a)) != NULL)
	{
		fprintf(b, "%s", c);
		free(c);
	}
	fclose(b);
	close(a);
}
*/
