/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:08:42 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/17 16:12:48 by dansimoe         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "codexion.h"

int is_int(char *av)
{
	int i;
	
	i = -1;
	while(av[++i])
		if (av[i] < '0' || av[i] > '9')
			return (0);
	return (1);
}

int get_parameters(char *av)
{
	if (!is_int(av))
		return (-1);
	else
		return (atoi(av));
}

t_parameters *set_parameters(t_parameters *p, int *list, char *scheduler)
{
	p = malloc(sizeof(t_parameters));
	
	p->coders = list[0];
	p->burnout = list[1];
	p->compile = list[2];
	p->debug = list[3];
	p->refactor = list[4];
	p->compiles_required = list[5];
	p->dongle_cooldown = list[6];
	p->scheduler = scheduler;
	return (p);
}

t_parameters *parser(char **av)
{
	t_parameters	*parameters;
	int				*list_parameters;
	int				i;

	list_parameters = malloc(7 * sizeof(int));
	parameters = NULL;
	i = 0;
	while (++i < 8)
	{
		list_parameters[i - 1] = get_parameters(av[i]);
		if (list_parameters[i - 1] < 0)
			return (free(list_parameters), parameters);
	}
	if (strcmp(av[8], "fifo") && strcmp(av[8], "edf"))
		return (free(list_parameters), parameters);
	return (set_parameters(parameters, list_parameters, av[8]));
}
