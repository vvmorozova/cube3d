/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:50:16 by eward             #+#    #+#             */
/*   Updated: 2022/01/10 12:50:18 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"

unsigned long	ft_strlen(const char *s);
char			*get_next_line(int fd);
char			*get_next_line(int fd);
char			*ft_crop_line(char *rest);
char			*ft_read_line(int fd, char *rest);
char			*ft_new_rez(char *rest);
#endif
