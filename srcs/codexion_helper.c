/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:44:48 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 10:22:00 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(struct timeval start)
{
	struct timeval now;
	
	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000
		+ (now.tv_usec - start.tv_usec) / 1000);
}
