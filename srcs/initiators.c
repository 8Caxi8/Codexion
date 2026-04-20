/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:03:40 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 15:51:21 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_parameters(t_parameters *p, int *list, const char *scheduler)
{
	pthread_mutex_init(&p->table, NULL);
	pthread_mutex_init(&p->logging, NULL);
	pthread_cond_init(&p->cond_table, NULL);
	p->no_coders = list[0];
	p->burnout = list[1];
	p->compile = list[2];
	p->debug = list[3];
	p->refactor = list[4];
	p->compiles_required = list[5];
	p->dongle_cooldown = list[6];
	p->scheduler = scheduler;
	p->stop = 0;
	p->finished_coders = 0;
}

void	init_dongle_state(t_parameters *p)
{
	int	i;

	i = -1;
	while(++i < p->no_coders)
		p->dongle_state[i] = 0;
}

int	init_threads(t_coder **coders_id, t_parameters *p)
{
	int	i;

	i = -1;
	while (++i < p->no_coders)
		if (pthread_create(p->coders + i, NULL, &routine, coders_id[i]) != 0)
			return (0);
	i = -1;
	while (++i < p->no_coders)
		if (pthread_create(p->dongles + i, NULL, &dongle_routine, coders_id[i]) != 0)
			return (0);
	if (pthread_create(&p->monitor, NULL, &monitor_routine, coders_id) != 0)
		return (0);
	return (1);
}

int	init_coders(t_parameters *p)
{
	int		i;
	t_coder	**coders_id;

	coders_id = alloc_coders(p, p->no_coders);
	if (!coders_id)
		return (0);
	if (!init_threads(coders_id, p))
		return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), err_message(2), 0);
	i = -1;
	while (++i < p->no_coders)
		if (pthread_join(p->coders[i], NULL) != 0)
			return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), err_message(3), 0);
	i = -1;
	while (++i < p->no_coders)
		if (pthread_join(p->dongles[i], NULL) != 0)
			return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), err_message(3), 0);
	if (pthread_join(p->monitor, NULL) != 0)
		return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), err_message(3), 0);
	return (free_aloc_coders(coders_id, p->no_coders), free(coders_id), 1);
}
