/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 22:13:43 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/15 22:14:22 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*new_struct(void)
{
	t_print	*new_one;

	if (!(new_one = malloc(sizeof(t_print))))
		return (NULL);
	new_one->plus = 0;
	new_one->minus = 0;
	new_one->zero = 0;
	new_one->type = 0;
	new_one->num = 0;
	new_one->percent = 0;
	new_one->space = 0;
	new_one->dot = 0;
	new_one->flag = 2;
	new_one->flag_p = 0;
	new_one->counter = 0;
	new_one->dot_for_string = 0;
	return (new_one);
}
