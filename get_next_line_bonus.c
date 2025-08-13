/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Micampil <micampil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:00:20 by Micampil          #+#    #+#             */
/*   Updated: 2025/08/12 20:30:38 by Micampil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*result;
	int			bytes_read;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	result = NULL;
	bytes_read = 1;
	if (!buffer[fd][0])
		bytes_read = -2;
	return (get_next_line_cont(fd, (char *)buffer, result, bytes_read));
}

// int	main(int argc, char **argv)
// {
// 	int fd;
// 	int second_fd;
// 	char *result;
// 	char *second_result;
// 	int i;

// 	i = 1;
// 	if (argc > 1)
// 	{
// 		fd = open(argv[1], O_RDONLY);
// 		second_fd = open(argv[2], O_RDONLY);
// 		result = get_next_line(fd);
// 		second_result = get_next_line(second_fd);
// 		while (result != NULL || second_result != NULL)
// 		{
// 			printf("\n\tcall #%d (first fd): %s", i, result);
// 			printf("\n\tcall #%d (second fd): %s", i, second_result);
// 			free(result);
// 			free(second_result);
// 			result = get_next_line(fd);
// 			second_result = get_next_line(second_fd);
// 			i++;
// 		}
// 		free(result);
// 		free(second_result);
// 		if (fd != -1)
// 			close(fd);
// 		if (second_fd != -1)
// 			close(second_fd);
// 	}
// }
