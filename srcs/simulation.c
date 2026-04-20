/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:10:44 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 11:03:59 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	delete_dongles(t_parameters *p)
{
	int	i;
	
	i = -1;
	while (++i < p->no_coders)
		pthread_mutex_destroy(&p->dongles[i]);
}

void	delete_sig_dongles(t_parameters *p)
{
	int	i;
	
	i = -1;
	while (++i < p->no_coders)
		pthread_cond_destroy(&p->sig_dongles[i]);
}

void	start_simulation(t_parameters *p)
{
	init_dongles(p);
	if (!init_coders(p))
		return (free_p(p));
	return (free_p(p));
}
