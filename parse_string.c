/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:17:03 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/16 19:13:46 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			parse_num(const char *pizdec, t_print **troll, int i)
{
	int		num;
	int		check;
	char	*itoa;
	int		count;

	count = 0;
	if (pizdec[i - 1] == '.')
		count = 1;
	while (pizdec[i] == '0')
		i++;
	num = ft_atoi(pizdec + i);
	itoa = ft_itoa(num);
	check = ft_strlen(itoa);
	if (count == 0)
		(*troll)->num = num;
	if (count == 1)
	{
		(*troll)->dot = num > 0 ? num : 0;
		num < 0 ? (*troll)->dot_for_string = -1 : 0;
	}
	free(itoa);
	return (i + check);
}

static char	*get_string(t_print **troll)
{
	if (((*troll)->dot <= 0 || (*troll)->num <= ft_strlen("(null)"))
	&& (*troll)->dot_for_string == -1)
	{
		if ((*troll)->dot < ft_strlen("(null)"))
			(*troll)->dot = ft_strlen("(null)");
		if ((*troll)->num < ft_strlen("(null)"))
			(*troll)->num = ft_strlen("(null)");
	}
	return ("(null)");
}

static void	fix_params(t_print **troll, char *value)
{
	if ((*troll)->dot)
		(*troll)->num -= (*troll)->dot < ft_strlen(value) ?
		(*troll)->dot : ft_strlen(value);
	else
		(*troll)->num -= ft_strlen(value);
	if (!(*troll)->minus)
	{
		while ((*troll)->zero && (*troll)->num-- > 0)
			(*troll)->counter += write(1, "0", 1);
		while (!(*troll)->zero && (*troll)->num-- > 0)
			(*troll)->counter += write(1, " ", 1);
	}
}

void		parse_string(va_list list, t_print **troll)
{
	char	*value;
	int		i;

	i = -1;
	if (!(value = va_arg(list, char*)))
		value = get_string(troll);
	if (!(*troll)->dot && (*troll)->dot_for_string > 0)
		value = "";
	fix_params(troll, value);
	if ((*troll)->dot)
		while (++i < (*troll)->dot && value[i])
			(*troll)->counter += write(1, &value[i], 1);
	else
		while (value[++i])
			(*troll)->counter += write(1, &value[i], 1);
	while ((*troll)->num-- > 0 && (*troll)->minus)
		(*troll)->counter += write(1, " ", 1);
}

void		parse_char(va_list list, t_print **troll)
{
	int	value;
	int		num;

	num = (*troll)->num;
	value = va_arg(list, unsigned int);
	if (!(*troll)->minus)
	{
		while ((*troll)->zero && (num--) > 1)
			(*troll)->counter += write(1, "0", 1);
		while (!(*troll)->zero && (num--) > 1)
			(*troll)->counter += write(1, " ", 1);
	}
	(*troll)->counter += write(1, &value, 1);
	while ((*troll)->minus && (num--) > 1)
		(*troll)->counter += write(1, " ", 1);
}
