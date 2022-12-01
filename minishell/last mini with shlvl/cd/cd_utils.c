/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 01:22:27 by ylambark          #+#    #+#             */
/*   Updated: 2022/12/01 01:22:28 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_dir_change_in_env(t_all_env *env, char *cwd, char *owd)
{
	t_env_one_element	*elem;

	elem = search_element_struct_env(env, "PWD");
	if (!elem)
		return ;
	elem->value = ft_strdup(cwd);
	elem = search_element_struct_env(env, "OLDPWD");
	if (!elem)
		return ;
	elem->value = ft_strdup(owd);
}
