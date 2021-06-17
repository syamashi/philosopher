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
