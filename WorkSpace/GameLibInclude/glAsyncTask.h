
#pragma once

#include "glRefCounter.h"

//
// @brief 异步任务接口类
// @desc
// 所有需要放置于后台的处理操作，都可以继承自该类后，通过 glAsyncTaskQueue
// 类进行调度，配合 glAsyncTaskCompleteCallback 接口以获取异步任务完成信息
// 在最佳实践中，不建议直接保存 glAsyncTaskCompleteCallback 接口实例，而是将
// glAsyncTaskCompleteCallback 接口实例存放于 glAsyncTaskCompleteCallbackResourcePool
// 之中，有需要的时候，再从 glAsyncTaskCompleteCallbackResourcePool 取出来使用
// 比如：
//
// class MyTask : public glAsyncTask {
// public:
//     MyTask(const int callbackID) {
//         mCallbackID = callbackID;
//     }
// public:
//     void onAsyncTaskRun(void) override {
//         // 在这里处理异步任务
//         // ...
//         // 异步任务处理完毕，执行完成回调
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
//         // 将异步任务完成回调实例从资源池中移除
//         glAsyncTaskCompleteCallbackResourcePool::markResourceUnuse(
//             this);
//     }
// public:
//     void onAsyncTaskComplete(void) override {
//         // 在这里处理异步任务完成回调
//     }
// };
//
// int main(int argc, char * argv[]) {
//     //
//     // 异步任务完成回调实例 id
//     //
//     int callbackID = 0;
//     //
//     // 创建异步任务完成回调实例
//     //
//     MyCompleteCallback * callback = new MyCompleteCallback();
//     //
//     // 将异步任务完成回调实例存放于资源池，并获取对应的 id
//     //
//     glAsyncTaskCompleteCallbackResourcePool::insertResource(
//         callback,
//         callbackID);
//     //
//     // 创建异步任务，并将异步任务完成回调实例 id 传递给异步任务
//     //
//     MyTask * task = new MyTask(callbackID);
//     //
//     // 将异步任务投入到任务队列中，等待被调度，并释放对其引用
//     //
//     glAsyncTaskQueue::postTask(task);
//     task->release();
//     //
//     // 在随后的任何时刻，你都可以销毁 callback 对象，task 对象不会受到任何影响
//     // 如果 callback 对象在 task 对象完成异步任务之前被销毁，则 task 对象会拿不到
//     // callback 对象，而无法执行完成回调，这正是我们所预期的良好结果
//     // 如果 callback 对象在 task 对象完成异步任务之后被销毁，则 task 对象可以拿到
//     // callback 对象，并执行完成回调，这正是我们所预期的最佳结果
//     //
//     return 0;
// }
//
// 这东西为什么要写得这么复杂呢？是因为在我个人过往的项目当中，曾经遇到这么一个问题：
//
// task 对象持有 callback 对象指针，在 task 完成之前，callback 对象就已经被 delete 掉了，
// 随后 task 调用之前拿到的 callback 对象（此时已经被销毁掉）进行调用的时候，程序就 crash 掉了。
//
// 所以，在这个版本中，我引入了一个中间人 resource pool，callback 是放置在 resource pool
// 里面的，并且有一个独一无二的 id 指向 resource pool 中的这个 callback，task 手持 callback
// 的 id，并且在任何时候，都可以通过这个 callback id 向 resource pool 查询对应的 callback。
//
// 由于 callback 对象自身在销毁的时候，会将自己从 resource pool 中移除掉，这样一来，task 再通过 id
// 从 resource pool 中查询 callback 的时候，就会查询失败，避免了程序 crash 的情况出现。
//
class glAsyncTask : public glRefCounter {
public:
	//
	// @brief 处理异步任务逻辑
	//
	virtual void onAsyncTaskRun(void) = 0;
};
