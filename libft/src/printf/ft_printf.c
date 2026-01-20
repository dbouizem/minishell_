/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:14:19 by dbouizem          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:44 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_printf	data;

	ft_bzero(&data, sizeof(t_printf));
	va_start(ap, format);
	va_copy(data.args, ap);
	while (*format && !data.error)
	{
		if (*format == '%')
		{
			format++;
			parse_format(&format, &data);
		}
		else
			ft_print_char(*format++, &data);
	}
	va_end(ap);
	va_end(data.args);
	if (data.error)
		return (-1);
	return (data.total);
}
