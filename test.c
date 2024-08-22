#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (const char *)src;
	if (!d || !s)
		return (NULL);
	if (s < d && d < (s + len))
	{
		d = d + len;
		s = s + len;
		while (len--)
			*--d = *--s;
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}

int main()
{
	char *test = malloc(5);
	test = "lola";
	ft_memmove(test, test + 1, 5);
}