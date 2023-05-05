/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:36:17 by melsahha          #+#    #+#             */
/*   Updated: 2023/05/05 14:30:46 by melsahha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minitalk.h"

t_message	g_message;

static void	check_message(void)
{
	char	letter;
	int		i;

	if (g_message.num_bits % 8 == 0)
	{
		letter = 0;
		i = 0;
		while (i < 8)
		{
			letter = letter | (g_message.bits[i] << (7 - i));
			i ++;
		}
		if (letter == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", letter);
	}
}

static void	receive_bit(int sig_num)
{
	if (sig_num == SIGUSR1)
		g_message.bits[g_message.num_bits % 8] = 0;
	else if (sig_num == SIGUSR2)
		g_message.bits[g_message.num_bits % 8] = 1;
	else if (sig_num == SIGINT)
	{
		write(1, "\nBye 👋", 13);
		exit (0);
	}
	else
		write(2, "Error\n", 6);
	g_message.num_bits ++;
	check_message();
}

int	main(void)
{
	struct sigaction	zero_sig;
	struct sigaction	one_sig;

	g_message.num_bits = 0;
	zero_sig.sa_handler = &receive_bit;
	one_sig.sa_handler = &receive_bit;
	zero_sig.sa_flags = SA_SIGINFO;
	one_sig.sa_flags = SA_SIGINFO;
	signal(SIGINT, &receive_bit);
	sigemptyset(&zero_sig.sa_mask);
	sigemptyset(&one_sig.sa_mask);
	if (sigaction(SIGUSR1, &zero_sig, 0) == -1)
		write(2, "Error\n", 6);
	if (sigaction(SIGUSR2, &one_sig, 0) == -1)
		write(2, "Error\n", 6);
	ft_printf("%i\n", getpid());
	while (1)
		pause();
	return (0);
}
