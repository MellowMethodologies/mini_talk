/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:41:39 by sbadr             #+#    #+#             */
/*   Updated: 2022/12/22 00:28:36 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	signal_error(void)
{
	ft_putstr("Error: Wrong PID or Signal Error", 2);
	exit(-1);
}

void	chartobin(char c, pid_t pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & 128)
		{
			if (kill(pid, SIGUSR2) == -1)
				signal_error();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				signal_error();
		}
		c <<= 1;
		bit++;
		pause();
		usleep(100);
	}
}

void	send_message(char *message, pid_t pid)
{
	int	i;

	i = 0;
	while (message[i])
	{
		chartobin(message[i], pid);
		i++;
	}
	chartobin('\0', pid);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_putstr("Message sent\n", 1);
		return ;
	}
	else if (sig == SIGUSR2)
	{
		return ;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_putstr("Error: Wrong number of args", 2);
		return (0);
	}
	if (argv[2][0] == '\0')
	{
		ft_putstr("please send a complete message", 2);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 0)
	{
		ft_putstr("waait a sec )_)", 2);
		exit(-1);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_message(argv[2], pid);
	return (0);
}
