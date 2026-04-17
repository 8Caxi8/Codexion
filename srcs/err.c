/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:52:22 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/17 16:04:08 by dansimoe         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "codexion.h"

int err_message(int i)
{
	if (i == 0)
		printf("[ERROR]: Function must be called with following arguments:\n"
			   "./codexion <number_of_coders> <time_to_burnout> <time_to_compile>"
			   " <time_to_debug> <time_to_refactor> <number_of_compiles_required>"
			   "<dongle_cooldown> <scheduler>\n");
	else if(i == 1)
		printf("[ERROR]: Wrong Format!");
	
	return (1);
}
