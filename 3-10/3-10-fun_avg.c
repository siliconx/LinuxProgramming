/*3-10-fun_avg.c ����fun_avg �����Ķ���*/
float fun_avg(int var[],int num) /*�Զ��庯�������㷵������Ԫ�ص�ƽ��ֵ*/
{
float avrg=0.0;
int i; 
for(i=0;i<num;i++)
avrg+=var[i];
avrg/=num;
return (avrg);
} 