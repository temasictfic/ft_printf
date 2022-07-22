/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:46:05 by sciftci           #+#    #+#             */
/*   Updated: 2022/07/21 18:36:37 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;
	char	*first;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			first = (char *)str;
			if (*(++str))
				count += ft_parse((char *)str, ap);
			while (*str && !ft_strchr(SPECIFIERS, *str))
				str++;
			if (!(*str))
				str = first;
		}
		else
			count += ft_putnchar_fd(*str, 1, 1);
		if (*str)
			str++;
	}
	va_end(ap);
	return (count);
}

int	ft_print_format(t_format fmt, va_list ap)
{
	int	count;

	count = 0;
	if (fmt.specifier == 'c' || fmt.specifier == '%')
		count = ft_print_c(fmt, ap);
	if (fmt.specifier == 's')
		count = ft_print_s(fmt, ap);
	if (fmt.specifier == 'd' || fmt.specifier == 'i' || fmt.specifier == 'u')
		count = ft_print_d_i_u(fmt, ap);
	if (fmt.specifier == 'X' || fmt.specifier == 'x')
		count = ft_print_x(fmt, ap);
	if (fmt.specifier == 'p')
		count = ft_print_p(fmt, ap);
	return (count);
}
