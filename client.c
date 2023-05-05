/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:39:46 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 14:30:36 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

static void	send_signal(int server_pid, char letter)
{
	int	i;
	int	ascii;

	i = 8;
	ascii = (int) letter;
	while (--i >= 0)
	{
		if ((ascii >> i) & 1)
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				write(2, "Error\n", 6);
				exit(0);
			}
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				write(2, "Error\n", 6);
				exit(0);
			}
		}
		usleep(100);
	}
}

static void	send_message(int server_pid, char *message)
{
	int	i;

	i = 0;
	while (message && message[i])
	{
		send_signal(server_pid, message[i]);
		i++;
	}
	send_signal(server_pid, '\0');
}

int	main(int c, char **v)
{
	int		server_pid;
	char	*message;

	if (c != 3)
		return (0);
	server_pid = ft_atoi(v[1]);
	message = v[2];
	send_message(server_pid, message);
	return (0);
}
