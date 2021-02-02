#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int main()
{
	int k;
	k = ft_printf("%.p\n", "123");
	ft_printf("%d\n", k);
	k = printf("%.p\n", "123");
	printf("%d\n", k);
}
