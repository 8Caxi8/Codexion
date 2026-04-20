/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:04:36 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 14:43:37 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_parameters(t_parameters *parameters)
{
	printf("The following parameters were asign:\n");
	printf("	-Coders:    %d\n", parameters->no_coders);
	printf("	-Burnout:   %d\n", parameters->burnout);
	printf("	-Compile:   %d\n", parameters->compile);
	printf("	-Debug:     %d\n", parameters->debug);
	printf("	-Refactor:  %d\n", parameters->refactor);
	printf("	-Com_Req:   %d\n", parameters->compiles_required);
	printf("	-Dong_CD:   %d\n", parameters->dongle_cooldown);
	printf("	-Scheduler: %s\n", parameters->scheduler);
}

int	main(int ac, char **av)
{
	t_parameters	*parameters;

	parameters = NULL;
	if (ac == 9)
	{
		parameters = parser(av);
		if (!parameters)
			return (err_message(1));
		//print_parameters(parameters);
		start_simulation(parameters);
	}
	else
		return (err_message(0));
	return (0);
}
