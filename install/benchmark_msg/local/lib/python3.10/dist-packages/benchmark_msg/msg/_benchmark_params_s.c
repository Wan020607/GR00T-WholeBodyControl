// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from benchmark_msg:msg/BenchmarkParams.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "benchmark_msg/msg/detail/benchmark_params__struct.h"
#include "benchmark_msg/msg/detail/benchmark_params__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool benchmark_msg__msg__benchmark_params__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[52];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("benchmark_msg.msg._benchmark_params.BenchmarkParams", full_classname_dest, 51) == 0);
  }
  benchmark_msg__msg__BenchmarkParams * ros_message = _ros_message;
  {  // enable_adaptative
    PyObject * field = PyObject_GetAttrString(_pymsg, "enable_adaptative");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->enable_adaptative = (Py_True == field);
    Py_DECREF(field);
  }
  {  // full_payload
    PyObject * field = PyObject_GetAttrString(_pymsg, "full_payload");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->full_payload = (Py_True == field);
    Py_DECREF(field);
  }
  {  // mu
    PyObject * field = PyObject_GetAttrString(_pymsg, "mu");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mu = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mu_zone1
    PyObject * field = PyObject_GetAttrString(_pymsg, "mu_zone1");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mu_zone1 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mu_zone2
    PyObject * field = PyObject_GetAttrString(_pymsg, "mu_zone2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mu_zone2 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // mu_zone3
    PyObject * field = PyObject_GetAttrString(_pymsg, "mu_zone3");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->mu_zone3 = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // new_vel_max
    PyObject * field = PyObject_GetAttrString(_pymsg, "new_vel_max");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->new_vel_max = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // new_w_max
    PyObject * field = PyObject_GetAttrString(_pymsg, "new_w_max");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->new_w_max = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // dist_obst
    PyObject * field = PyObject_GetAttrString(_pymsg, "dist_obst");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->dist_obst = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * benchmark_msg__msg__benchmark_params__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of BenchmarkParams */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("benchmark_msg.msg._benchmark_params");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "BenchmarkParams");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  benchmark_msg__msg__BenchmarkParams * ros_message = (benchmark_msg__msg__BenchmarkParams *)raw_ros_message;
  {  // enable_adaptative
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->enable_adaptative ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "enable_adaptative", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // full_payload
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->full_payload ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "full_payload", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mu
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mu);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mu", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mu_zone1
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mu_zone1);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mu_zone1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mu_zone2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mu_zone2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mu_zone2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mu_zone3
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->mu_zone3);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mu_zone3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // new_vel_max
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->new_vel_max);
    {
      int rc = PyObject_SetAttrString(_pymessage, "new_vel_max", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // new_w_max
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->new_w_max);
    {
      int rc = PyObject_SetAttrString(_pymessage, "new_w_max", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dist_obst
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->dist_obst);
    {
      int rc = PyObject_SetAttrString(_pymessage, "dist_obst", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
