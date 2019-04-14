/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:11:21 by mchi              #+#    #+#             */
/*   Updated: 2019/04/13 16:58:26 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define COUNT 2

//fails from free.x
int main(void)
{
	char *str[COUNT];
	int i;

	i = 0;
	while (i < COUNT)
	{
		str[i] = malloc(1);
		if (str[i] == NULL)
			printf("malloc fail: %d \n", i);
		printf("malloc: %d\n", i);
		i++;
	}
	i = 0;
	while (i < COUNT)
	{
		free(str[i]);
		printf("free: %d\n", i);
		i++;
	}

	return (0);
}
