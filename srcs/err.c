/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:04:23 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 12:42:12 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	err_message(int i)
{
	if (i == 0)
	{
		printf("[ERROR]: Function must be called with following arguments:\n");
		printf("./codexion <number_of_coders> <time_to_burnout> ");
		printf("<time_to_compile> <time_to_debug> <time_to_refactor> ");
		printf("<number_of_compiles_required> <dongle_cooldown> <scheduler>\n");
	}
	else if (i == 1)
		printf("[ERROR]: Wrong Format!\n");
	else if (i == 2)
		printf("[ERROR]: Failed to create thread!\n");
	else if (i == 3)
		printf("[ERROR]: Failed to join thread!\n");
	else if (i == 4)
		printf("[ERROR]: Coders memory allocation failed!\n");
	return (1);
}
