/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajoliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:39:41 by ajoliet           #+#    #+#             */
/*   Updated: 2022/12/14 17:53:05 by ajoliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "str not good", 13);
		return ;
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	putpid(int nbr)
{
	char	c;

	c = nbr % 10 + '0';
	nbr /= 10;
	if (nbr)
		putpid(nbr);
	write(1, &c, 1);
}
