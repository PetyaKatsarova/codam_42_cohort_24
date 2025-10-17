#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * This is a recursive descent parser for arithmetic expressions with + ➕, * ✖️, parentheses (️⃣), and single-digit numbers 🔢. It validates the input ✅, checks for error cases ⚠️, and computes the result 🧮, all in a single run 🚀. It's a good learning example 📚 for building a hand-written parser in C 💻.
 */

void errorprinter(char *msg, char token)
{
	printf("%s '%c'\n", msg, token);
	exit(1);
}

int firstcheck(char *str)
{
	int c = 0, i = -1;


	if (str[0] != '(' && !isdigit(str[0]))
		errorprinter("Unexpected token", str[0]);
	while(str[++i])
	{
		if (str[i] != '(' && str[i] != ')' && str[i] != '+' && str[i] != '*' && !isdigit(str[i]))
			errorprinter("Unexpected token", str[i]);
		if ((str[i] == '+' || str[i] == '*') && (str[i + 1] == '+' || str[i + 1] == '*'))
			errorprinter("Unexpected token", str[i + 1]);
		if (isdigit(str[i]) && isdigit(str[i + 1]))
			errorprinter("Unexpected token", str[i + 1]);
		if (isdigit(str[i]) && ((str[i + 1] != '+' && str[i + 1] != '*') && (str[i - 1] != '+' && str[i - 1] != '*')))
		{
			if (isdigit(str[0]) && !str[i + 1])
				return(str[i] - 48);
			if (str[i - 1] != '(' && str[i + 1] != ')' )
				errorprinter("Unexpected token", str[i]);
		}
		if (str[i] == '(' && (str[i + 1] == '+' || str[i + 1] == '*'))
			errorprinter("Unexpected token", str[i + 1]);
		if (str[i] == ')' && (str[i - 1] == '+' || str[i - 1] == '*'))
			errorprinter("Unexpected token", str[i - 1]);
		if (str[i] == '(' && str[i + 1] == ')')
			errorprinter("Unexpected token", str[i + 1]);
		if (str[i] == '(')
			c++;
		if (str[i] == ')')
			c--;
	}
	if (c > 0)
		errorprinter("Unexpected token", '(');
	if (c < 0)
		errorprinter("Unexpected token", ')');
	if (str[i - 1] != ')' && !isdigit(str[i - 1]))
	{
		printf("Unexpected end of line\n");
		exit(1);
	}
	return(0);
}

long long makeplus(long long r, long long a, long long b, int c)
{
	if (r == 0 && c == 0)
		return(a + b);
	else
		return(r + b);
}

long long makemult(long long rm, long long a, long long b)
{
	if (rm == -1)
		return(a * b);
	else
		return(rm * b);
}

int next(char *str, int pos)
{
	while (str[pos]) 
	{
		if (str[pos] == '*')
			return (1);
		if (str[pos] == '+' || str[pos] == ')')
			return (0);
		pos++;
	}
	return (0);
}

int nextquats(char *str, int pos)
{
	int c = 0;

	while (str[pos]) 
	{
		if (str[pos] == '(')
			c++;
		if (str[pos] == ')')
			c--;
		if (c == 0)
			return(next(str, pos + 1));
		pos++;
	}
	return (0);
}

long long checkrm(long long r, long long rm)
{
	if (rm != -1)
	{
		if (r == 0)
			r = rm;
		else
			r += rm;
	}
	return (r);
}

long long calcinside(char *str, int pos)
{
	static int i, flagr = 0;
	long long r = 0, rm = -1, rc = 0, a = 0;
	int flag = 0, c = 0;

	i = pos;
	while(str[i])
	{
		if (str[i] == '(')
		{
			rc = calcinside(str, ++i);
			if (str[i] == '*')
				rm = rc;
			else
				r += rc;
		}
		if (str[i] == ')')
		{
			r = checkrm(r, rm);
			if (rm != -1)
				rm = -1;
			i++;
			if (c == 0 && r == 0)
				return (a);
			else
				return (r);
		}
		if (isdigit(str[i]))	
			a = str[i] - 48;
		if (str[i] == '*')
		{
			if (str[i - 1] == ')' && str[i + 1] == '(')
			{	
				if (rm == -1)
				{
					a = r;
					r = 0;
				}
				rm = makemult(rm, a, calcinside(str, i + 2));
				flag = 1;
			}
			else if (isdigit(str[i - 1]) && str[i + 1] == '(')
			{
				flagr = 2;
				rm = makemult(rm, a, calcinside(str, i + 2));
				flag = 1;
			}
			else if (isdigit(str[i - 1]) && isdigit(str[i + 1]))
				rm = makemult(rm, a, str[i + 1] - 48);
			else if (str[i - 1] == ')' && isdigit(str[i + 1]))
			{
				if (rm == -1)
				{
					a = r;
					r = 0;
				}
				rm = makemult(rm, a, str[i + 1] - 48);
			}
			c++;
		}
		if (str[i] == '+')
		{
			flag = 0;
			r = checkrm(r, rm);
			if (rm != -1)
				rm = -1;
			if (flagr == 1)
			{
				flagr = 0;
				i--;
				return(r);
			} 
			if (str[i - 1] == ')' && str[i + 1] == '(')
			{	
				if (!nextquats(str, i + 1))
				{
					r = makeplus(r, a, calcinside(str, i + 2), c);
					flag = 1;
				}
				else
					r = makeplus(r, a, 0, c);
			}
			else if (isdigit(str[i - 1]) && str[i + 1] == '(')
			{
				if (!nextquats(str, i + 1))
				{
					r = makeplus(r, a, calcinside(str, i + 2), c);
					flag = 1;
				}
				else 
					r = makeplus(r, a, 0, c);
			}
			else if (isdigit(str[i - 1]) && isdigit(str[i + 1]))
			{
				if (!next(str, i + 1))
					r = makeplus(r, a, str[i + 1] - 48, c);
				else
				{
					flagr = 1;
					r = makeplus(r, a, calcinside(str, ++i), c);
				}
			}
			else if (str[i - 1] == ')' && isdigit(str[i + 1]))
			{
				if (!next(str, i + 1))
					r = makeplus(r, a, str[i + 1] - 48, c);
				else
				{
					flagr = 1;
					r = makeplus(r, a, calcinside(str, ++i), c);
				}
			}
			c++;
		}
		if (flag == 1)
			flag = 0;
		else
			i++;
	}
	r = checkrm(r, rm);
	if (rm != -1)
		rm = -1;
	return(r);
}

int main(int gc, char **gv)
{	
	int r;

	if (gc != 2 || !gv[1][0])
		exit(1);
	r = firstcheck(gv[1]);
	if (r > 0)
	{
		printf("%d\n", r);
		return(0);
	}
	printf("%lld\n", calcinside(gv[1], 0));
	return(0);
}