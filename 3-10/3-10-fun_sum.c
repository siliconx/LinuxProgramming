/*3-10-fun_sum.c ����fun_sum �����Ķ���*/
float fun_sum(int var[],int num) /*�Զ��庯�������㷵������Ԫ�ص�ƽ��ֵ*/
{
float avrg=0.0;
int i;
for(i=0;i<num;i++)
avrg+=var[i];
return (avrg);
}
