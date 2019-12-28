/**
 * Created by Nie Tao on 2019/12/23 0023.
 * Steps:
 * (1)Install Python3.6-dev on your ubuntu18.04:
 * $ sudo apt-get install python3.6-dev
 * (2) Compile:
 * $ g++ -I/usr/include/python3.6 py_invoker.cpp -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6m -o py_invoker
 * (3) Run:
 * $ ./py_invoker
 */
#include <string>
#include <Python.h>
#include <iostream>

using namespace std;
// The directory where you put the Python script.
#define PY_DIR "/home/topher/projects/toy-project/python/find_largest/"

PyObject *pFunc;

int init()
{
    if (pFunc == nullptr){
        Py_Initialize();
        // Import this working directory
        PyRun_SimpleString("import sys");
        string append_str = "sys.path.append('";
        append_str.append(PY_DIR).append("')");
        PyRun_SimpleString(append_str.c_str());
        // Import python module.
        PyObject *pModule = PyImport_ImportModule("hand_highlight");
        if (pModule == nullptr) {
            cout << "ERROR importing module!" << endl;
            exit(-1);
        }
        // Get a function of the module.
        pFunc = PyObject_GetAttrString(pModule, "cal_score_to_hot_encoding_str");
        if (pFunc == nullptr) {
            cout << "ERROR getting function!" << endl;
            exit(-1);
        }
        cout << "Initialize Python function successfully."  << endl;
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

int destroy()
{
    // Free resources.
    Py_Finalize();
//    getchar();
    cout << "Destroy Python environment successfully."  << endl;
    return 0;
}

int main()
{
    init();

    char hand_str[] = "AC-AD-QD-TH-KS-JS-2H";
    string re_str = invoke(hand_str);
    cout << "Result: " << re_str << endl;

    destroy();
    return 0;
}


