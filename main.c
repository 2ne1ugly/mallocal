/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchi <mchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:11:51 by mchi              #+#    #+#             */
/*   Updated: 2019/07/23 15:12:25 by mchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"
// #include "malloc_int.h"

// #include <stdlib.h>

#include <stdio.h>

int main () 
{ 
malloc (1024); 
malloc (1024 * 32); 
malloc (1024 * 1024); 
malloc (1024 * 1024 * 16); 
malloc (1024 * 1024 * 128); 
show_alloc_mem (); 
return (0); 
}