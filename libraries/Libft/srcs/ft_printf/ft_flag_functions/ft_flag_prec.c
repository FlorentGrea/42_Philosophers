/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_prec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:10:21 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:10:22 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

void	ft_flag_prec(t_flags flags)
{
	while (flags.prec-- > 0)
		ft_putchar_fd('0', 1);
}
