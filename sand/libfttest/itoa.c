#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
	while (1)
	{
		++len;
		n /= 10;
		if (!n)
			break ;
	}
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
	i = len;
	while (--i >= 0)
	{
		str[i] = m % 10 + '0';
		m /= 10;
		if (!m)
			break ;
	}
	str[len] = '\0';
	return (str);
}

int main()
{
	char *c;
	int num[] = {-10, -1, 0, 1, 9, 10, 99, 2147483647, -2147483648}; // 9

	for (int i=0; i<9; ++i){
		c = ft_itoa(num[i]);
		printf("c[%d]:%s\n", num[i], c);
		free(c);
	}
}
