/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbrs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:46:24 by sciftci           #+#    #+#             */
/*   Updated: 2022/07/25 22:08:26 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

static char	sign(t_format fmt)
{
	if (fmt.plus)
		return ('+');
	return ('-');
}

static int	ft_print_nbr(t_format fmt, char *nbr, int len, int neg)
{
	int	c;

	c = 0;
	fmt.width -= (fmt.space && !neg && !fmt.plus && fmt.width);
	if (neg || fmt.plus)
		c += ft_putnchar_fd(sign(fmt), 1, fmt.zero && (!fmt.dot
					|| fmt.neg_prec));
	else if (fmt.space)
		c += ft_putnchar_fd(' ', 1, fmt.zero && !fmt.dot);
	if (!fmt.minus && fmt.zero && fmt.width > fmt.prec && (!fmt.dot
			|| fmt.neg_prec))
		c += ft_putnchar_fd('0', 1, fmt.width - fmt.prec - neg - fmt.plus);
	else if (!fmt.minus && fmt.width > fmt.prec)
		c += ft_putnchar_fd(' ', 1, fmt.width - fmt.prec - neg - fmt.plus);
	if (neg || fmt.plus)
		c += ft_putnchar_fd(sign(fmt), 1, !fmt.zero || (fmt.dot
					&& !fmt.neg_prec));
	else if (fmt.space)
		c += ft_putnchar_fd(' ', 1, !fmt.zero || fmt.dot);
	c += ft_putnchar_fd('0', 1, fmt.prec - len);
	c += ft_putstrn_fd(nbr, 1, len);
	if (fmt.minus && fmt.width > fmt.prec)
		c += ft_putnchar_fd(' ', 1, fmt.width - fmt.prec - neg - fmt.plus);
	return (c);
}

int	ft_print_d_i_u(t_format fmt, va_list ap)
{
	char	*nbr;
	int		next;
	int		count;
	int		len;
	int		neg;

	next = va_arg(ap, int);
	neg = (next < 0 && fmt.specifier != 'u');
	if (neg)
		fmt.plus = 0;
	if (next < 0 && fmt.specifier == 'u')
		nbr = ft_uitoa((unsigned)next);
	else
		nbr = ft_itoa(next);
	len = ft_strlen(nbr) * !(*nbr == '0' && !fmt.prec && fmt.dot);
	if (*nbr == '-')
		len--;
	if (fmt.prec < len || !fmt.dot)
		fmt.prec = len;
	count = ft_print_nbr(fmt, nbr + (*nbr == '-'), len, neg);
	free(nbr);
	return (count);
}
