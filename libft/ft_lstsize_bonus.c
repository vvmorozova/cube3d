/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsarai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:01:27 by bsarai            #+#    #+#             */
/*   Updated: 2022/06/29 10:01:28 by bsarai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// int	main()
// {
// 	t_list * l =  NULL;
// 	ft_lstadd_front(&l, ft_lstnew((void*)1));
// 	printf("%p\n", l->content);
// 	printf("%d\n", ft_lstsize(l));

// }
