/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dansimoe <dansimoe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:20:26 by dansimoe          #+#    #+#             */
/*   Updated: 2026/04/18 16:28:55 by dansimoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *coders)
{
	int	coder_id;
	int compiles;
	
	compiles = 0;
	coder_id = ((t_coder *) coders)->code_id;
	while (compiles < ((t_coder *) coders)->parameters->compiles_required)
	{
		compile((t_coder *) coders, coder_id);
		debug((t_coder *) coders, coder_id);
		refactor((t_coder *) coders, coder_id);
		compiles++;
	}
	return (NULL);
}
