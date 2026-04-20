/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:18:48 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 16:03:50 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *arg)
{
	t_coder	*coders = (t_coder *) arg;
	int	coder_id;
	int compiles;
	
	compiles = 0;
	coder_id = coders->code_id;
	while (compiles < coders->parameters->compiles_required && !coders->parameters->stop)
	{
		wait_to_compile(coders, coder_id);
		debug(coders, coder_id);
		refactor(coders, coder_id);
		compiles++;
	}
	pthread_mutex_lock(&coders->parameters->table);
	coders->parameters->finished_coders++;
	if (coders->parameters->finished_coders == coders->parameters->no_coders)
	{
		coders->parameters->stop = 1;
		pthread_cond_broadcast(&coders->parameters->cond_table);
	}
	pthread_mutex_unlock(&coders->parameters->table);
	return (NULL);
}

void	*dongle_routine(void *arg)
{
	t_coder	*coders = (t_coder *) arg;
	int	dongle_id;

	dongle_id = coders->code_id -1;
	
	pthread_mutex_lock(&coders->parameters->table);
	while(!coders->parameters->stop)
	{
		while (coders->parameters->dongle_state[dongle_id] != 2 && !coders->parameters->stop)
			pthread_cond_wait(&coders->parameters->cond_table, &coders->parameters->table);
		if (coders->parameters->stop)
			break;
		pthread_mutex_unlock(&coders->parameters->table);
		usleep(coders->parameters->dongle_cooldown * 1000);
		pthread_mutex_lock(&coders->parameters->table);
		coders->parameters->dongle_state[dongle_id] = 0;
		pthread_cond_broadcast(&coders->parameters->cond_table);
	}
	pthread_mutex_unlock(&coders->parameters->table);
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_coder 		**coders = (t_coder **) arg;
	t_parameters	*p = coders[0]->parameters;
	long			now;
	int				i;
	
	coders = (t_coder **) arg;
	p = coders[0]->parameters;
	while (!p->stop)
	{
		usleep(1000);
		i = -1;
		now = get_time_ms(coders[0]->start_time);
		while (++i < p->no_coders)
		{
			if (now - coders[i]->last_compile > p->burnout)
			{
				pthread_mutex_lock(&p->table);
				coder_write(now, coders[i]->code_id, "burned out", &p->logging);
				p->stop = 1;
				pthread_cond_broadcast(&p->cond_table);
				pthread_mutex_unlock(&p->table);
				break;
			}
		}
	}
	return (NULL);
}