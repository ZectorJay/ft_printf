/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:38:57 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/22 19:00:50 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fix_flags(t_print **troll, char *itoa)
{
	if ((*troll)->dot_for_string > 0)
		(*troll)->zero = 0;
	if ((*troll)->type == 'i')
		(*troll)->dot ? (*troll)->zero = 0 : 0;
	if ((*troll)->minus || (*troll)->dot)
		(*troll)->zero = 0;
	if ((*troll)->plus)
		(*troll)->space = 0;
	if ((*troll)->dot >= ft_strlen(itoa))
		(*troll)->num -= (*troll)->dot;
	else
		(*troll)->num -= ft_strlen(itoa);
	if ((*troll)->dot)
		(*troll)->dot -= (*troll)->dot ? ft_strlen(itoa) : 0;
	if ((*troll)->type == 'u')
	{
		(*troll)->plus = 0;
		(*troll)->space = 0;
	}
	if ((*troll)->type == 'x')
	{
		(*troll)->plus = 0;
		(*troll)->space = 0;
	}
}

void	writing_for_decimal(char *itoa, t_print **troll, long long int value)
{
	if (value >= 0)
		print_positive_value(troll);
	else
		print_negative_value(troll);
	write(1, itoa, ft_strlen(itoa));
	(*troll)->counter += ft_strlen(itoa);
	if ((*troll)->minus)
		while ((*troll)->num-- > 0)
		{
			(*troll)->counter++;
			write(1, " ", 1);
		}
}

void	parse_decimal(char *new_value, t_print **troll, va_list list)
{
	long long		num;
	long long int	value;
	char			*itoa;

	value = 0;
	if ((*troll)->type != 'u' && (*troll)->type != 'x')
		value = va_arg(list, int);
	else if ((*troll)->type != 'x')
		value = va_arg(list, unsigned int);
	num = value >= 0 ? value : (-1 * value);
	itoa = ft_itoa(num);
	if ((*troll)->type == 'x')
	{
		itoa = new_value;
		value = 1;
	}
	if ((*troll)->dot_for_string < 0 && value == 0)
		itoa = "0";
	else if ((*troll)->dot_for_string && value == 0)
		itoa = "";
	fix_flags(troll, itoa);
	writing_for_decimal(itoa, troll, value);
	if (value != 0)
		free(itoa);
}

/*
** oops
*/

void	print_positive_value(t_print **troll)
{
	(*troll)->flag_p == 1 ? (*troll)->num -= 2 : 0;
	(*troll)->flag_p == 1 ? (*troll)->counter += 2 : 0;
	(*troll)->num -= (*troll)->plus ? (*troll)->plus : (*troll)->space;
	if (!(*troll)->zero && !(*troll)->minus)
		while ((*troll)->num-- > 0)
			(*troll)->counter += write(1, " ", 1);
	else if ((*troll)->zero && !(*troll)->minus)
		while ((*troll)->num-- > 0)
			(*troll)->counter += write(1, "0", 1);
	(*troll)->flag_p == 1 ? write(1, "0x", 2) : 0;
	if ((*troll)->plus)
		(*troll)->counter += write(1, "+", 1);
	if ((*troll)->space)
		(*troll)->counter += write(1, " ", 1);
	while ((*troll)->dot-- > 0)
		(*troll)->counter += write(1, "0", 1);
}

void	print_negative_value(t_print **troll)
{
	(*troll)->dot--;
	(*troll)->num--;
	if (!(*troll)->zero && !(*troll)->minus)
		while ((*troll)->num-- > 0)
		{
			(*troll)->counter++;
			write(1, " ", 1);
		}
	write(1, "-", 1);
	(*troll)->counter++;
	if ((*troll)->zero && !(*troll)->minus)
		while ((*troll)->num-- > 0)
		{
			(*troll)->counter++;
			write(1, "0", 1);
		}
	while ((*troll)->dot-- >= 0)
	{
		write(1, "0", 1);
		(*troll)->counter++;
	}
}
