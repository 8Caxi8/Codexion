/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:09:52 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/20 16:04:22 by dansimoe         ###   ########.fr       */
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
	pthread_t		*dongles;
	pthread_t		monitor;
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
	int				stop;
	int				finished_coders;
}					t_parameters;

typedef struct s_coder
{
	t_parameters	*parameters;
	struct timeval	start_time;
	int				code_id;
	long			last_compile;
}					t_coder;

//coders_actions.c
void			release_dongle(t_coder *coders, int dongle);
void			take_dongle(t_coder *coders, int dongle, int coder_id);
void			debug(t_coder *coders, int coder_id);
void			refactor(t_coder *coders, int coder_id);
void			compile(t_coder *coders, int coder_id);
//coders.c
void			wait_to_compile(t_coder *coders, int coder_id);
void			coder_write(long time, int id, const char *message, pthread_mutex_t *logging);
//codexion_helper.c
long			get_time_ms(struct timeval start);
//err.c
int				err_message(int i);
//initiators.c
void			init_parameters(t_parameters *p, int *list, const char *scheduler);
void			init_dongle_state(t_parameters *p);
int				init_coders(t_parameters *p);
//memory.c
t_parameters	*alloc_parameters(t_parameters *p, int *list, const char *scheduler);
t_coder			**alloc_coders(t_parameters *p, int size);
void			free_aloc_coders(t_coder **coders, int size);
void			free_p(t_parameters *p);
void			thread_destroy(t_parameters *p);
//parser.c
int				is_int(char *av);
int				get_parameters(char *av);
t_parameters	*parser(char **av);
//routines.c
void			*routine(void *arg);
void			*dongle_routine(void *arg);
void			*monitor_routine(void *arg);
//simulation.c
void			start_simulation(t_parameters *p);

#endif
