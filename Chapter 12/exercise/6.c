/*
Q. Rewrite the following function to use pointer arithmetic instead of array subscripting.
(In other words, eliminate the variable i and all uses of the [] operator.)

Make as few changes as possible.

int sum_array(const int a[], int n)
{
    int i, sum;

    sum = 0;
    for (i = 0; i < n; i++)
        sum += a[i];
    return sum;
}
*/


int sum_array(const int a[], int n)
{
    int sum;

    sum = 0;
    for (; n > 0; a++, n--)
        sum += *a;
    return sum;
}
