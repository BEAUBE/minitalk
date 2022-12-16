/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajoliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:10:24 by ajoliet           #+#    #+#             */
/*   Updated: 2022/12/14 17:34:44 by ajoliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ar;

void	sigreceived(int sig)
{
	(void)sig;
	g_ar = 1;
}

void	wait(void)
{
	while (1)
	{
		signal(SIGUSR1, sigreceived);
		if (g_ar == 1)
			break ;
	}
	g_ar = 0;
}

void	sendcpid(int spid, int cpid)
{
	int	bit;

	bit = 0;
	while (bit < 32)
	{
		usleep(1000);
		if (cpid >> bit & 1)
		{
			kill(spid, SIGUSR2);
		}
		else
		{
			kill(spid, SIGUSR1);
		}
		bit++;
	}
	wait();
}

int	sendlen(char *str, int spid)
{
	int	i;
	int	bit;

	bit = 0;
	i = 0;
	while (str[i])
		i++;
	while (bit < 32)
	{
		if (i >> bit & 1)
			kill(spid, SIGUSR2);
		else
			kill(spid, SIGUSR1);
		wait();
		bit++;
	}
	return (i);
}

int	main(int ac, char **av)
{
	int	spid;
	int	cpid;
	int	len;

	(void)ac;
	if (ac != 3)
	{
		write(1, "arg Error\n", 11);
		exit(EXIT_FAILURE);
	}
	if (!av[2][0])
		exit(EXIT_SUCCESS);
	cpid = getpid();
	spid = mt_atoi(av[1]);
	if (spid > 0 && kill(spid, SIGUSR1) < 0)
	{
		write(1, "pid Error\n", 11);
		exit(EXIT_FAILURE);
	}
	usleep(100);
	sendcpid(spid, cpid);
	len = sendlen(av[2], spid);
	(void)len;
	sendstr(spid, len, av[2]);
}
