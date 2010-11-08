#include "stdafx.h"
#include <memory>
#include <iostream>
#include <stdio.h>

#include "scope_guard.h"

using namespace std;
using namespace utility::guard;

// closeIt�̳� freeIt�� Dissmiss�� ȣ������ ������  scope_guard�� destructor��
// ȣ�� transaction�� commit�� ȿ���� �������� �������� Dismiss�� ȣ���Ѵ�.
// ���� �������� �ڵ����� �޸𸮸� �����ϰ� ������ ON_BLOCK_EXIT(Obj)��ũ�θ�
// ����Ѵ�.
// 
// Dissmiss == Commit <---> Rollback
void test()
{
   void* buffer = malloc(1024);
   scope_guard freeIt = make_guard(free, buffer);

   FILE* topSecret = fopen("cia.txt", "rw");
   scope_guard closeIt = make_guard(fclose, topSecret);
}

/*
void decrement(int& x)
{
	--x;
}

void useResource(int &refCount)
{
	++refCount;
	scope_guard guard = make_guard(decrement, ByRef(refCount));

	cout << "1" <<  refCount << endl;
}
*/

// ��ü�� ����Լ��� ����� ���.
// friends_.push_back(&newFriend);
// scope_guard guard = MakeObjGuard(friends_, &UserCont::pop_back);
//    

int main()
{
    test();
	int refCount = 1;
	// useResource(refCount);
 
    return 0;
}