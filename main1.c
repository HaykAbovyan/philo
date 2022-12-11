#include <stdio.h>

int main()
{
	int i;
	i = 4;
	while (--i >= 0)
	{
		printf("%d ", i);
		printf("%d\n", (i + 1) % 4);
	}
}