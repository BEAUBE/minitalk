/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajoliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:04:09 by ajoliet           #+#    #+#             */
/*   Updated: 2022/12/14 17:56:21 by ajoliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_str;

void	reccpid(int sig, int *cpid, int *step)
{
	static int	bit = 0;

	if (sig == SIGUSR1)
		*cpid |= (0 << bit);
	else
		*cpid |= (1 << bit);
	bit++;
	if (bit == 32)
	{
		bit = 0;
		*step += 1;
	}
}

int	*reclen(int sig, int *step)
{
	static int	len = 0;
	static int	bit = 0;

	if (sig == SIGUSR1)
		len |= (0 << bit);
	else
		len |= (1 << bit);
	bit++;
	if (bit == 32)
	{
		g_str = malloc(sizeof(char) * len + 1);
		*step += 1;
		bit = 0;
	}
	return (&len);
}

void	recstr(int sig, int len, int *step)
{
	static int	bit = 0;
	static int	byte = 0;

	if (sig == SIGUSR1)
		g_str[byte] |= (0 << bit);
	else
		g_str[byte] |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		byte++;
		if (byte == len)
		{
			ft_putstr(g_str);
			byte = 0;
			*step += 1;
		}
		bit = 0;
	}	
}

void	server_handler(int sig)
{
	static int	step = 0;
	static int	cpid = 0;
	static int	*len = NULL;

	if (step == 3)
		recstr(sig, *len, &step);
	if (step == 2)
		len = reclen(sig, &step);
	if (step == 1)
		reccpid(sig, &cpid, &step);
	if (step == 0)
		step++;
	if (step > 1)
		kill(cpid, SIGUSR1);
	if (step == 4)
	{
		cpid = 0;
		*len = 0;
		free(g_str);
		step = 0;
	}
}

int	main(void)
{
	putpid(getpid());
	write(1, "\n", 2);
	while (1)
	{
		signal(SIGUSR1, server_handler);
		signal(SIGUSR2, server_handler);
	}
}
