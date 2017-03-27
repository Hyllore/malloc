/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:21:29 by droly             #+#    #+#             */
/*   Updated: 2017/03/27 17:41:04 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"

#define M1 (1024 * 1024 )

void        print(char *s)
{
	    write(1, s, strlen(s));
}

int            main(void)
{
	char tmp[10];
malloc(1024);
    malloc(1024 * 32);
	    malloc(1024 * 1024);
		    malloc(1024 * 1024 * 16);
			    malloc(1024 * 1024 * 128);
				    print("\n---------show_alloc_mem()------------\n");
					    show_alloc_mem();
						    print(&tmp[0]);
//							    show_alloc_mem_ex();
								    return (0);
}
