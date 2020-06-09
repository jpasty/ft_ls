/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 20:09:10 by lseema            #+#    #+#             */
/*   Updated: 2020/06/05 15:30:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# define BLACK		"\x1b[30m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN 		"\x1b[36m"
# define WHITE 		"\x1b[37m"
# define RESET 		"\x1b[0m"

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct		s_format
{
	size_t			i;
	char			hash;
	char			minus_zero;
	char			plus_space;
	size_t			width;
	int				precision;
	int				size;
	char			type;
	char			float_type;
	int				sign;
	char			*bdot;
	char			*adot;
	char			*zero;
	char			*ten;
	char			*one;
}					t_format;

typedef struct		s_calc
{
	char			*zero;
	char			*ten;
	char			*one;
	char			*rem;
	char			*k;
	char			*out;
}					t_calc;

typedef struct		s_mult
{
	char			*zero;
	char			*preout;
	char			*out;
	char			*s1;
	char			*s2;
	char			*hereout;
	size_t			longest;
	unsigned int	carry;
	int				i;
}					t_mult;

typedef struct		s_sum
{
	unsigned int	carry;
	char			*carryc;
	char			*out;
	char			*s1;
	char			*s2;
	size_t			l;
	size_t			s;
}					t_sum;

typedef struct		s_subt
{
	int				carry;
	int				temp;
	int				rem;
	char			*s1;
	char			*s2;
	size_t			l;
	size_t			s;
	char			*out;
	char			*remc;
}					t_subt;

typedef struct		s_fl
{
	unsigned long	mant;
	unsigned short	exp:15;
	unsigned char	sign:1;
}					t_fl;

union				u_float
{
	long double		num;
	t_fl			val;
}					fl;

int					ft_printf(const char *format, ...);
size_t				format_manager(const char *format, va_list ap);
void				format_clean(t_format *param);
t_format			*format_initialize(void);
void				format_parser(const char *format, t_format *param,
		va_list ap);
void				flags_parser(const char *format, t_format *param);
void				width_prcsn_parser(const char *format, t_format *param,
		va_list ap);
void				size_parser(const char *format, t_format *param);
size_t				print_argument(t_format *param, char s, va_list ap);
size_t				print_int(t_format *param, va_list ap);
size_t				print_oct(t_format *param, va_list ap);
size_t				print_unsigned(t_format *param, va_list ap);
size_t				print_hex(t_format *param, va_list ap);
size_t				print_str(t_format *param, va_list ap);
size_t				print_pointer(t_format *param, va_list ap);
size_t				print_float(t_format *param, va_list ap);
size_t				print_percent(t_format *param);
size_t				print_chr(t_format *param, va_list ap);
char				*ft_itoa_base(unsigned long long value, int base, int reg);
char				*print_int2(t_format *param, char *str, int sign);
char				*fill_zero(t_format *param, char *str, size_t len);
char				*fill_zero_unsigned(t_format *param, char *str, size_t len);
char				*print_width(t_format *param, char *str, size_t len);
char				*add_atributes_width(t_format *param, char *str, char *tmp);
char				*split_and_assemble(t_format *param, char *str, char *tmp);
char				*add_atributes_precision(char *tmp, char *str);
unsigned long long	get_unsigned(t_format *param, va_list ap);
char				*string_width(t_format *param, char *str, size_t len);
char				*pointer_precision(t_format *param, char *str, size_t len);
void				clr_float_params(t_format *param);
char				*strjf(char *s1, char *s2, int k1, int k2);
char				*ft_add(char *s1, char *s2, int negs, int clr);
char				*ft_subtract(char *s1, char *s2);
char				*ft_mult(char *stra, char *strb);
size_t				str_to_out(char *str);
char				*exceptions(unsigned long m, int sign);
size_t				ft_max(char *s1, char *s2);
size_t				ft_min(char *s1, char *s2);
int					ft_abs(int nb);
void				clean_mult(t_mult *mult);
void				clean_sum(t_sum *sum);
char				*ft_strsubf(char *s, unsigned int start, size_t len);
char				*check_format(t_format *param);
char				*e_format(t_format *param);
char				*g_precision(t_format *params);
char				*f_precision(t_format *params, int i);
char				*cropp(char *adot, int prec, char *one);
int					ft_chararcmp(char *a, char *b);
char				*ft_negs(char *res);
int					put_color(char *color);
int					colorize(const char *s);

#endif
