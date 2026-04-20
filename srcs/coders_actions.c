/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:25:12 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 15:42:54 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void release_dongle(t_coder *coders, int dongle)
{
	pthread_mutex_lock(&coders->parameters->table);
	coders->parameters->dongle_state[dongle] = 2;
	pthread_cond_broadcast(&coders->parameters->cond_table);
	pthread_mutex_unlock(&coders->parameters->table);
}

void	take_dongle(t_coder *coders, int dongle, int coder_id)
{
	int	curr_time;

	curr_time = get_time_ms(coders->start_time);
	coders->parameters->dongle_state[dongle] = 1;
	coder_write(curr_time, coder_id, "has taken a dongle\n", &coders->parameters->logging);
}

void debug(t_coder *coders, int coder_id)
{
	long	curr_time;

	curr_time = get_time_ms(coders->start_time);
	coder_write(curr_time, coder_id, "is debugging\n", &coders->parameters->logging);
	usleep(((t_coder *) coders)->parameters->debug * 1000);
}

void refactor(t_coder *coders, int coder_id)
{
	long	curr_time;

	curr_time = get_time_ms(coders->start_time);
	coder_write(curr_time, coder_id, "is refactoring\n", &coders->parameters->logging);
	usleep(coders->parameters->refactor * 1000);
}

void compile(t_coder *coders, int coder_id)
{
	long	curr_time;

	curr_time = get_time_ms(coders->start_time);
	coders->last_compile = curr_time;
	coder_write(curr_time, coder_id, "is compiling\n", &coders->parameters->logging);
	usleep(coders->parameters->compile * 1000);
}
