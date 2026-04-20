/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:19:34 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 15:43:39 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_parameters	*alloc_parameters(t_parameters *p, int *list, const char *scheduler)
{
	p = malloc(sizeof(t_parameters));
	if (!p)
		return (free(list), NULL);
	init_parameters(p, list, scheduler);
	p->coders = malloc(p->no_coders * sizeof(pthread_t));
	if (!p->coders)
		return (free(list), NULL);
	p->dongles = malloc(p->no_coders * sizeof(pthread_t));
	if (!p->dongles)
		return (free(list), free(p->coders), NULL);
	p->dongle_state = malloc(p->no_coders * sizeof(int *));
	if (!p->dongle_state)
		return (free(list), free(p->coders), free(p->dongles), NULL);
	init_dongle_state(p);
	return (free(list), p);
}

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
		coders[i]->last_compile = 0;
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

void	free_p(t_parameters *p)
{
	if (p->coders)
		free(p->coders);
	if (p->dongles)
		free(p->dongles);
	free(p->dongle_state);
	thread_destroy(p);
	free(p);
}

void	thread_destroy(t_parameters *p)
{
	pthread_mutex_destroy(&p->table);
	pthread_mutex_destroy(&p->logging);
	pthread_cond_destroy(&p->cond_table);
}
