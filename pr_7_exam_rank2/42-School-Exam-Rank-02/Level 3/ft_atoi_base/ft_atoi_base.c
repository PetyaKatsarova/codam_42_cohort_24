#include <stdio.h>

char to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

int get_digit(char c, int str_base)
{
	int max_digit;

	if (str_base <= 10)
		max_digit = str_base - 1 + '0';
	else
		max_digit = str_base - 10 - 1 + 'a';

	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

int ft_atoi_base(const char *str, int str_base)
{
	int result = 0;
	int sign = 1;
	int digit;

	if (str == NULL || str_base < 2 || str_base > 16)
		return 0;

	if (*str == '-')
	{
		sign = -1;
		++str;
	}

	while (*str)
	{
		digit = get_digit(to_lower(*str), str_base);
		if (digit == -1)
			break;
		result = result * str_base + digit;
		++str;
	}
	return (result * sign);
}

int main()
{
	int num = ft_atoi_base("10222", 8);
	printf("octal 4242[10222] is: %o\n", num);

	num = ft_atoi_base("4242", 10);
	printf("decimal 4242 is: %d\n", num);

	num = ft_atoi_base("AF42", 16);
	printf("hex for 44866[AF42] is: %X\n", num);

	return (0);
}