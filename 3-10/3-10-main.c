#include <stdio.h> /*�ļ�Ԥ����������׼���������*/
#include "chengji.h" /*�ļ�Ԥ��������fun_avg ��fun_sum ��������*/
int main () /*C ���������������ʼ���*/
{
int n,i;
float average,sum;
printf("��������Ҫ��Ҫͳ�Ƶ�ѧ������");
scanf("%d",&n);
int array[n];
for(i=0;i<n;i++)
{
printf("�������%d ��ѧ���ĳɼ���",i+1);
scanf("%d",&array[i]);
}
sum=fun_sum(array,n); /*����avg ����������ֵ���ݸ�average*/
printf("�����%d ��ѧ�����ܳɼ��ǣ�%6.2f\n",n,sum);
average=fun_avg(array,n); /*����avg ����������ֵ���ݸ�average*/
printf("�����%d ��ѧ����ƽ���ɼ��ǣ�%6.2f\n",n,average);
}