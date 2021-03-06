/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbladd_last.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdezaphi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:50:21 by kdezaphi          #+#    #+#             */
/*   Updated: 2014/11/27 17:55:59 by kdezaphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

void	ft_lstdbladd_last(t_list_def *def, t_list_dbl *new)
{
	t_list_dbl	*list;

	if (new)
	{
		if (!def->first)
		{
			def->last = new;
			def->first = new;
		}
		else
		{
			list = def->last;
			def->last = new;
			new->prev = list;
			list->next = new;
		}
		def->nb_elem++;
	}
}
