/**
 * Created by Nie Tao on 2019/12/23 0023.
 * Steps:
 * (1)Install Python3.6-dev on your ubuntu18.04:
 * $ sudo apt-get install python3.6-dev
 * (2) Compile:
 * $ g++ -I/usr/include/python3.6 py_invoker.cpp -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -L/usr/lib -lpthread -lpython3.6m -o py_invoker
 * (3) Run:
 * $ ./py_invoker
 */
#include <string>
#include <Python.h>
#include <iostream>
#include <pthread.h>

using namespace std;
// The directory where you put the Python script.
#define PY_DIR "/home/topher/projects/toy-project/python/find_largest/"

class PythonThreadLocker
{
    PyGILState_STATE state;
public:
    PythonThreadLocker() : state(PyGILState_Ensure())
    {}
    ~PythonThreadLocker() {
        PyGILState_Release(state);
    }
};


PyObject *pFunc;

int init()
{
    if (pFunc == nullptr)
    {
        Py_Initialize();
        // Multi-thread support
        PyEval_InitThreads();
        cout << "[Python] Thread initialized: " << PyEval_ThreadsInitialized() << endl;

        // Import this working directory
        PyRun_SimpleString("import sys");
        string append_str = "sys.path.append('";
        append_str.append(PY_DIR).append("')");
        PyRun_SimpleString(append_str.c_str());

        // Import python module.
        PyObject *pModule = PyImport_ImportModule("hand_highlight");
        if (pModule == nullptr)
        {
            cout << "ERROR importing module!" << endl;
            exit(-1);
        }
        // Get a function of the module.
        pFunc = PyObject_GetAttrString(pModule, "cal_score_to_hot_encoding_str");
        if (pFunc == nullptr)
        {
            cout << "ERROR getting function!" << endl;
            exit(-1);
        }
        cout << "Initialize Python function successfully."  << endl;
        // Make global lock available to threads
        PyEval_ReleaseThread(PyThreadState_Get());
        cout << "[Python] GIL State check: " << PyGILState_Check() << endl;
    }
    return 0;
}

string invoke(char* hand_str)
{
    if (pFunc == nullptr)
    {
        cout << "Error! Python function has not been initialized yet!"  << endl;
        exit(-1);
    }

    //Convert C++'s string to Python's string.
    PyObject *pArg = Py_BuildValue("(s)", hand_str);
    //Call function;
    PyObject *pResult = PyEval_CallObject(pFunc, pArg);
    if (pResult == nullptr){
        cout << "ERROR calling function!"  << endl;
        exit(-1);
    }
    //Store the return value of the Python function.
    char* re_str;
    PyArg_Parse(pResult, "s", &re_str);
    string s(re_str);

    // To avoid memory leak.
    Py_DecRef(pResult);
    Py_DecRef(pArg);

    return s;
}

void* threadInvoke(void* argv)
{
    PythonThreadLocker locker;
    char hand_str1[] = "6s-3d-Ac-7c-7s-Td-7d";
    string re = invoke(hand_str1);
    cout << "The result is: " << re << endl;
}

int destroy()
{
    cout << "[Python] GIL State check: " << PyGILState_Check() << endl;
    // Ensure all threads have completed
    PyGILState_Ensure();
    // Free resources.
    Py_Finalize();
    cout << "Destroy Python environment successfully."  << endl;
    return 0;
}

int main()
{
    init();

    const int THREAD_NUM = 10;
    pthread_t threadBuf[THREAD_NUM];
    // Simulate creating threads
    for (auto & t : threadBuf)
    {
        pthread_t threadID;
        int ret = pthread_create(&threadID, nullptr, threadInvoke, nullptr);
        if (ret != 0)
        {
            cout << "Pthread_create failed!" << endl;
            break;
        }
        t = threadID;
    }
    // Simulate destroying threads
    for (auto & t : threadBuf)
    {
        pthread_join(t, nullptr);
    }

    destroy();
    return 0;
}


