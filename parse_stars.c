/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 07:53:44 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/16 16:16:08 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_star(va_list list, t_print **troll)
{
	int digit;

	digit = 0;
	if (!(digit = va_arg(list, int)))
		return (0);
	if (digit < 0)
		(*troll)->dot_for_string = -1;
	return (digit);
}

void	parse_percent(t_print **troll)
{
	int		num;

	num = (*troll)->num;
	if (!(*troll)->minus)
	{
		while ((*troll)->zero && (num--) > 1)
			(*troll)->counter += write(1, "0", 1);
		while (!(*troll)->zero && (num--) > 1)
			(*troll)->counter += write(1, " ", 1);
	}
	(*troll)->counter += write(1, "%", 1);
	while ((*troll)->minus && (num--) > 1)
		(*troll)->counter += write(1, " ", 1);
}

int		find_percent(const char *pizdec, t_print **troll, int i)
{
	while (pizdec[i] != '%' && pizdec[i])
	{
		(*troll)->counter += write(1, &pizdec[i], 1);
		i++;
	}
	if (pizdec[i] == '%')
	{
		(*troll)->percent = 1;
		i++;
	}
	return (i);
}

void	no_type(const char *pizdec, t_print **troll)
{
	int i;

	i = 0;
	while (ft_strchr(VALID, pizdec[i]))
		i++;
	if (!ft_strchr(VALID, pizdec[i]))
		i++;
	while (pizdec[i])
	{
		(*troll)->counter += write(1, &pizdec[i], 1);
		i++;
	}
}

int		check_percent(const char *pizdec, t_print **troll, int i, va_list list)
{
	int j;

	j = i;
	while (pizdec[j] && j != -1)
	{
		if (ft_strchr("cspdiuxX%o", pizdec[j]))
			j = -2;
		j++;
	}
	if (j != -1 && (*troll)->percent == 1)
	{
		no_type(pizdec + i, troll);
		return (-1);
	}
	while (pizdec[i])
	{
		if (!ft_strchr(VALID, pizdec[i]))
			return (-1);
		i = check_flags(pizdec, troll, i, list);
		if ((check_type(pizdec, troll, i, list)))
			return (++i);
		i++;
	}
	return (i);
}
