/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:42:59 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/17 16:05:21 by dansimoe         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_parameters
{
	int			coders;
	int			burnout;
	int			compile;
	int			debug;
	int			refactor;
	int			compiles_required;
	int			dongle_cooldown;
	char		*scheduler;
}				t_parameters;

int				err_message(int i);
t_parameters	*parser(char **av);
void 			print_parameters(t_parameters *parameters);

#endif
