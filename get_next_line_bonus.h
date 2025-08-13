/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Micampil <micampil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:00:20 by Micampil          #+#    #+#             */
/*   Updated: 2025/08/12 22:21:24 by Micampil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*get_next_line_cont(int fd, char *buffer, char *result, int bytes_read);
int		find_new_line(char *buff, int fd);
char	*ft_handle_new_line(char *buff, char *result, int i, int fd);
char	*ft_process_buffer(char *buff, int i, int fd);
char	*ft_rezise(char *result, int i, int *r);

#endif
