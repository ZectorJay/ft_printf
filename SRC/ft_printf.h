/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 10:00:38 by hmickey           #+#    #+#             */
/*   Updated: 2020/12/16 17:23:20 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# define VALID "cspdiuxX%0123456789-+ .#*o"

typedef struct	s_print
{
	int			plus;
	int			minus;
	int			zero;
	char		type;
	int			num;
	int			percent;
	int			space;
	int			dot;
	int			flag;
	int			flag_p;
	int			counter;
	int			dot_for_string;
}				t_print;

int				check_percent(const char *pizdec, t_print **troll,
				int i, va_list list);
int				parse_star(va_list list, t_print **troll);
int				parse_num(const char *pizdec, t_print **troll, int i);
void			parse_string(va_list list, t_print **troll);
int				find_percent(const char *pizdec, t_print **troll, int i);
int				check_type(const char *pizdec, t_print **troll,
				int i, va_list list);
t_print			*new_struct(void);
char			*ft_strchr(const char *s, int c);
int				ft_strlen(const char *str);
int				parse_first_arg(const char *pizdec,
				t_print **troll, va_list list);
int				ft_printf(const char *params, ...);
void			ft_putstr_fd(char const *s, int fd);
void			*ft_memset(void *b, int c, size_t len);
int				ft_isdigit(char c);
int				ft_atoi(const char *str);
char			*ft_itoa(long long int n);
void			parse_char(va_list list, t_print **troll);
void			parse_percent(t_print **troll);
void			parse_decimal(char *new_value, t_print **troll, va_list list);
int				check_stars(const char *pizdec, t_print **troll,
				int i, va_list list);
void			print_positive_value(t_print **troll);
void			print_negative_value(t_print **troll);
void			parse_x(t_print **troll, va_list list);
int				ft_isprint(int c);
int				check_flags(const char *str,
				t_print **troll, int i, va_list list);
char			*ft_strdup(const char *s1);
void			*ft_calloc(size_t count, size_t size);
void			*ft_bzero(void *str, size_t len);

#endif
