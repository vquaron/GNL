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
char	*get_full_line(int fd, char **current_res, int bytes_read);
char	*print_line(char **current_res, int bytes_read);
char	*get_line(char ***current_res, int bytes_read, int n_index);
int	eof_check(char *res);
size_t	ft_strlen(const char *s);
//

char	*get_next_line(int fd)
{
	static char	*current_res;
	int			bytes_read;

	if (BUFFER_SIZE <= 0 || !fd || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	current_res = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!current_res)
		return (NULL);
	bytes_read = read(fd, current_res, BUFFER_SIZE); // 8
	if (!print_line(&current_res, bytes_read))
		return (get_full_line(fd, &current_res, bytes_read));
	return (current_res);

}

char	*print_line(char **current_res, int bytes_read)
{
	char	*line;
	int		i;

	i = 0;
	while (i < bytes_read)
	{
		if ((*current_res)[i] == '\n')
				return (get_line(&current_res, bytes_read, i));
		i++;
	}
	return (NULL);
}

char	*get_full_line(int fd, char **current_res, int bytes_read)
{
	char	*line;
	char	*temp_line;
	int		i;

	i = 0;
	while (eof_check(*current_res) == 0)
	{
		line = (char *)malloc(BUFFER_SIZE * sizeof(char));
		read(fd, line, BUFFER_SIZE);
		temp_line = ft_strjoin(*current_res, line);
		*current_res = (char *)malloc(ft_strlen(temp_line) * sizeof(char));
		if (!*current_res)
			return (NULL);
		ft_memcpy(*current_res, temp_line, ft_strlen(temp_line));
		free(temp_line);
		i++;
	}
	return (line);
}

int	eof_check(char *res)
{
	int	i;
	int	len;
	int	new_line;

	i = 0;
	len = ft_strlen(res);
	new_line = 0;
	while (i < len)
	{
		if (res[i] == '\n')
			new_line++;
		i++;
	}
	return (new_line);
}

char	*get_line(char ***current_res, int bytes_read, int n_index)
{
	char	*line;
	char	*temp_current_res;
	int		current_res_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = (char *)malloc((n_index + 1) * sizeof(char));
	while (i <= n_index)
	{
		line[i] = (**current_res)[j];
		i++;
		j++;
	}
	i = 0;
	current_res_len = ft_strlen(**current_res);
	temp_current_res = (char *)malloc((current_res_len - n_index) * sizeof(char));
	if (!temp_current_res)
		return (NULL);
	while (i < current_res_len - n_index)
	{
		temp_current_res[i] = (**current_res)[j];
		i++;
		j++;
	}
	free(**current_res);
	**current_res = (char *)malloc((current_res_len - n_index) * sizeof(char));
	if (!**current_res)
		return (NULL);
	ft_memcpy(**current_res, temp_current_res, current_res_len - n_index - 1);
	return(line);
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