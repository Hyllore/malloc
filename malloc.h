/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 10:41:08 by droly             #+#    #+#             */
/*   Updated: 2017/04/27 11:43:12 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <string.h>

typedef struct		s_list
{
	unsigned long	size;
	int				isfree;
	int				floor;
	int				type;
	void			*start;
	struct s_list	*next;
}					t_list;

t_list	*list;


t_list	*split_mem(size_t size, t_list *list, int num);
void	*add_new2(t_list *list, size_t size, t_list *tmp, t_list *tmp2);
void	*add_new(t_list *list, int page, size_t size, void *tmp);
int		check_free(t_list *list, size_t size, t_list *tmp2, int page);
t_list	*begin_new(t_list *list, int num,  size_t size, int type);
t_list	*check_size(t_list *list, size_t size, int page);
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_putstr(char *str);
void	show_alloc_mem();
char	*ft_itoa_base_ull(unsigned long long value, int base);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*calloc(size_t count, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);


void	showadd(void *str);

#endif
