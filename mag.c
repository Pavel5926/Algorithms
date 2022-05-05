#include <stdio.h>

#define n 50

int main(void)
{
int i, A = 0 ;
int a, z, d[n];

for(i=0;i<n; i++)
{
    d[i]=0;
}
a=2;
z=0;
for(i=0; i<n; i++)
{
 
d[i] = a % 10;
z = ((a) / 10);
a = (((a % 10) * 2) + z);

if (a==2 && z==0)
{
    break;
}
}
for(i=0;i<n;i++){
    if ( ( A ) || ( d[n-i-1] ) )
    {
        printf("%i",d[n-i-1]); 
        A = 1;
    }

}

}