//
//   File name      : Main.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : DigitalDFS
//
//   Create datetime: 2013-02-22 19:01:07
//

// Tested or implemented header
// ...

// C system headers
#include <stdio.h>
#include <math.h>
#include <string.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

int total_solution_count = 0;

void DFS(int number, int left_count, int target, char op_stack[], int op_count);
double Calculate(int number, char op_stack[], int op_count); // count of number is stack_len + 1
double CalculateTimeDivide(int number, char op_stack[], int op_count, int *ret_op_used_count);
void Print(int number, int target, char op_stack[], int stack_len);

int main()
{
    int number = 0;
    int count  = 0;
    int target = 0;
    char op_stack[128];

    while (1)
    {
        printf("输入数字，数字个数及期待的答案。输入3个0退出程序。\n");
        scanf("%d%d%d", &number, &count, &target);
        if (
            (0 == number) &&
            (0 == count) &&
            (0 == target)
            )
        {
            break;
        }

        total_solution_count = 0;
        if (0 == count)
        {
            continue;
        }
        DFS(number, count - 1, target, op_stack, 0);
        printf("找到了 %d 个答案。\n", total_solution_count);
    }

    return 0;
}

void DFS(int number, int left_count, int target, char op_stack[], int op_count)
{
    static char oplist[] = "+-*/";
    int i;
    if (0 == left_count)
    {
        if (fabs(target - Calculate(number, op_stack, op_count) ) < 0.0000001)
        {
            total_solution_count++;
            Print(number, target, op_stack, op_count);
        }
        return;
    }

    for (i = 0; i < strlen(oplist); i++)
    {
        op_stack[op_count] = oplist[i];
        DFS(number, left_count - 1, target, op_stack, op_count + 1);
    }

    return;
}

double Calculate(int number, char op_stack[], int op_count)
{
    int count = op_count + 1;
    int op_used_count = 0;

    double result = CalculateTimeDivide(number, op_stack, op_count, &op_used_count);

    int i;

    for (i = op_used_count; i < op_count; i++)
    {
        switch (op_stack[i])
        {
        case '+':
            result += CalculateTimeDivide(number, op_stack + i + 1, op_count - i - 1, &op_used_count);
            i += op_used_count;
            break;
        case '-':
            result -= CalculateTimeDivide(number, op_stack + i + 1, op_count - i - 1, &op_used_count);
            i += op_used_count;
            break;
        default:
            return 0.0; // 这行不可能执行。
        }
    }

    return result;
}

double CalculateTimeDivide(int number, char op_stack[], int op_count, int *ret_op_used_count)
{
    double result = number;
    int i;

    *ret_op_used_count = 0;

    for (i = 0; i < op_count; i++)
    {
        if ('*' == op_stack[i])
        {
            result *= number;
            (*ret_op_used_count)++;
        }
        else if ('/' == op_stack[i])
        {
            result /= number;
            (*ret_op_used_count)++;
        }
        else
        {
            break;
        }
    }

    return result;
}

void Print(int number, int target, char op_stack[], int stack_len)
{
    int i;
    printf("(%d) ", total_solution_count);
    for (i = 0; i < stack_len; i++)
    {
        printf("%d %c ", number, op_stack[i]);
    }
    printf("%d = %d\n", number, target);
    return;
}
