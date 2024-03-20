/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/13 12:17:47 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
// #include <limits.h>

char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2, ssize_t bytes_read);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*get_line(char **buffer);
char	*read_file(char *buffer, ssize_t *bytes_read, int fd);
char	*truncate_buffer(char **buffer, size_t i);
char	*joining_to_buffer(char *buffer, int fd, ssize_t **bytes_read);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;
	ssize_t		bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(buffer, &bytes_read, fd);
	if (!buffer)
		return (0);
	result = get_line(&buffer);
	if (bytes_read == 0)
		buffer = NULL;
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
		if (buffer == NULL)
			return (NULL);
		ft_memcpy(buffer, read_buffer, *bytes_read);
	}
	while (!ft_strchr(buffer, '\n'))
	{
		buffer = joining_to_buffer(buffer, fd, &bytes_read);
		if (*bytes_read == 0)
			break ;
	}
	return (buffer);
}

char	*joining_to_buffer(char *buffer, int fd, ssize_t **bytes_read)
{
	char	read_buffer[BUFFER_SIZE];
	char	*temp_buffer;
	ssize_t	temp_buffer_len;

	**bytes_read = read(fd, read_buffer, BUFFER_SIZE);
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
	char	*res;
	size_t	len;
	ssize_t	i;

	res = NULL;
	i = -1;
	if (!ft_strchr(*buffer, '\n'))
		return (*buffer);
	else if (*buffer == NULL)
		return (NULL);
	else
	{
		len = ft_strlen(*buffer);
		res = (char *)malloc(len * sizeof(char));
		if (!res)
		{
			free (*buffer);
			return (NULL);
		}
		while (*buffer && (*buffer)[++i] != '\n')
			res[i] = (*buffer)[i];
		res[i] = (*buffer)[i];
		*buffer = truncate_buffer(buffer, i);
	}
	return (res);
}

char	*truncate_buffer(char **buffer, size_t i)
{
	char	*truncated_buffer;
	size_t	new_buffer_len;

	new_buffer_len = ft_strlen(&((*buffer)[i + 1]));
	if (new_buffer_len == 0)
	{
		free(*buffer);
		return (NULL);
	}
	if (new_buffer_len > 0)
	{
		truncated_buffer = (char *)malloc(new_buffer_len * sizeof(char));
		if (!truncated_buffer)
		{
			free(*buffer);
			return (NULL);
		}
		ft_memcpy(truncated_buffer, &((*buffer)[i + 1]), new_buffer_len);
		free(*buffer);
		return (truncated_buffer);
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
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
// /*
// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int	a1 = open("41_with_nl.txt", O_RDONLY);
// 	int	a2 = open("42_with_nl.txt", O_RDONLY);
// 	int	a3 = open("43_with_nl.txt", O_RDONLY);

// 	char *b;
// 	b = get_next_line(a1); printf("%s", b); free(b);
// 	b = get_next_line(a2); printf("%s", b); free(b);
// 	b = get_next_line(a3); printf("%s", b); free(b);
// 	b = get_next_line(a1); printf("%s", b); free(b);
// 	b = get_next_line(a2); printf("%s", b); free(b);
// 	b = get_next_line(a3); printf("%s", b); free(b);
	
// 	close(a1);
// 	close(a2);
// 	close(a3);
// }

// #include <fcntl.h>
// #include <stdio.h>
// int	main()
// {
// 	int	a = open("/Users/aleks/Desktop/42/get_next_line/alternate_line_nl_with_nl.txt", O_RDONLY);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		char *m = get_next_line(a);
// 		printf("%s", m);
// 	}
// }

// #include <fcntl.h>
// #include <stdio.h>
// int	main()
// {
// 	int	a = open("/Users/aleks/Desktop/42/get_next_line/alternate_line_nl_with_nl.txt", O_RDONLY);
// 	FILE *b = fopen("output.txt", "w+");
// 	char *c;

// 	// while ((c = get_next_line(a)) != NULL)
// 	// {
// 	// 	fprintf(b, "%s", c);
// 	// 	free(c);
// 	// }
	
// 	c = get_next_line(a);
// 	printf("1 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);
		
// 	c = get_next_line(a);
// 	printf("2 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);

// 	c = get_next_line(a);
// 	printf("3 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);
		
// 	c = get_next_line(a);
// 	printf("4 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);

// 	c = get_next_line(a); // 5
// 	printf("5 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);
		
// 	c = get_next_line(a);
// 	printf("6 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);

// 	c = get_next_line(a);
// 	printf("7 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);
		
// 	c = get_next_line(a);
// 	printf("8 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);

// 	c = get_next_line(a); // 9
// 	printf("9 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);
		
// 	c = get_next_line(a); // 10
// 	printf("10 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);

// 	c = get_next_line(a); // 11
// 	printf("11 call:\n%s", c);
// 	fprintf(b, "%s", c);
// 	free(c);

// 	fclose(b);
// 	close(a);
// }
