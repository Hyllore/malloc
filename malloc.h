/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 10:41:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/28 12:11:37 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
void	*add_new2(t_list *list, size_t size, t_list *tmp);
void	*add_new(t_list *list, t_list *tmp2, size_t size);
int		check_free(t_list *list, size_t size, t_list *tmp2);
t_list	*begin_new(t_list *list, int num,  size_t size, int type);
t_list	*check_size(t_list *list, size_t size);
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_putstr(char *str);
void	show_alloc_mem();
char	*ft_itoa_base_ull(unsigned long long value, int base);
size_t	ft_strlen(const char *s);

#endif
