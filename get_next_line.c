/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alazarev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:48:27 by alazarev          #+#    #+#             */
/*   Updated: 2018/04/04 21:22:00 by alazarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/includes/libft.h"
#include <stdio.h>

static char		*ft_read(const int fd)
{
	char		*str;
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			ret;

	str = NULL;
	if (!(temp = ft_strnew(0)))
		return (0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin(temp, buf);
		free(temp);
		temp = str;
	}
	return (str);
}

t_list	*ft_find(t_list *storage, size_t fd)
{
	while (storage)
	{
		if (storage->content_size == fd)
			return (storage);
		storage = storage->next;
	}
	return (NULL);
}

t_list	*ft_create(void const *content, size_t content_size)
{
	t_list	*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		return (0);
	node->content = (void*)content;
	node->content_size = content_size;
	node->next = NULL;
	return (node);
}

int		line_fill(t_list **node, char **line)
{
	int		i;
	int		len;
	char	*t;
	char	*buf;
	t = ft_strchr((char*)((*node)->content), '\n');
	if (t)
		len = t - (char*)(*node)->content;
	else
		len = ft_strlen((char*)(*node)->content);
		
	if (!(*line = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = -1;
	while (++i < len)
		(*line)[i] = ((char*)((*node)->content))[i];
	(*line)[i] = '\0';
	if (((char*)((*node)->content))[i])
	{
		buf = ft_strdup(((char*)((*node)->content)) + i + 1);
		free(((*node)->content));
		(*node)->content = (void*)buf;
	}
	else
		ft_memdel(&(((*node)->content)));
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*storage = NULL;
	t_list			*node;

	if (!line || read(fd, 0, 0) < 0 || fd > 7999)
		return (-1);
	if (!storage)
		storage = ft_create((void*)ft_read(fd), fd);
	node = ft_find(storage, fd);
	if (!node)
	{
		node = ft_create((void*)ft_read(fd), fd);
		ft_lstadd(&storage, node);
	}
	else if (node->content == NULL || (*(char*)node->content) == '\0')
		return (0);
	if (!(line_fill(&node, line)))
		return (-1);
	return (1);
}