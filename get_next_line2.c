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
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*read_line(int fd);
size_t	new_lines_check(char *line);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*get_full_line(char **result, int fd);
char	*return_new_line(char **result, size_t *new_lines_counter);

char	*get_next_line(int fd)
{
	static char 	*result; // Here we accumulate the result of function, either it will be one line or several depending on buffer size
	static size_t	call_counter; // A counter for cases when we've got several lines and repeadted calls
	static size_t	new_lines_counter;

	if (new_lines_counter == 0)
		result = read_line(fd);
	new_lines_counter = new_lines_check(result);
	// printf("\nres: %s \n", result);
	if (result == NULL)
		return (NULL);
	if (new_lines_check(result) == 0)
		return (get_full_line(&result, fd));
	while (call_counter < new_lines_counter)
		{
			call_counter++;
			return(return_new_line(&result, &new_lines_counter));
		}
	return (result);
}

char	*return_new_line(char **result, size_t *new_lines_counter)
{
	char			*new_line_result;
	static size_t	i;
	size_t			j;

	*new_lines_counter = new_lines_check(*result);
	j = 0;
	if (*new_lines_counter != 0)
		i = 0;
	while ((*result)[i] != '\n' && new_lines_counter > 0)
	{
		if ((*result)[i] == '\n')
			(*new_lines_counter)--;
		i++;
	}
	new_line_result = (char *)malloc((i + 1) * sizeof(char));
	i -= i;
	while ((*result)[i] != '\n')
	{
		new_line_result[j] = (*result)[i];
		j++;
		i++;
	}
	new_line_result[j] = '\n';
	i++;
	return (new_line_result);
}

char	*get_full_line(char **result, int fd)
{
	char	*new_result;
	char	*temp_result;

	while (new_lines_check(*result) == 0)
	{
		temp_result = read_line(fd);
		if (temp_result == NULL)
		{
			free(temp_result);
			return (*result);
		}
		new_result = ft_strjoin(*result, temp_result);
		*result = (char *)malloc(ft_strlen(new_result) * sizeof(char));
		if (!*result)
			return (NULL);
		ft_memcpy(*result, new_result, ft_strlen(new_result));
		free(new_result);
	}
	// if (new_lines_check(result) > 0)
	// {
	// 	temp_result = read_line(fd);
	// 	new_result = ft_strjoin(result, temp_result);
	// 	result = (char *)malloc(ft_strlen(new_result) * sizeof(char));
	// 	if (!result)
	// 		return (NULL);
	// 	ft_memcpy(result, new_result, ft_strlen(new_result));
	// 	free(new_result);
	// }
	return (*result);
}
char	*read_line(int fd)
{
	int		fd_response;
	char	*result;

	result = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!result)
		return (NULL);
	fd_response = read(fd, result, BUFFER_SIZE);
	if (fd_response < 0)
	{
		free(result);
		return (NULL);
	}
	// if (fd_response < BUFFER_SIZE)
	// 	return (result);
	if (fd_response == 0)
		return(NULL);
	return (result);
}

size_t	new_lines_check(char *line)
{
	size_t	i;
	size_t	new_lines;
	size_t	len;

	i = 0;
	new_lines = 0;
	len = ft_strlen(line);
	if (!line)
		return(0);
	while (i < len)
	{
		if (line[i] == '\n')
			new_lines++;
		i++;
	}
	return (new_lines);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
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
	free((char *)s2);
	return (joined_str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	copy_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	copy_len = dstsize - 1;
	if (copy_len > src_len)
		copy_len = src_len;
	ft_memcpy(dst, src, copy_len);
	dst[copy_len] = '\0';
	return (src_len);
}
/* 
int	main()
{
	int	a = open("/Users/aleks/Desktop/42/get_next_line/1.txt", O_RDONLY);
	for (int i = 0; i < 2; i++)
	{
		char *m = get_next_line(a);
		printf("%s", m);
		free(m);
	}
	// char *m = get_next_line(a);
	// printf("%s", m);
	// free(m);
	close(a);
	// printf("%s", m);
}
*/