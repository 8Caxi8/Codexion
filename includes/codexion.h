/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:09:52 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 11:17:06 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_parameters
{
	pthread_t		*coders;
	int				*dongle_state;
	pthread_mutex_t	table;
	pthread_cond_t	cond_table;
	pthread_mutex_t	logging;
	int				no_coders;
	int				burnout;
	int				compile;
	int				debug;
	int				refactor;
	int				compiles_required;
	int				dongle_cooldown;
	const char		*scheduler;
}					t_parameters;

typedef struct s_coder
{
	t_parameters	*parameters;
	struct timeval	start_time;
	int				code_id;
}					t_coder;

int				err_message(int i);
t_parameters	*parser(char **av);
void			print_parameters(t_parameters *parameters);
void			start_simulation(t_parameters *p);
void			free_p(t_parameters *p);
void			*routine();
void			delete_dongles(t_parameters *p);
t_coder			**alloc_coders(t_parameters *p, int size);
void			free_aloc_coders(t_coder **coders, int size);
void			take_dongle(pthread_mutex_t dongle, int coder_id);
void			compile(t_coder *coders, int coder_id);
void			debug(t_coder *coders, int coder_id);
void			refactor(t_coder *coders, int coder_id);
long			get_time_ms(struct timeval start);
void			init_parameters(t_parameters *p, int *list, const char *scheduler);
void			init_dongle_state(t_parameters *p);

#endif
