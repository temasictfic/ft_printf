/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:46:17 by sciftci           #+#    #+#             */
/*   Updated: 2022/07/22 03:22:27 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

t_format	ft_defaultfmt(void)
{
	t_format	fmt;

	fmt.minus = 0;
	fmt.plus = 0;
	fmt.width = 0;
	fmt.prec = 0;
	fmt.specifier = 0;
	fmt.zero = 0;
	fmt.dot = 0;
	fmt.space = 0;
	fmt.sharp = 0;
	fmt.neg_prec = 0;
	fmt.str = NULL;
	return (fmt);
}

static t_format	ft_parse_bonus(char *str, t_format fmt)
{
	while (!((*str > '0' && *str <= '9') || *str == '*')
		&& *str != '.' && !ft_strchr(SPECIFIERS, *str))
	{
		if (*str == '-')
			fmt.minus = 1;
		if (*str == '0')
			fmt.zero = 1;
		if (*str == '+')
			fmt.plus = 1;
		if (*str == ' ')
			fmt.space = 1;
		if (*str == '#')
			fmt.sharp = 1;
		str++;
	}
	fmt.str = str;
	return (fmt);
}

static t_format	ft_parse_width(char *str, va_list ap, t_format fmt)
{
	int	specified;

	specified = 0;
	while (*str != '.' && !ft_strchr(SPECIFIERS, *str))
	{
		if (((*str > '0' && *str <= '9') || *str == '*') && !specified)
		{
			if (*str == '*')
				fmt.width = va_arg(ap, int);
			else
				fmt.width = ft_atoi(str);
			specified = 1;
		}
		str++;
	}
	fmt.str = str;
	return (fmt);
}

static t_format	ft_parse_prec(char *str, va_list ap, t_format fmt)
{
	int	specified;

	specified = 0;
	while (!ft_strchr(SPECIFIERS, *str))
	{
		if ((ft_isdigit(*str) || *str == '*') && !specified)
		{
			if (*str == '*')
				fmt.prec = va_arg(ap, int);
			else
				fmt.prec = ft_atoi(str);
			specified = 1;
		}
		str++;
	}
	fmt.str = str;
	return (fmt);
}

int	ft_parse(char *str, va_list ap)
{
	t_format	fmt;

	fmt = ft_defaultfmt();
	fmt = ft_parse_bonus(str, fmt);
	fmt = ft_parse_width(fmt.str, ap, fmt);
	if (*fmt.str == '.' && !fmt.specifier)
	{
		fmt.dot = 1;
		fmt = ft_parse_prec(fmt.str++, ap, fmt);
	}
	if (fmt.width < 0)
	{
		fmt.minus = 1;
		fmt.width *= -1;
	}
	fmt.specifier = *fmt.str;
	fmt.neg_prec = fmt.prec < 0;
	return (ft_print_format(fmt, ap));
}
