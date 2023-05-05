/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:39:46 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 14:30:38 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

t_message	g_response;

static void	check_message(void)
{
	char	letter;
	int		i;

	if (g_response.num_bits % 8 == 0)
	{
		letter = 0;
		i = 0;
		while (i < 8)
		{
			letter = letter | (g_response.bits[i] << (7 - i));
			i ++;
		}
		if (letter == '\0')
		{
			ft_printf("\n");
			exit(0);
		}
		else
			ft_printf("%c", letter);
	}
}

static void	receive_bit(int sig_num)
{
	if (sig_num == SIGUSR1)
		g_response.bits[g_response.num_bits % 8] = 0;
	else if (sig_num == SIGUSR2)
		g_response.bits[g_response.num_bits % 8] = 1;
	else
		write(2, "Error\n", 6);
	g_response.num_bits ++;
	check_message();
}

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
	int					server_pid;
	char				*message;
	struct sigaction	zero_sig;
	struct sigaction	one_sig;

	if (c != 3)
		return (-1);
	g_response.num_bits = 0;
	zero_sig.sa_handler = &receive_bit;
	one_sig.sa_handler = &receive_bit;
	zero_sig.sa_flags = SA_SIGINFO;
	one_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&zero_sig.sa_mask);
	sigemptyset(&one_sig.sa_mask);
	if (sigaction(SIGUSR1, &zero_sig, 0) == -1)
		write(2, "Error\n", 6);
	if (sigaction(SIGUSR2, &one_sig, 0) == -1)
		write(2, "Error\n", 6);
	server_pid = ft_atoi(v[1]);
	message = v[2];
	send_message(server_pid, message);
	write(1, "From server:\n", 14);
	while (1)
		pause();
	return (0);
}
