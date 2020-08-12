/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:19:41 by angonyam          #+#    #+#             */
/*   Updated: 2018/08/26 10:38:55 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include <unistd.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if ((int)n < 0)
		;
	else
	{
		i = 0;
		while (i < n)
		{
			((char*)s)[i] = '\0';
			i++;
		}
	}
}
