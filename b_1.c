#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>			

#define STACK_MAX_SIZE 1024

typedef struct Set
{
	int *arr;
	size_t N;
} Set;

typedef struct Prior
{
	char ch;
	int N;
	int priority;
} Prior;

typedef struct Stack
{
	int data[STACK_MAX_SIZE];
	size_t size;
} Stack;

int str_to_int(char *);
int *my_sort(int *, size_t);
int is_all_right(char *);
void push(Stack *, int);
int pop(Stack *);
void get_all_sizes(Set *, int , char *);
void modify_array(Set *, int , Stack *);
void get_priorities(Prior *, int , char *);
void swap_struct_1(Set *, int , int);
void swap_struct_2(Prior *, int , int );

void swap_struct_1(Set *a, int i, int j)
{	
	int *temp_1 = NULL;
	int *temp_2 = NULL;
	int p = 0;
	int k = 0;
	size_t temp = 0;
	
	temp_1 = (int *)malloc(a[i].N * sizeof(int));
	temp_2 = (int *)malloc(a[j].N * sizeof(int));
	
	for(p = 0; p < a[i].N; p++)
		temp_1[p] = a[i].arr[p];
	for(k = 0; k < a[j].N; k++)
		temp_2[k] = a[j].arr[k];
	
	a[i].arr = realloc(a[i].arr, a[j].N * sizeof(int));
	a[j].arr = realloc(a[j].arr, a[i].N * sizeof(int));
	
	temp = a[i].N;
	a[i].N = a[j].N;
	a[j].N = temp;
	
	for(p = 0; p < a[i].N; p++)
		a[i].arr[p] = temp_2[p];
	for(k = 0; k < a[j].N; k++)
		a[j].arr[k] = temp_1[k];
		
	free(temp_1);
	free(temp_2);
	
	return;
}

void swap_struct_2(Prior *a, int i, int j)
{
	char temp_1 = a[i].ch;
	a[i].ch = a[j].ch;
	a[j].ch = temp_1;
	
	int temp_2 = a[i].N;
	a[i].N = a[j].N;
	a[j].N = temp_2;
	
	int temp_3 = a[i].priority;
	a[i].priority = a[j].priority;
	a[j].priority = temp_3;
	
	return;
}

void push(Stack *stack, int value)
{
	stack->data[stack->size] = value;
	stack->size++;
}

int pop(Stack *stack)
{
	stack->size--;
	return stack->data[stack->size];
}

void get_priorities(Prior *prior, int n, char *str_1)
{
	int q = 0;
	int r = 0;
	int l = 0;
	int i = 0;
	int k = 0;
	
	q = -1;
	
	for(i = 0; i < strlen(str_1); i++)
	{
		if(str_1[i] == '\\' || str_1[i] == 'U' || str_1[i] == '^')
		{
			r = 0;
			l = 0;
			q++;
			prior[q].ch = str_1[i];
			prior[q].N = q;
			if(str_1[i] == '\\')
			{
				prior[q].priority = 1;
				for(k = 0; k < i; k++)
				{
					if(str_1[k] == '(')
						l++;
					if(str_1[k] == ')')
						r++;
				}
				prior[q].priority = prior[q].priority + 2*(l - r);
			}
			if(str_1[i] == 'U')
			{
				prior[q].priority = 1;
				for(k = 0; k < i; k++)
				{
					if(str_1[k] == '(')
						l++;
					if(str_1[k] == ')')
						r++;
				}
				prior[q].priority = prior[q].priority + 2*(l - r);
			}
			if(str_1[i] == '^')
			{
				prior[q].priority = 2;
				for(k = 0; k < i; k++)
				{
					if(str_1[k] == '(')
						l++;
					if(str_1[k] == ')')
						r++;
				}
				prior[q].priority = prior[q].priority + 2*(l - r);
			}
		}
		if(q == (n - 2))
			break;
	}
	
	return;
}

void get_all_sizes(Set *sets, int n, char *str_1)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int q = 0;
	
	q = -1;
	
	for(i = 0; i < strlen(str_1); i++)
	{
		if(str_1[i] == '[')
		{
			q++;
			for(j = i + 1; j < strlen(str_1); j++)
			{
				if(str_1[j] == ']')
					break;
				
				if(str_1[j] == ',')
					k++;
			}
			
			sets[q].N = (size_t)(k + 1);
			
			if(str_1[i+1] == ']')
				sets[q].N = (size_t)(0);
				
			k = 0;
		}
		if(q == (n-1))
			break;
	}
	
	return;
}

void modify_array(Set *sets, int k, Stack *stack)
{
	int m = 0;
	int i = 0;
	int j = 0;
	
	stack->size = 0;
	m = 0;
		
	for(i = 0; i < sets[k].N; i++)
	{
		for(j = i + 1; j < sets[k].N; j++)
		{
			if(sets[k].arr[i] != sets[k].arr[j])
				m++;
		}
			
		if(i > 0)
		{
			for(j = 0; j < i; j++)
			{
				if(sets[k].arr[i] != sets[k].arr[j]);
					m++;
			}
		}
			
		if(m == (sets[k].N - 1))
			push(stack, sets[k].arr[i]);
		m = 0;
	}
		
	sets[k].N = stack->size;
	sets[k].arr = realloc(sets[k].arr, sets[k].N * sizeof(int));
		
	for(i = 0; i < sets[k].N; i++)
		sets[k].arr[i] = pop(stack);
		
	return;
}


int *my_sort(int *arr, size_t n)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	
	for(i = 0; i < n - 1; i++)
	{
		for(j = 0; j < n - i - 1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	
	return arr;
}

int str_to_int(char *str)
{
	int i = 0;
	int res = 0;
	
	if(str[0] == '0')
		return 0;
	
	for(i = 0; i < strlen(str); i++)
	{
		res *= 10;
		res += (str[i] - '0'); 
	}
	
	return res;
}

int is_all_right(char *s)
{
	int i = 0;
	
	for(i = 0; i < strlen(s); i++)
	{
		if((s[i]>'9' || s[i]<'0') && s[i]!=',' && s[i]!='(' && s[i]!=')' && s[i]!='[' && s[i]!=']' && s[i]!='U' && s[i]!='^' && s[i]!='\\')
		{
			return 0;
		}
	}
	
	int k = 0;
	int l = 0;
	int j = 0;
	int q = 0;
	i = 0;
	
	for(q = 0; q < strlen(s); q++)
	{
		if(s[q] == '[')
			i++;
			
		if(s[q] == ']')
			j++;
			
		if(s[q] == '(')
			k++;
			
		if(s[q] == ')')
			l++;	
	}
	
	int p = 0;
	int m = 0;
	
	for(p = 0; p < strlen(s); p++)
	{
		if(s[p] == '\\' || s[p] == 'U' || s[p] == '^')
			m++;
	}
	
	if(m != (i - 1))
	{
		return 0;
	}
	
	if(i == 0 || j == 0)
	{
		return 0;
	}
	
	if(i != j)
	{
		return 0;
	}
	
	if((k > 0 || l > 0) && k != l)
	{
		return 0;
	}
	
	i = 0;
	k = 0;
	l = 0;
	j = 0;
	q = 0;
	
	for(i = 0; i < strlen(s); i++)
	{
		if(s[i] == '[')
		{
			for(j = i + 1; j < strlen(s); j++)
			{
				if(s[j] == '[')
				{
					for(k = i + 1; k < j; k++)
					{
						if(s[k] == ']')
							q++;
					}
					if(q != 1)
					{
						return 0;
					}
					q = 0;
					break;
				}
			}
		}
	}
	
	i = 0;
	k = 0;
	l = 0;
	j = 0;
	q = 0;
	
	for(i = 0; i < strlen(s); i++)
	{
		if(s[i] == ']')
		{
			for(j = 0; j < i; j++)
			{
				if(s[j] == '[')
					k++;
			}
			if(k != 1)
			{
				return 0;
			}
			k = 0;
			break;
		}
	}
	
	i = 0;
	k = 0;
	l = 0;
	j = 0;
	q = 0;
	
	for(i = 0; i < strlen(s); i++)
	{
		if(s[i] == ')')
		{
			for(j = 0; j < i; j++)
			{
				if(s[j] == '(')
					k++;
			}
			if(!k)
			{
				return 0;
			}
			break;
		}
	}
	
	i = 0;
	k = 0;
	l = 0;
	j = 0;
	q = 0;
	
	if((s[0] != '[' && s[0] != '(') || (s[strlen(s) - 1] != ']' && s[strlen(s) - 1] != ')'))
	{
		return 0;
	}
	
	for(i = 0; i < strlen(s); i++)
	{
		if(s[i] == '[')
		{
			for(j = i + 1; j < strlen(s); j++)
			{
				if(s[j] == ']')
				{
					for(k = i; k < j; k++)
					{
						if(s[k] == '\\' || s[k] == '^' || s[k] == 'U' || s[k] == '(' || s[k] == ')')
							return 0;
					}
					break;
				}
			}
		}
	}
	
	return 1;
}

int main()
{
	char str[2048] = "";
	char str_1[2048] = "";
	int i = 0;
	
	fgets(str, 2048, stdin);
	
	int q = 0;
	
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] != ' ' && str[i] != '\n' && str[i] != '\0' && str[i] != EOF && str[i] != '\t')
		{
			str_1[q] = str[i];
			q++;
		}
	}
	
	q = 0;
	
	q = is_all_right(str_1);
	
	if(!q)
	{
		printf("[error]");
		return 0;
	}
	
	int n = 0;
	int j = 0;
	char num[2048] = "";
	
	for(i = 0; i < strlen(str_1); i++)
	{
		if(str_1[i] == '[')
			j++;
	}
	
	n = j;
	j = 0;
	i = 0;
	int l = 0;
	int m = 0;
	int k = 0;
	
	Stack *stack = NULL;
	stack = (Stack*)malloc(sizeof(Stack));
	if(stack == NULL)
	{
		printf("[error]");
		return 0;
	}
	
	Set *sets = NULL;
	sets = (Set*) malloc(n * sizeof(Set));
	if(sets == NULL)
	{
		printf("[error]");
		free(stack);
		return 0;
	}
	
	get_all_sizes(sets, n, str_1);
	
	for(i = 0; i < n; i++)
	{
		sets[i].arr = NULL;
		sets[i].arr = (int *)malloc(sets[i].N * sizeof(int));
		
		if(sets[i].arr == NULL && (i == 0))
		{
			if(sets[i].N == 0)
				continue;
			free(sets);
			free(stack);
			printf("[error]");
			return 0;
		}
		
		if(sets[i].arr == NULL && (i > 0))
		{
			if(sets[i].N == 0)
				continue;
			for(j = 0; j < i; j++)
			{
				free(sets[i].arr);
			}
			free(stack);
			free(sets);
			printf("[error]");
			return 0;
		}
	}
	
	q = -1;
	m = 0;
	l = 0;
	stack->size = 0;

	for(i = 0; i < strlen(str_1); i++)
	{
		if(str_1[i] == '[')
		{
			l = 0;
			m = 0;
			q++;
			for(j = i + 1; j < strlen(str_1); j++)
			{
				if(str_1[i+1] == ']')
					break;
				if(str_1[j] != ',' && str_1[j] != ']')
				{
					num[m] = str_1[j];
					m++;
				}
				 
				if(str_1[j] == ',' || str_1[j] == ']')
				{
					sets[q].arr[l] = str_to_int(num);
					if(sets[q].arr[l] == 0)
					{
						printf("[error]");
						for(i = 0; i < q ; i++)
						{
							free(sets[i].arr);
						}
						free(stack);
						free(sets);
						return 0;
					}
					memset(num, 0, sizeof(num));
					m = 0;
					l++;
				}
				if(str_1[j] == ']')
					break;
			}
		}
		if(q == (n - 1))
			break;
	}
	
	for(i = 0; i < n; i++)
	{
		modify_array(sets, i, stack);
	}
	
	stack->size = 0;
	
	if(n == 1)
	{	
		if(sets[0].N == 0)
		{
			printf("[]");
			free(stack);
			free(sets);
			return 0;
		}
		
		sets[0].arr = my_sort(sets[0].arr, sets[0].N);
		
		printf("[");
		for(i = 0; i < sets[0].N - 1; i++)
		{
			printf("%d,", sets[0].arr[i]);
		}
		printf("%d", sets[0].arr[sets[0].N - 1]);
		printf("]");
		
		free(sets[0].arr);
		
		free(sets);
		free(stack);
		
		return 0;
	}
	
	q = 0;
	
	Prior *prior = NULL;
	
	for(i = 0; i < strlen(str_1); i++)
	{
		if(str_1[i] == '\\' || str_1[i] == 'U' || str_1[i] == '^')
		{
			q++;
		}
	}
	
	prior = (Prior*)malloc(q * sizeof(Prior));
	
	if(prior == NULL)
	{
		printf("[error]");
		for(i = 0; i < n; i++)
		{
			free(sets[i].arr);
		}
		free(stack);
		free(sets);
		return 0;
	}
	
	get_priorities(prior, n, str_1);
	
	Stack *stack_1 = NULL;
	stack_1 = (Stack*)malloc(sizeof(Stack));
	
	if(stack_1 == NULL)
	{
		printf("[error]");
		for(i = 0; i < n; i++)
		{
			free(sets[i].arr);
		}
		free(stack);
		free(sets);
		return 0;
	}
	
	stack_1->size = 0;
	stack->size = 0;
	
	push(stack, 0);

	for(i = 1; i < n - 1; i++)
	{
		for(j = i; j > 0; j--)
		{
				if(prior[j-1].priority >= prior[i].priority)
				{
					push(stack_1, pop(stack));
				}
				else
				{
					push(stack, i);
					m = stack_1->size;
					if(m > 0)
					{
						for(q = 0; q < m; q++)
							push(stack, pop(stack_1));
					}
					break;
				}
				if(stack->size == 0)
				{
					push(stack, i);
					m = stack_1->size;
					if(m > 0)
					{
						for(q = 0; q < m; q++)
							push(stack, pop(stack_1));
					}
					break;
				}
		}
		stack_1->size = 0;
	}
	
	m = stack->size;
	
	while(stack->size > 0)
	{
		q = pop(stack);
		m = 0;
		l = 0;
		stack_1->size = 0;
		
		switch(prior[q].ch)
		{
			case 'U':
				if(sets[q].N == 0 && sets[q+1].N == 0)
				{
					sets[q].N = 0;
					sets[q+1].N = 0;
					if(stack->size == 0)
					{
						printf("[]");
						free(prior);
						free(stack_1);
						free(stack);
	
						for(i = 0; i < n ; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					for(i = 0; i < stack->size; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else if(sets[q].N == 0 && sets[q+1].N != 0)
				{
					sets[q].N = sets[q+1].N;
					sets[q].arr = realloc(sets[q].arr, sets[q].N * sizeof(int));
					for(i = 0; i < sets[q].N; i++)
						sets[q].arr[i] = sets[q+1].arr[i];
				
					sets[q].arr = my_sort(sets[q].arr, sets[q].N);
					sets[q+1].arr = my_sort(sets[q+1].arr, sets[q+1].N);
					
					if(stack->size == 0)
					{
						printf("[");
						for(i = 0; i < sets[q].N - 1; i++)
							printf("%d,", sets[q+1].arr[i]);
						printf("%d]", sets[q+1].arr[sets[q+1].N - 1]);
			
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}

						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else if(sets[q].N != 0 && sets[q+1].N == 0)
				{
					sets[q+1].N = sets[q].N;
					sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
					for(i = 0; i < sets[q+1].N; i++)
						sets[q+1].arr[i] = sets[q].arr[i];
					
					sets[q+1].arr = my_sort(sets[q+1].arr, sets[q+1].N);
					sets[q].arr = my_sort(sets[q].arr, sets[q].N);
				
					if(stack->size == 0)
					{
						printf("[");
						for(i = 0; i < sets[q+1].N - 1; i++)
							printf("%d,", sets[q+1].arr[i]);
						printf("%d]", sets[q+1].arr[sets[q+1].N - 1]);
				
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else
				{
					for(j = 0; j < sets[q].N; j++)
					{
						push(stack_1, sets[q].arr[j]);
						m++;
					}
			
					for(j = 0; j < sets[q+1].N; j++)
					{
						l = 0;
						for(k = 0; k < sets[q].N; k++)
						{
							if(sets[q+1].arr[j] != sets[q].arr[k])
								l++;
						}
				
						if(l == sets[q].N)
						{
							m++;
							push(stack_1, sets[q+1].arr[j]);
						}
						l = 0;
					}
					sets[q].N = m;
					sets[q+1].N = m;
					sets[q].arr = realloc(sets[q].arr, sets[q].N * sizeof(int));
					sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
					m = stack_1->size;
					for(j = 0; j < m; j++)
					{
						sets[q].arr[j] = pop(stack_1);
						sets[q+1].arr[j] = sets[q].arr[j];
					}
			
					sets[q].arr = my_sort(sets[q].arr, sets[q].N);
					sets[q+1].arr = my_sort(sets[q+1].arr, sets[q+1].N);
					if(stack->size == 0)
					{
						printf("[");
						for(i = 0; i < sets[q+1].N - 1; i++)
						{
							printf("%d,", sets[q+1].arr[i]);
						}
						printf("%d", sets[q+1].arr[sets[q+1].N - 1]);
						printf("]");
			
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
	
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
		
			case '\\':
				if(sets[q].N == 0 && sets[q+1].N == 0)
				{
					sets[q].N = 0;
					sets[q+1].N = 0;
					if(stack->size == 0)
					{
						printf("[]");
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else if(sets[q].N == 0 && sets[q+1].N != 0)
				{
					sets[q].N = 0;
					sets[q+1].N = 0;
					if(stack->size == 0)
					{
						printf("[]");
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else if(sets[q].N != 0 && sets[q+1].N == 0)
				{
					sets[q+1].N = sets[q].N;
					sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
					for(i = 0; i < sets[q+1].N; i++)
						sets[q+1].arr[i] = sets[q].arr[i];
					
					sets[q].arr = my_sort(sets[q].arr, sets[q].N);
					sets[q+1].arr = my_sort(sets[q+1].arr, sets[q+1].N);
				
					if(stack->size == 0)
					{
						printf("[");
						for(i = 0; i < sets[q+1].N - 1; i++)
							printf("%d,", sets[q+1].arr[i]);
						printf("%d]", sets[q+1].arr[sets[q+1].N - 1]);
				
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else
				{
					l = 0;
			
					for(j = 0; j < sets[q].N; j++)
					{
						for(k = 0; k < sets[q+1].N; k++)
						{
							if(sets[q].arr[j] != sets[q+1].arr[k])
								m++;
						}
						if(m == sets[q+1].N)
						{
							push(stack_1, sets[q].arr[j]);
							l++;
						}
						m = 0;
					}
			
					if(l == 0)
					{
						sets[q].N = 0;
						sets[q+1].N = 0;
						sets[q].arr = realloc(sets[q].arr, sets[q].N * sizeof(int));
						sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
						if(stack->size == 0)
						{
							printf("[]");
							free(stack_1);
							free(stack);
							free(prior);
	
							for(i = 0; i < n; i++)
							{
								free(sets[i].arr);
							}
	
							free(sets);
	
							return 0;
						}
						for(k = q; k < n - 1; k++)
							swap_struct_1(sets, k, k + 1);
						for(k = q; k < n - 2; k++)
							swap_struct_2(prior, k , k + 1);
						m = stack->size;
						for(i = 0; i < m; i++)
						{
							if(stack->data[i] > q)
								stack->data[i]--;
						}
						break;
					}
					else
					{
						sets[q].N = l;
						sets[q+1].N = l;
						sets[q].arr = realloc(sets[q].arr, sets[q].N * sizeof(int));
						sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
						l = stack_1->size;
						for(j = 0; j < l; j++)
						{
							sets[q].arr[j] = pop(stack_1);
							sets[q+1].arr[j] = sets[q].arr[j];
						}
			
						sets[q].arr = my_sort(sets[q].arr, sets[q].N);
						sets[q+1].arr = my_sort(sets[q+1].arr, sets[q+1].N);
						if(stack->size == 0)
						{
							printf("[");
							for(i = 0; i < sets[q+1].N - 1; i++)
							{
								printf("%d,", sets[q+1].arr[i]);
							}
							printf("%d", sets[q+1].arr[sets[q+1].N - 1]);
							printf("]");
			
							free(stack_1);
							free(stack);
							free(prior);
	
							for(i = 0; i < n; i++)
							{
								free(sets[i].arr);
							}
	
							free(sets);
	
							return 0;
						}
						for(k = q; k < n - 1; k++)
							swap_struct_1(sets, k, k + 1);
						for(k = q; k < n - 2; k++)
							swap_struct_2(prior, k , k + 1);
						m = stack->size;
						for(i = 0; i < m; i++)
						{
							if(stack->data[i] > q)
								stack->data[i]--;
						}
						break;
					}
				}
		
			case '^':
				if(sets[q].N == 0 || sets[q+1].N == 0)
				{
					sets[q].N = 0;
					sets[q+1].N = 0;
					if(stack->size == 0)
					{
						printf("[]");
						free(stack_1);
						free(stack);
						free(prior);
	
						for(i = 0; i < n; i++)
						{
							free(sets[i].arr);
						}
	
						free(sets);
						return 0;
					}
					for(k = q; k < n - 1; k++)
						swap_struct_1(sets, k, k + 1);
					for(k = q; k < n - 2; k++)
						swap_struct_2(prior, k , k + 1);
					m = stack->size;
					for(i = 0; i < m; i++)
					{
						if(stack->data[i] > q)
							stack->data[i]--;
					}
					break;
				}
				else
				{
					for(j = 0; j < sets[q].N; j++)
					{
						for(k = 0; k < sets[q+1].N; k++)
						{
							if(sets[q].arr[j] == sets[q+1].arr[k])
							{
								m++;
								push(stack_1, sets[q].arr[j]);
								break;
							}
						}
					}
			
					if(m == 0)
					{
						sets[q].N = 0;
						sets[q+1].N = 0;
						sets[q].arr = realloc(sets[q].arr, sets[q].N * sizeof(int));
						sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
						if(stack->size == 0)
						{
							printf("[]");
							free(stack_1);
							free(stack);
							free(prior);
	
							for(i = 0; i < n; i++)
							{
								free(sets[i].arr);
							}
	
							free(sets);
	
							return 0;
						}
						for(k = q; k < n - 1; k++)
							swap_struct_1(sets, k, k + 1);
						for(k = q; k < n - 2; k++)
							swap_struct_2(prior, k , k + 1);
						m = stack->size;
						for(i = 0; i < m; i++)
						{
							if(stack->data[i] > q)
								stack->data[i]--;
						}
						break;
					}
					else
					{
						sets[q].N = m;
						sets[q+1].N = m;
						sets[q].arr = realloc(sets[q].arr, sets[q].N * sizeof(int));
						sets[q+1].arr = realloc(sets[q+1].arr, sets[q+1].N * sizeof(int));
						m = stack_1->size;
						for(j = 0; j < m; j++)
						{
							sets[q].arr[j] = pop(stack_1);
							sets[q+1].arr[j] = sets[q].arr[j];
						}
			
						sets[q].arr = my_sort(sets[q].arr, sets[q].N);
						sets[q+1].arr = my_sort(sets[q+1].arr, sets[q+1].N);
						if(stack->size == 0)
						{
							printf("[");
							for(i = 0; i < sets[q+1].N - 1; i++)
							{
								printf("%d,", sets[q+1].arr[i]);
							}
							printf("%d", sets[q+1].arr[sets[q+1].N - 1]);
							printf("]");
			
							free(stack_1);
							free(stack);
							free(prior);
	
							for(i = 0; i < n; i++)
							{
								free(sets[i].arr);
							}
	
							free(sets);
	
							return 0;
						}
						for(k = q; k < n - 1; k++)
							swap_struct_1(sets, k, k + 1);
						for(k = q; k < n - 2; k++)
							swap_struct_2(prior, k , k + 1);
						m = stack->size;
						for(i = 0; i < m; i++)
						{
							if(stack->data[i] > q)
								stack->data[i]--;		
						}
						break;
					}
				}
		}
	}
	
	free(stack);
	free(prior);
	free(stack_1);
	
	for(i = 0; i < n; i++)
	{
		free(sets[i].arr);
	}
	
	free(sets);
	
	return 0;
}
