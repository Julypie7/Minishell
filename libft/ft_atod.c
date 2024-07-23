/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <martalop@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:11:55 by martalop          #+#    #+#             */
/*   Updated: 2024/07/03 19:03:23 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <math.h>

double	get_decimal(const char *str)
{
	int		i;
	int		count;
	double	dec_num;

	i = 0;
	count = 0;
	dec_num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		dec_num = dec_num * 10.0 + (str[i] - '0');
		count++;
		i++;
	}
	return (dec_num / pow(10.0, count));
}

void	check_decimal(const char *str, int i, int *flag, double *num)
{
	if (str[i] == '.' && str[i + 1])
	{
		if (*num >= 2 && get_decimal(&str[i + 1]) != 0.0)
			*flag = 1;
		*num = *num + get_decimal(&str[i + 1]);
	}
}

double	ft_atod(const char *str, int *flag)
{
	int		signo;
	double	num;
	int		i;

	i = 0;
	num = 0;
	signo = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signo = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	check_decimal(str, i, flag, &num);
	return (signo * num);
}

//(0 || (i = 0) || (num = 0) || (signo = 1));

/*#include <stdlib.h>

int	main(void)
{
	const char	*str;

	str = "12.214748364749";
	printf("%.15f\n", ft_atod(str));
	return (0);
}*/
