/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:11:51 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 00:35:11 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"
// #include "malloc_int.h"

// #include <stdlib.h>

#include <stdio.h>

int main () 
{ 
int i; 
char * addr; 

i = 0; 
while (i <1024) 
{ 
addr = (char *) malloc (1024); 
addr [0] = 42; 
//free (addr); 
i ++; 
} 
return (0); 
} 