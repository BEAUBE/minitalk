/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajoliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:34:33 by ajoliet           #+#    #+#             */
/*   Updated: 2022/12/14 17:55:10 by ajoliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

void	putpid(int nbr);
void	putstr(char *str);
int		mt_atoi(char *str);
void	sendcpid(int spid, int cpid);
int		sendlen(char *str, int spid);
void	sendchar(char c, int spid);
void	sendstr(int spid, int len, char *str);
void	wait(void);
void	ft_putstr(char *str);

#endif
