/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleksee <aaleksee@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:15:22 by aaleksee          #+#    #+#             */
/*   Updated: 2024/02/23 03:15:24 by aaleksee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#endif
#include <stdlib.h>

char *get_next_line(int fd);

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 9
#endif