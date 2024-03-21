/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:14 by aaleksee          #+#    #+#             */
/*   Updated: 2024/03/13 12:54:50 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*read_file(char *buffer, ssize_t *bytes_read, int fd);
char	*append_to_buffer(char *buffer, int fd, ssize_t **bytes_read);
char	*get_line(char **buffer, size_t *len);
char	*truncate_buffer(char *buffer, size_t i);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2, ssize_t bytes_read);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);

#endif
