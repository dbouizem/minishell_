/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:11:18 by dbouizem          #+#    #+#             */
/*   Updated: 2025/09/23 17:32:38 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_dispatch_format(char specifier, t_printf *data)
{
	if (!specifier || data->error)
		return ;
	if (specifier == 'c')
		ft_print_char((char)va_arg(data->args, int), data);
	else if (specifier == 's')
		ft_print_str(va_arg(data->args, char *), data);
	else if (specifier == 'p')
		ft_print_ptr(va_arg(data->args, void *), data);
	else if (specifier == 'd' || specifier == 'i')
		ft_print_int(va_arg(data->args, int), data);
	else if (specifier == 'u')
		ft_print_u_int(va_arg(data->args, unsigned int), data);
	else if (specifier == 'x')
		ft_print_hex(va_arg(data->args, unsigned int), 0, data);
	else if (specifier == 'X')
		ft_print_hex(va_arg(data->args, unsigned int), 1, data);
	else if (specifier == '%')
		ft_print_char('%', data);
	else
	{
		ft_print_char('%', data);
		ft_print_char(specifier, data);
	}
}

void	handle_invalid_specifier(const char **format, t_printf *data)
{
	ft_print_char('%', data);
	if (**format)
	{
		ft_print_char(**format, data);
		(*format)++;
	}
}

void	parse_format(const char **format, t_printf *data)
{
	if (ft_strchr("cspdiuxX%", **format))
	{
		handle_dispatch_format(**format, data);
		(*format)++;
	}
	else
		handle_invalid_specifier(format, data);
}
