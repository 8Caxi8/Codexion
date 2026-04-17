/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:09:52 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/17 20:45:13 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_parameters
{
	pthread_t		*coders;
	pthread_mutex_t	*dongles;
	int				no_coders;
	int				burnout;
	int				compile;
	int				debug;
	int				refactor;
	int				compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
}					t_parameters;

int				err_message(int i);
t_parameters	*parser(char **av);
void			print_parameters(t_parameters *parameters);
void			start_simulation(t_parameters *p);
void			free_p(t_parameters *p);
void			*routine();

#endif
