/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:21:29 by droly             #+#    #+#             */
/*   Updated: 2017/03/28 17:12:04 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "string.h"
#include "unistd.h"
#include "stdlib.h"

/*#define M1 (1024 * 1024 )

void        print(char *s)
{
	    write(1, s, strlen(s));
}

int            main(void)
{
	char tmp[10];
malloc(10);
malloc(250);
malloc(500);

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
}*/

int        main(void)
{
    int            i;
	int i2;
	char        *addr;

	i2 = 0;
	i = 0;
	while (i < 1024)
	{
//		ft_putstr("hey");
		addr = (char*)malloc(1024);
		i2 = 0;
		while (i2 < 1024)
		{
//			ft_putstr("yo");
			addr[i2] = 42;
			printf("%c", addr[i2]);
			i2++;
		}
//		free(addr);
		i++;
	}
	realloc(addr, 2);
//	show_alloc_mem();
//	printf("hey");
	return (0);
}
//getrlimit voir pour gerer les erreurs, et trouver pk ca segfault comme un fils de pute de sa mere la tinp
