/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:41:34 by sbadr             #+#    #+#             */
/*   Updated: 2022/12/22 11:23:48 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void static	sigerror(void)
{
	ft_putstr("Error :PID-404", 2);
	exit(-1);
}

void	sighandlehelp(char *c, int *i, pid_t *clientpid)
{
	write(1, c, 1);
	if (*c == '\0')
	{
		write(1, "\n", 1);
		*c = 0;
		if (kill(*clientpid, SIGUSR1) == -1)
			sigerror();
		return ;
	}
	*i = 0;
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int		i;
	static char		c;
	static pid_t	clientpid;
	static pid_t	workingpid;

	(void)context;
	if (!clientpid)
		clientpid = info->si_pid;
	workingpid = info->si_pid;
	if (clientpid != workingpid)
	{
		clientpid = workingpid;
		i = 0;
		c = 0;
	}
	c |= (sig == SIGUSR2);
	i++;
	if (i == 8)
		sighandlehelp(&c, &i, &clientpid);
	c <<= 1;
	usleep(100);
	kill(clientpid, SIGUSR2);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putstr("\n", 1);
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{	
		pause();
	}
}
