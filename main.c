/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:21:29 by droly             #+#    #+#             */
/*   Updated: 2017/03/31 13:34:48 by droly            ###   ########.fr       */
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

/*int        main(void)
{
    int            i;
	int i2;
	char        *addr;
	size_t t;

	t = 2147483648;
	i2 = 0;
	i = 0;
	while (i < 1024)
	{
		ft_putstr("hey");
		addr = (char*)malloc(2147483606);
		ft_putchar('h');
		i2 = 0;
		if (addr == NULL)
			return (0);
//		while (i2 < 1024)
//		{
//			ft_putstr("yo");
//			addr[i2] = 42;
//			printf("%c", addr[i2]);
//			i2++;
//		}
//		free(addr);
		i++;
	}
	realloc(addr, 1000000000000000000);
//	realloc(addr, 100);
	realloc(addr, 500);
	show_alloc_mem();
//	printf("hey");
	ft_putnbr(t);
	return (0);
}*/
//getrlimit voir pour gerer les erreurs, et trouver pk ca segfault comme un fils de pute de sa mere la tinp


int				main(void)
{
	int			*str;
	int			*ptr;
	int			i;
	t_list		*tmp;

	i = 0;
	printf("\nlu %lu\n", (sizeof(t_list)));
//	if ((*str = ft_malloc(sizeof(int) * 8)) == NULL)
//		printf("\nnull\n");
	printf("\nlu %lu\n", (sizeof(t_list)));
//	printf("ext %p\n", *str);
//segfault si trop gros chiffre
//	str = ft_malloc(sizeof(int) * 8);
///	str = ft_malloc(sizeof(int) * 25);
//	str = ft_malloc(sizeof(int) * 100);
//	str = ft_malloc(sizeof(int) * 1000);
//	str = ft_malloc(sizeof(int) * 10000);
//	str = ft_malloc(sizeof(int) * 20000);
//	str = ft_malloc(sizeof(int) * 1000000);
//	str = ft_malloc(sizeof(int) * 20000);
//	str = ft_malloc(sizeof(int) * 10000);
//	str = ft_malloc(sizeof(int) * 1000);
//	str = ft_malloc(sizeof(int) * 100);
//	str = ft_malloc(sizeof(int) * 2);
	int y;

	y = 0;
//	while (i < 3)
//	{
//		printf("\nnb : %d\n", i);
		str = malloc(16 * 10 * 10);
		printf("\nadresse str %p\n", str);
		printf("\nnb : %d\n", i);
		tmp = list;
		free(str);
		ptr = malloc(120 * 10 * 10);
		printf("\nadresse ptr %p\n", ptr);
//		ft_free(str);
//	y = 0;
///		while (y < 20)
//		{
//			str[y] = 1;
///			printf("\nchiffre : %d\n", str[y]);
//			y++;
//		}
//		i++;
//	}
	i = 0;
//	while (i < 69536)
//	{
//		list->start++;
//		i++;
//	}
//		printf("\nadresses fin %p\n", list->start++);
	i = 0;
	//trouver pourquoi segfault si 655 et si plus de 100 appel
//	free(ptr);
//	free(str);
//		printf("\nnb : %d\n", i);
		str = malloc(250);
		printf("\nadresse str %p\n", str);
		ptr = malloc(1);
		printf("\nadresse ptr %p\n", ptr);
free(ptr);
			str = malloc(2);
		printf("\nadresse str %p\n", str);
free(str);
		str = malloc(3);
		printf("\nadresse str %p\n", str);
free(str);
		str = malloc(4);
		printf("\nadresse str %p\n", str);
free(str);
	str = malloc(5);
		printf("\nadresse str %p\n", str);
free(str);
		str = malloc(6);
		printf("\nadresse str %p\n", str);
free(str);
	str = malloc(7);
		printf("\nadresse str %p\n", str);
free(str);
		str = malloc(8);
		printf("\nadresse str %p\n", str);
free(str);
			str = malloc(9);
		printf("\nadresse str %p\n", str);
free(str);
		str = malloc(10);
		printf("\nadresse str %p\n", str);
free(str);
		str = malloc(9000);
		printf("\nadresse str %p\n", str);
		ptr = malloc(9005);
		printf("\nadresse ptr %p\n", ptr);
		ptr = realloc(ptr, 8000);
		str = realloc(str, 8500);
//		ft_malloc(8000);
//		ft_free(ptr);
//		str = ft_malloc(10);
//		printf("\nadresse str %p\n", str);
//		printf("\nadresse ptr %p\n", ptr);
	list = tmp;
	while (list != NULL)
	{
		printf("\nadresse %p\n", list);
//		i = 0;
//		while (i++ < 56)
//			printf("\nadresse %p\n", list->start--);
		printf("\nlist sortie %p\n", list->start);
		printf("\nlist free %d\n", list->isfree);
		i++;
//		while (i < 32)
//		{
//			printf(" %p\n", list->start++);
//			i++;
//		}
		printf("type %d\n", list->type);
		printf("floor %d\n", list->floor);
		printf("size %lu\n", list->size);
//		if (list->next != NULL)
			list = list->next;
//		else
//			break;
	}
	list = tmp;
	i = 0;
//	while (i < 36)
//	{
//		printf("\nadresses dispos %p\n", list->start++);
//		i++;
//	}
	printf("\nnobre de tours : %d\n", i);
	printf("\nsize get page 16 / 100 : %d\n", 16 * getpagesize() / 100);
	printf("\nsize get page 4 / 100  : %d\n", 4 * getpagesize()/ 100);
	printf("\nsize get page 16  : %d\n", 16 * getpagesize());
	printf("\nsize get page 4  : %d\n", 4 * getpagesize());
	printf("\nsize get page 16 + sizeof(t_list) * 100 : %lu\n", 16 * getpagesize() +sizeof(t_list) * 100 );
	printf("\nsize get page 4 + sizeof(t_list) * 100  : %lu\n", 4 * getpagesize() +sizeof(t_list) * 100 );
//	str = malloc(sizeof(int) * 2);
//	str[0] = 544;
//	str[1] = 5454;
//	str[2] = 64584;
//	printf("%d%d%d", str[0], str[1], str[2]);
//	str = malloc(8);
//	list = tmp;;
//	ft_free(str);
//	list = tmp;
	//trouver pourquoi c tjr la premiere adresse qui free
}
