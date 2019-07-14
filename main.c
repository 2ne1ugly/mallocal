/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:11:21 by mchi              #+#    #+#             */
/*   Updated: 2019/04/25 12:29:23 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "malloc.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define COUNT 2

//test realloc.
int main(void)
{
	int *a;
	int *b;
	int *c;
	a = malloc(1);
	b = malloc(9);
	c = malloc(1);
	free(b);
	b = malloc(1);
	return (0);
}
