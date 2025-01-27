/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagame <yagame@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:08:13 by yagame            #+#    #+#             */
/*   Updated: 2025/01/27 13:14:01 by yagame           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


void	ft_putchar(char c)
{
	write(1, &c, 1);
}
void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}
