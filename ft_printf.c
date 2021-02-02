/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 21:32:24 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/23 11:40:39 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_first_arg(const char *str, t_print **troll, va_list list)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = find_percent(str, troll, i);
		if (str[i])
			i = check_percent(str, troll, i, list);
		if (i == -1)
			return ((*troll)->counter);
	}
	return ((*troll)->counter);
}

int		ft_printf(const char *params, ...)
{
	static	t_print	*troll;
	va_list			list;

	troll = new_struct();
	va_start(list, params);
	parse_first_arg(params, &troll, list);
	va_end(list);
	free(troll);
	return ((*troll).counter);
}

