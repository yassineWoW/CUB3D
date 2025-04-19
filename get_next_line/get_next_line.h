/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainouni <ainouni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:39:34 by ainouni           #+#    #+#             */
/*   Updated: 2025/03/14 21:39:35 by ainouni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 20

char	*ft_strchr2(char *s, int c);
size_t	len_str(const char *s);
char	*ft_strcpy(char *str, char *src);
char	*ft_strjoin2(char *s1, char const *s2);
char	*prepare_line(char *buff);
char	*save_next_line(char *buff);
char	*get_next_line(int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif