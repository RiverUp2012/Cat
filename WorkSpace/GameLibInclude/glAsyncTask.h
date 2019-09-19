
#pragma once

#include "glRefCounter.h"

//
// @brief �첽����ӿ���
// @desc
// ������Ҫ�����ں�̨�Ĵ�������������Լ̳��Ը����ͨ�� glAsyncTaskQueue
// ����е��ȣ���� glAsyncTaskCompleteCallback �ӿ��Ի�ȡ�첽���������Ϣ
// �����ʵ���У�������ֱ�ӱ��� glAsyncTaskCompleteCallback �ӿ�ʵ�������ǽ�
// glAsyncTaskCompleteCallback �ӿ�ʵ������� glAsyncTaskCompleteCallbackResourcePool
// ֮�У�����Ҫ��ʱ���ٴ� glAsyncTaskCompleteCallbackResourcePool ȡ����ʹ��
// ���磺
//
// class MyTask : public glAsyncTask {
// public:
//     MyTask(const int callbackID) {
//         mCallbackID = callbackID;
//     }
// public:
//     void onAsyncTaskRun(void) override {
//         // �����ﴦ���첽����
//         // ...
//         // �첽��������ϣ�ִ����ɻص�
//         glAsyncTaskCompleteCallback * callback = 0;
//         glAsyncTaskCompleteCallbackResourcePool::getResource(
//             mCallbackID,
//             callback,
//             true);
//         if(callback) {
//             callback->onAsyncTaskComplete();
//         }
//     }
// private:
//     int mCallbackID;
// };
//
// class MyCompleteCallback : public glAsyncTaskCompleteCallback {
// public:
//     ~MyCompleteCallback() {
//         // ���첽������ɻص�ʵ������Դ�����Ƴ�
//         glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(
//             this);
//     }
// public:
//     void onAsyncTaskComplete(void) override {
//         // �����ﴦ���첽������ɻص�
//     }
// };
//
// int main(int argc, char * argv[]) {
//     //
//     // �첽������ɻص�ʵ�� id
//     //
//     int callbackID = 0;
//     //
//     // �����첽������ɻص�ʵ��
//     //
//     MyCompleteCallback * callback = new MyCompleteCallback();
//     //
//     // ���첽������ɻص�ʵ���������Դ�أ�����ȡ��Ӧ�� id
//     //
//     glAsyncTaskCompleteCallbackResourcePool::insertResource(
//         callback,
//         callbackID);
//     //
//     // �����첽���񣬲����첽������ɻص�ʵ�� id ���ݸ��첽����
//     //
//     MyTask * task = new MyTask(callbackID);
//     //
//     // ���첽����Ͷ�뵽��������У��ȴ������ȣ����ͷŶ�������
//     //
//     glAsyncTaskQueue::postTask(task);
//     task->release();
//     //
//     // �������κ�ʱ�̣��㶼�������� callback ����task ���󲻻��ܵ��κ�Ӱ��
//     // ��� callback ������ task ��������첽����֮ǰ�����٣��� task ������ò���
//     // callback ���󣬶��޷�ִ����ɻص���������������Ԥ�ڵ����ý��
//     // ��� callback ������ task ��������첽����֮�����٣��� task ��������õ�
//     // callback ���󣬲�ִ����ɻص���������������Ԥ�ڵ���ѽ��
//     //
//     return 0;
// }
//
// �ⶫ��ΪʲôҪд����ô�����أ�����Ϊ���Ҹ��˹�������Ŀ���У�����������ôһ�����⣺
//
// task ������� callback ����ָ�룬�� task ���֮ǰ��callback ������Ѿ��� delete ���ˣ�
// ��� task ����֮ǰ�õ��� callback ���󣨴�ʱ�Ѿ������ٵ������е��õ�ʱ�򣬳���� crash ���ˡ�
//
// ���ԣ�������汾�У���������һ���м��� resource pool��callback �Ƿ����� resource pool
// ����ģ�������һ����һ�޶��� id ָ�� resource pool �е���� callback��task �ֳ� callback
// �� id���������κ�ʱ�򣬶�����ͨ����� callback id �� resource pool ��ѯ��Ӧ�� callback��
//
// ���� callback �������������ٵ�ʱ�򣬻Ὣ�Լ��� resource pool ���Ƴ���������һ����task ��ͨ�� id
// �� resource pool �в�ѯ callback ��ʱ�򣬾ͻ��ѯʧ�ܣ������˳��� crash ��������֡�
//
class glAsyncTask : public glRefCounter {
public:
	//
	// @brief �����첽�����߼�
	//
	virtual void onAsyncTaskRun(void) = 0;
};
