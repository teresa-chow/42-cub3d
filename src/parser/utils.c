/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:42:55 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/26 07:01:43 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

bool	check_file_format(char *str, char *format)
{
	int			i;
	int			j;

	i = ft_strlen(str) - 4;
	j = 0;
	while (j < 4)
	{
		if (str[i++] != format[j++])
			return (0);
	}
	return (1);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
