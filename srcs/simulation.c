/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:10:44 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/18 15:27:42 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_coders(t_parameters *p)
{
	int		i;
	t_coder	**coders_id;

	coders_id = alloc_coders(p, p->no_coders);
	if (!coders_id)
		return (0);
	i = -1;
	while (++i < p->no_coders)
		if (pthread_create(p->coders + i, NULL, &routine, coders_id[i]) != 0)
			return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), err_message(2), 0);
	i = -1;
	while (++i < p->no_coders)
		if (pthread_join(p->coders[i], NULL) != 0)
			return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), err_message(3), 0);
	return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), 1);
}

void	init_dongles(t_parameters *p)
{
	int	i;
	
	i = -1;
	while (++i < p->no_coders)
		pthread_mutex_init(&p->dongles[i], NULL);
}

void	delete_dongles(t_parameters *p)
{
	int	i;
	
	i = -1;
	while (++i < p->no_coders)
		pthread_mutex_destroy(&p->dongles[i]);
}

void	start_simulation(t_parameters *p)
{
	init_dongles(p);
	if (!init_coders(p))
		return (free_p(p));
	return (free_p(p));
}
