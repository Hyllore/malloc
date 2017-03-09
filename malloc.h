/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 10:41:08 by droly             #+#    #+#             */
/*   Updated: 2017/03/09 17:27:06 by droly            ###   ########.fr       */
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
	int				size;
	int				isfree;
	void			*start;
	struct s_list	*next;
}					t_list;

/*typedef struct		s_struct
{
	void			*ptr;
	t_list			*list;
	t_list			*tmp;
}					t_struct;
*/
#endif
