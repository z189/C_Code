#pragma once
#include "vector.h"
#include <assert.h>
//创建顺序表
//初始化
//参数: 长度(用作计算开辟内存的大小)
Vector InitVector(int n)
{
    Vector vector;
    //创建一个空的表,动态申请储存
    vector.pV = (int*)malloc(sizeof(int) * n);
    //判断: 如果申请失败
    if (!vector.pV)
    {
        printf("内存申请失败!\n");
        //申请失败,退出程序,异常代码:-1
        exit(-1);
    }
    vector.size = 0;
    vector.capacity = n;
    return vector;
}
//扩容顺序表
//扩容
//参数: 表指针 容量
Vector* CheckCapacityVector(Vector* pVector)
{
    //1.判断是否有储存空间
    //2.如果不够 就扩容
    if (pVector->capacity <= pVector->size)
    {
        //1.记录原来的内存
        int* ptemp = pVector->pV;
        //2.申请新的内存
        pVector->pV = (int*)calloc(sizeof(int), pVector->capacity *= 2);
        if (!pVector->pV)
        {
            printf("内存申请失败!\n");
            //申请失败,退出程序,异常代码:-1
            exit(-1);
        }
        //拷贝
        for (int i = 0; i < pVector->size; i++)
        {
            pVector->pV[i] = ptemp[i];
        }
        //释放
        free(ptemp);
        ptemp = NULL;
    }
    //返回表指针
    return pVector;
}
//尾部插入元素
//增
//参数: 表指针 数值
Vector* PushBackVector(Vector* pVector, int num)
{
    assert(pVector != NULL);
    //判断是否有储存空间
    CheckCapacityVector(pVector);
    //插入
    pVector->pV[pVector->size] = num;
    pVector->size++;
    return pVector;
}
//任意位置插入元素
//插入
//参数: 表指针 数值 位置
Vector* InsertVector(Vector* pVector, int num, int pos)
{
    assert(pVector != NULL);
    //判断操作是否存在问题
    if (pos >= pVector->size || pos < 0)
    {
        return pVector;
    }
    //判断是否有储存空间
    CheckCapacityVector(pVector);
    //插入
    //1后移
    for (int i = pVector->size; i >= pos; i--)
    {
        pVector->pV[i + 1] = pVector->pV[i];
    }
    //2.插入
    pVector->pV[pos] = num;
    pVector->size++;
    return pVector;
}
//释放表
//释放
//参数 表
void DestoryVector(Vector temp)
{
    free(temp.pV);
    temp.pV = NULL;
}
//查找元素
//查找
//参数: 表 数值
int FindWithVector(Vector* pVector, int num)
{
    assert(pVector != NULL);
    for (int i = 0; i < pVector->size; i++)
    {
        if (num == pVector->pV[i])
        {
            //如果找到了返回坐标点
            return i;
        }
    }
    //如果没有找到返回-1
    return -1;
}
//删除坐标的元素
//删除
//参数: 表指针 坐标
Vector* DelPosVector(Vector* pVector, int pos)
{
    assert(pVector != NULL);
    //判断删除的位置是否正确
    if (pos >= pVector->size || pos < 0)
    {
        printf("删除的位置不对!");
        exit(-1);
    }
    //删除
    for (int i = pos; i < pVector->size; i++)
    {
        pVector->pV[i] = pVector->pV[i + 1];
    }
    pVector->size--;
    return pVector;
}
//删除尾部的元素
//删除
//参数: 表指针
Vector* PopBackVector(Vector* pVector)
{
    assert(pVector != NULL);
    DelPosVector(pVector, pVector->size);
    return pVector;
}
