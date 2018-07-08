/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 17:33:35 by jcamhi            #+#    #+#             */
/*   Updated: 2018/07/08 18:55:07 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

static void	print_info(t_opt *opt)
{
	if (opt->flags & Q_OPT || opt->flags & P_OPT || !(opt->content))
		return ;
	if (opt->flags & S_OPT && !(opt->flags & R_OPT))
	{
		write(1, "MD5 (\"", 6);
		write(1, opt->content, ft_strlen(opt->content));
		write(1, "\") = ", 5);
	}
	else if (opt->flags & S_OPT && opt->flags & R_OPT)
	{
		write(1, " \"", 2);
		write(1, opt->content, ft_strlen(opt->content));
		write(1, "\"", 1);
	}
	else if (!(opt->flags & S_OPT) && !(opt->flags & R_OPT))
	{
		write(1, "MD5 (", 5);
		write(1, opt->content, ft_strlen(opt->content));
		write(1, ") = ", 4);
	}
	else
	{
		write(1, " ", 1);
		write(1, opt->content, ft_strlen(opt->content));
	}
}

static void	print_info_64(t_opt *opt)
{
	if (opt->flags & Q_OPT || opt->flags & P_OPT || !(opt->content))
		return ;
	if (opt->flags & S_OPT && !(opt->flags & R_OPT))
	{
		write(1, "SHA256 (\"", 9);
		write(1, opt->content, ft_strlen(opt->content));
		write(1, "\") = ", 5);
	}
	else if (opt->flags & S_OPT && opt->flags & R_OPT)
	{
		write(1, " \"", 2);
		write(1, opt->content, ft_strlen(opt->content));
		write(1, "\"", 1);
	}
	else if (!(opt->flags & S_OPT) && !(opt->flags & R_OPT))
	{
		write(1, "SHA256 (", 8);
		write(1, opt->content, ft_strlen(opt->content));
		write(1, ") = ", 4);
	}
	else
	{
		write(1, " ", 1);
		write(1, opt->content, ft_strlen(opt->content));
	}
}


void		print_result_32(uint buffer[4], t_opt *opt)
{
	int		i;
	char	buff[33];

	i = 0;
	if (!(opt->flags & R_OPT))
		print_info(opt);
	while (i < 16)
	{
		buff[i * 2] = ((((char *)buffer)[i] & 0xf0) >> 4) + '0';
		buff[i * 2] > '9' ? buff[i * 2] = buff[i * 2] - '9' - 1 + 'a' : 0;
		buff[i * 2 + 1] = (((char *)buffer)[i] & 0xf) + '0';
		buff[i * 2 + 1] > '9' ?
			buff[i * 2 + 1] = buff[i * 2 + 1] - '9' - 1 + 'a' : 0;
		i++;
	}
	write(1, buff, 32);
	if (opt->flags & R_OPT)
		print_info(opt);
	write(1, "\n", 1);
}

void		print_result_64(unsigned char buffer[32], t_opt *opt)
{
	int		i;
	char	buff[65];

	i = 0;
	if (!(opt->flags & R_OPT))
		print_info_64(opt);
	while (i < 32)
	{
		if (i % 4 == 0)
			*(uint *)(buffer + i) = end_conv_32(*(uint *)(buffer + i));
		buff[i * 2] = ((buffer[i] & 0xf0) >> 4) + '0';
		buff[i * 2] > '9' ? buff[i * 2] = buff[i * 2] - '9' - 1 + 'a' : 0;
		buff[i * 2 + 1] = (buffer[i] & 0xf) + '0';
		buff[i * 2 + 1] > '9' ?
			buff[i * 2 + 1] = buff[i * 2 + 1] - '9' - 1 + 'a' : 0;
		i++;
	}
	write(1, buff, 64);
	if (opt->flags & R_OPT)
		print_info_64(opt);
	write(1, "\n", 1);
}

uint		end_conv_32(uint nbr)
{
	return (uint)((nbr >> 24) | ((nbr & 0xFF0000) >> 8) |
		((nbr & 0xFF00) << 8) | (nbr << 24));
}

uint64_t	end_conv_64(uint64_t nbr)
{
	return ((uint64_t)end_conv_32(nbr & -1) << 32 | end_conv_32(nbr >> 32));
}
