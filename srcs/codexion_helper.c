/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:44:48 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/18 17:06:57 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	**alloc_coders(t_parameters *p, int size)
{
	int		i;
	t_coder	**coders;
	struct timeval start_time;
	
	gettimeofday(&start_time, NULL);
	coders = malloc(size * sizeof(t_coder *));
	if (!coders)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		coders[i] = NULL;
		coders[i] = malloc(size * sizeof(t_coder));
		if (!coders[i])
			return (free_aloc_coders(coders, i), free(coders), err_message(4), NULL);
		coders[i]->code_id = i + 1;
		coders[i]->parameters = p;
		coders[i]->start_time = start_time;
	}
	return coders;
}

void	free_aloc_coders(t_coder **coders, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		(free(coders[i]));
}
