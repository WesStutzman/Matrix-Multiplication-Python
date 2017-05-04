#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Python.h>

void getListDimentions(PyObject* inputList, int* rows, int* columns)
{
  // Get a instance of a list out of the list
  PyObject* holder = PyList_GetItem(inputList, 0);
  // Save the length of the main list
  *rows = PyList_Size(inputList);
  // Save the length of the list inside the main list
  *columns = PyList_Size(holder);
}

PyObject* getListItem(PyObject* inputList, int row, int column)
{
  PyObject* holder = PyList_GetItem(inputList, row);
  PyObject* returnValue = PyList_GetItem(holder, column);

  if (returnValue == NULL)
  {
    return Py_BuildValue("i", 0);
  }
  return PyList_GetItem(holder, column);
}

void setListItem(PyObject* inputList, int row, int column, PyObject* inputItem)
{
  PyObject* holder = PyList_GetItem(inputList, row);
  PyList_SetItem(holder, column, inputItem);
}

PyObject* test(PyObject* inputList1, PyObject* inputList2)
{
  // Needed Variables            // Needed  Variables
  int i, m, p;                   // For Loop Counters
  int rowSize1, rowSize2;        // Hold Row    Sizes
  int columnSize1, columnSize2;  // Hold Column Sizes
  
  // Get the number of rows and columns from the list's
  getListDimentions(inputList1, &rowSize1, &columnSize1);
  getListDimentions(inputList2, &rowSize2, &columnSize2);

  // Create needed PyObjects
  PyObject* returnList = PyList_New(rowSize1);    // Hold the list to be retruned
  PyObject* zero = Py_BuildValue("i", 0);  // Hold zero to be placed in empty cells

  // Matrix Multiplication
  for(i = 0; i < rowSize1; ++i)
  {
    // PyObject* workingRow = PyList_New(0);
    PyList_SetItem(returnList, i, PyList_New(columnSize2));
    for(m = 0; m < columnSize2; ++m)
    {
      // PyList_Append(workingRow, zero);
      for(p = 0; p < columnSize1; ++p)
      {
        // printf("i: %d\tm: %d\tp: %d\t\n", i, m, p);
        //int index = PyLong_AsLong(PyList_GetItem(workingRow, m));
        int index = PyLong_AsLong(getListItem(returnList, i, m));
        index += PyLong_AsLong(getListItem(inputList1, i, p)) * PyLong_AsLong(getListItem(inputList2, p, m));
        PyObject* endDex = Py_BuildValue("i", index);
        setListItem(returnList, i, m, endDex);
        // PyList_SetItem(workingRow, m, endDex);
      }
    }
    // PyList_Append(returnList, workingRow);
  }
  return returnList;
}

static PyObject* matrixMultiply(PyObject* self, PyObject* args)
{
  PyObject* inputList1;
  PyObject* inputList2;

  if(!PyArg_ParseTuple(args, "OO", &inputList1, &inputList2))
  {
    return NULL;
  }

  PyObject* returnObject = test(inputList1, inputList2);
  //PyObject* returnObject = PyLong_FromLong(returnList);
  return Py_BuildValue("O", returnObject);
}

int* cprintArray(int* inputArray, int x)
{
  int i;
  printf("Made it to Here!!\n");
  for(i=0; i < x; ++i)
  {
    printf("%d: %d\n", i, inputArray[i]);
  }
  return inputArray;
}

static PyObject* printArray(PyObject* self, PyObject* args)
{
  PyObject* inputList;
  int* inputArray;
  int listSize;
  int length;
  int i;
  if(!PyArg_ParseTuple(args, "Oi", &inputList, &length))
  {
    return NULL;
  }

  listSize = PyList_Size(inputList);
  printf("List Size: %d\n", listSize);
  inputArray = (int*)malloc(listSize * sizeof(int));
  for(i = 0; i < listSize; ++i)
  {
    inputArray[i] = PyLong_AsLong(PyList_GetItem(inputList, i));
  }
  return Py_BuildValue("i", cprintArray(inputArray, length));
}

static PyMethodDef myMethods[] = {
  {"printArray", printArray, METH_VARARGS, "Print an array in c"},
  {"matrixMultiply", matrixMultiply, METH_VARARGS, "Multiple Matrix together"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef myModule = {
  PyModuleDef_HEAD_INIT,
  "myModule",
  "Printing in c",
  -1,
  myMethods
};

PyMODINIT_FUNC PyInit_myModule(void)
{
  return PyModule_Create(&myModule);
};
