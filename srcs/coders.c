/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:20:26 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 14:19:06 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	wait_to_compile(t_coder *coders, int coder_id)
{
	int				left;
	int				right;

	left = coder_id - 1;
	if (coder_id == ((t_coder *) coders)->parameters->no_coders)
		right = 0;
	else
		right = coder_id;
	pthread_mutex_lock(&coders->parameters->table);
	while (coders->parameters->dongle_state[left] != 0 || coders->parameters->dongle_state[right] != 0)
		pthread_cond_wait(&coders->parameters->cond_table, &coders->parameters->table);
	take_dongle(coders, left, coder_id);
	take_dongle(coders, right, coder_id);
	pthread_mutex_unlock(&coders->parameters->table);
	compile(coders, coder_id);
	release_dongle(coders, left);
	release_dongle(coders, right);
}

void coder_write(long time, int id, const char *message, pthread_mutex_t *logging)
{
	pthread_mutex_lock(logging);
	printf("%ld %d %s", time, id, message);
	pthread_mutex_unlock(logging);
}
