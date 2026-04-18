/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:04:44 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/18 14:28:38 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_int(char *av)
{
	int	i;

	if (strlen(av) > 10)
		return (0);
	i = -1;
	while (av[++i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		if (i == 9 && (av[0] > '2' || atoi(av) < 0))
			return (0);
	}
	return (1);
}

int	get_parameters(char *av)
{
	if (!is_int(av))
		return (-1);
	else
		return (atoi(av));
}

t_parameters	*set_parameters(t_parameters *p, int *list, char *scheduler)
{
	p = malloc(sizeof(t_parameters));
	if (!p)
		return (free(list), NULL);
	p->no_coders = list[0];
	p->burnout = list[1];
	p->compile = list[2];
	p->debug = list[3];
	p->refactor = list[4];
	p->compiles_required = list[5];
	p->dongle_cooldown = list[6];
	p->scheduler = scheduler;
	p->coders = malloc(p->no_coders * sizeof(pthread_t));
	if (!p->coders)
		return (free(list), NULL);
	p->dongles = malloc(p->no_coders * sizeof(pthread_mutex_t));
	if (!p->dongles)
		return (free(list), free(p->coders), NULL);
	return (free(list), p);
}

t_parameters	*parser(char **av)
{
	t_parameters	*parameters;
	int				*list_parameters;
	int				i;

	parameters = NULL;
	list_parameters = malloc(7 * sizeof(int));
	if (!list_parameters)
		return (NULL);
	i = 0;
	while (++i < 8)
	{
		list_parameters[i - 1] = get_parameters(av[i]);
		if (list_parameters[i - 1] <= 0)
			return (free(list_parameters), NULL);
	}
	if (strcmp(av[8], "fifo") && strcmp(av[8], "edf"))
		return (free(list_parameters), NULL);
	return (set_parameters(parameters, list_parameters, av[8]));
}
