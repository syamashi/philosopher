/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syamashi <syamashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:28:08 by syamashi          #+#    #+#             */
/*   Updated: 2021/06/17 11:42:18 by syamashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	intlen(long n)
{
	int len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n = -n;
		++len;
	}
	++len;
	while (n /= 10)
		++len;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	m;
	int		i;

	len = intlen(n);
	str = (char*)malloc(len + 1);
	if (!str)
		return (NULL);
	m = n;
	if (n < 0)
	{
		str[0] = '-';
		m = -m;
	}
	i = len - 1;
	str[i] = m % 10 + '0';
	while (m /= 10)
		str[--i] = m % 10 + '0';
	str[len] = '\0';
	return (str);
}

static size_t	ft_strlen(const char *s)
{
	size_t	n;

	if (!s)
		return (0);
	n = 0;
	while (*s++ != '\0')
		n++;
	return (n);
}

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		ssz;
	int		n;

	if (!str)
		return (NULL);
	ssz = ft_strlen(str);
	copy = malloc(sizeof(char) * (ssz + 1))
	if (!copy)
		return (NULL);
	n = 0;
	while (*str)
		copy[n++] = *str++;
	copy[n] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*src;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	src = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!src)
		return (NULL);
	i = 0;
	while (*s1)
		src[i++] = *s1++;
	j = 0;
	while (*s2)
		src[i + j++] = *s2++;
	src[i + j] = '\0';
	return (src);
}
