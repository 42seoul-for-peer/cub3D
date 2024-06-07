/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeunkim <hyeunkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:05:43 by hyeunkim          #+#    #+#             */
/*   Updated: 2023/10/26 20:52:08 by hyeunkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while ((8 < *str && *str < 14) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return ((int) num * sign);
}

// C에서는 무적캐스트가 발생
// long long을 넘어갔을 때 atoi 원본함수가 하는 행동이 있다
//
// overflow가 날 뿐이지 계속 곱해나가니까 핸들링이 안되있음
// 수정하는 게 나을 것 같다
//
// 최소한 int 범위를 넘어서는 순간에 대해 체크하는 게 필요
//
// 어떤 운영체제에서는 longlong이 int보다 크지 않을 수 있음
// undefined behavior라서 체크할 의무는 없지만, 이상태라면 문제가 생겼는지 알 수없다
