/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 02:24:52 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/16 16:21:47 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_width(const char *str, int i,
				t_print **troll, va_list list)
{
	if ((str[i] == '*' || ft_isdigit(str[i]))
	&& str[i - 1] != '.' && str[i] != '0')
	{
		str[i] == '*' ? (*troll)->num = parse_star(list, troll) :
		(i = parse_num(str, troll, i));
		if ((*troll)->num < 0)
		{
			(*troll)->num *= -1;
			(*troll)->minus = 1;
		}
	}
	return (i);
}

static void	get_num(const char *str, t_print **troll,
				int i, va_list list)
{
	while (!(ft_strchr("cspdiuxX%o", str[i])))
	{
		i = get_width(str, i, troll, list);
		if (ft_strchr("cspdiuxX%o", str[i]))
		{
			(*troll)->flag = 0;
			break ;
		}
		if ((str[i] == '*' || ft_isdigit(str[i]))
			&& str[i - 1] == '.')
		{
			(*troll)->dot_for_string = 1;
			str[i] == '*' ? ((*troll)->dot = parse_star(list, troll)) :
			(i = parse_num(str, troll, i));
		}
		if (str[i] == '.' && (!ft_isdigit(str[i + 1])
			|| str[i + 1] != '*'))
		{
			(*troll)->dot = 0;
			(*troll)->dot_for_string = 1;
		}
		i++;
	}
}

int			check_stars(const char *str,
			t_print **troll, int i, va_list list)
{
	int		old;

	old = i;
	while (str[i] && !(ft_strchr("cspdiuxX%o", str[i])))
	{
		if (ft_strchr("cspdiuxX%o", str[i + 1]))
		{
			i = old;
			(*troll)->flag = 1;
			break ;
		}
		i++;
	}
	if ((*troll)->flag == 1)
		get_num(str, troll, i, list);
	i = old;
	return (i);
}

int			check_flags(const char *str,
			t_print **troll, int i, va_list list)
{
	if ((*troll)->flag == 2)
		i = check_stars(str, troll, i, list);
	(*troll)->plus = (str[i] == '+') ? 1 : (*troll)->plus;
	(*troll)->minus = (str[i] == '-') ? 1 : (*troll)->minus;
	if (!ft_isdigit(str[i - 1]) && str[i - 1] != '.' && str[i] == '0')
		(*troll)->zero = 1;
	(*troll)->space = (str[i] == 32) ? 1 : (*troll)->space;
	return (i);
}

int			check_type(const char *str,
			t_print **troll, int i, va_list list)
{
	int		count;

	count = 0;
	if (ft_strchr("cspdiuxX%o", str[i]))
	{
		count += (*troll)->counter;
		(*troll)->counter = 0;
		(*troll)->type = *(ft_strchr("cspdiuxX%o", str[i]));
		(*troll)->dot < 0 ? (*troll)->dot = 0 : 0;
		(*troll)->type == 'o' ? (*troll)->type = 'd' : 0;
		(*troll)->type == '%' ? parse_percent(troll) : 0;
		(*troll)->type == 's' ? parse_string(list, troll) : 0;
		(*troll)->type == 'c' ? parse_char(list, troll) : 0;
		((*troll)->type == 'd' || (*troll)->type == 'i' ||
		(*troll)->type == 'u') ? parse_decimal(0, troll, list) : 0;
		((*troll)->type == 'x' || (*troll)->type == 'X'
		|| (*troll)->type == 'p') ? parse_x(troll, list) : 0;
		count += (*troll)->counter;
		free(*troll);
		*troll = new_struct();
		(*troll)->counter = count;
		return (1);
	}
	return (0);
}
