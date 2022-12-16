/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajoliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:29:07 by ajoliet           #+#    #+#             */
/*   Updated: 2022/12/14 17:38:23 by ajoliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	putpid(int nbr)
{
	char	c;

	c = nbr % 10 + '0';
	nbr /= 10;
	if (nbr)
		putpid(nbr);
	write(1, &c, 1);
}

int	mt_atoi(char *str)
{
	int	res;
	int	neg;
	int	i;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res = res + str[i++] - '0';
	}
	if (str[i] == '\0')
		return (res * neg);
	return (0);
}

void	sendchar(char c, int spid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c >> bit & 1)
			kill(spid, SIGUSR2);
		else
			kill(spid, SIGUSR1);
		wait();
		bit++;
	}
}

void	sendstr(int spid, int len, char *str)
{
	int	byte;

	byte = 0;
	while (byte < len)
	{
		sendchar(str[byte], spid);
		byte++;
	}
}
