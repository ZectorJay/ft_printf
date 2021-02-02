/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:27:06 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/16 17:21:05 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*reverse(char *new_value)
{
	int		i;
	int		j;
	char	tmp;
	int		len;

	if (!new_value)
		return (NULL);
	j = 0;
	while (new_value[j])
		j++;
	if (j != 0)
		j--;
	i = 0;
	while (i != j && i < j)
	{
		tmp = new_value[i];
		new_value[i++] = new_value[j];
		new_value[j--] = tmp;
	}
	len = ft_strlen(new_value);
	return (new_value);
}

char	fill_value(char new_value, unsigned long int value,
		unsigned long long int ostatok, t_print **troll)
{
	ostatok = value * 10;
	if (ostatok / 10 % 16 > 9 && ostatok != 10)
		ostatok = value % 16 + 1;
	else
		ostatok = value % 16;
	if (ostatok == 11)
		new_value = (*troll)->type == 'x' ? 'a' : 'A';
	else if (ostatok == 12)
		new_value = (*troll)->type == 'x' ? 'b' : 'B';
	else if (ostatok == 13)
		new_value = (*troll)->type == 'x' ? 'c' : 'C';
	else if (ostatok == 14)
		new_value = (*troll)->type == 'x' ? 'd' : 'D';
	else if (ostatok == 15)
		new_value = (*troll)->type == 'x' ? 'e' : 'E';
	else if (ostatok == 16)
		new_value = (*troll)->type == 'x' ? 'f' : 'F';
	else
		new_value = ostatok + 48;
	return (new_value);
}

void	parse_x(t_print **troll, va_list list)
{
	unsigned long int		value;
	unsigned long long int	ostatok;
	char					*new_value;
	int						i;

	i = 0;
	ostatok = 0;
	value = (*troll)->type == 'p' ? va_arg(list, unsigned long int) :
	va_arg(list, unsigned int);
	(*troll)->type == 'p' ? (*troll)->flag_p = 1 : 0;
	(*troll)->type == 'p' ? (*troll)->type = 'x' : 0;
	new_value = ft_calloc(sizeof(char), 10);
	if (value == 0 && (*troll)->dot_for_string <= 0)
		new_value[0] = '0';
	while (value)
	{
		new_value[i] = fill_value(new_value[i], value, ostatok, troll);
		value /= 16;
		i++;
	}
	(*troll)->type == 'X' ? (*troll)->type = 'x' : 0;
	new_value = reverse(new_value);
	parse_decimal(new_value, troll, list);
}
