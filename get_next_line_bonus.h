/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Micampil <micampil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:00:20 by Micampil          #+#    #+#             */
/*   Updated: 2025/06/15 18:09:58 by Micampil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

// Main function
char	*get_next_line(int fd);

// Helper functions
char	*read_buffer(int fd, char *storage);
char	*ft_extract_line(char *storage);
char	*ft_update_storage(char *storage);
char	*ft_join_and_free(char *storage, char *buffer);

// Utility functions
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *string, int to_find);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif