#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "Line.h"

typedef struct
{
    PyObject_HEAD
        // define the attributes of the class
        Line *line;
} Py_Line;

static PyObject *Line_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
static int Line_init(Py_Line *self, PyObject *args, PyObject *kwds);
static void Line_dealloc(Py_Line *self);
static PyObject *Line_solve(Py_Line *self, PyObject *args, PyObject *kwds);
static PyObject *Line_crossed_by(Py_Line *self, PyObject *args);
static PyObject *Line_distance_to(Py_Line *self, PyObject *args);
static PyObject *Line_intersection(Py_Line *self, PyObject *args);
static PyObject *Line_get_points(Py_Line *self, void *closure);
static PyObject *Line_get_m(Py_Line *self, void *closure);
static PyObject *Line_get_b(Py_Line *self, void *closure);
static PyObject *Line_get_p1(Py_Line *self, void *closure);
static PyObject *Line_get_p2(Py_Line *self, void *closure);

/* Line methods */
static PyMethodDef Py_Line_methods[] = {
    {"solve", (PyCFunction)Line_solve, METH_KEYWORDS | METH_VARARGS, "Solve for x or y."},
    {"crossed_by", (PyCFunction)Line_crossed_by, METH_VARARGS, "Check if the line is crossed by a point. return [-1,0,1]."},
    {"distance_to", (PyCFunction)Line_distance_to, METH_VARARGS, "Get the distance to a point."},
    {"intersection", (PyCFunction)Line_intersection, METH_VARARGS, "Get the intersection point of two lines."},
    {"get_points", (PyCFunction)Line_get_points, METH_NOARGS, "Get the two points of the line."},
    {"get_m", (PyCFunction)Line_get_m, METH_NOARGS, "Get the slope of the line."},
    {"get_b", (PyCFunction)Line_get_b, METH_NOARGS, "Get the y-intercept of the line."},
    {"get_p1", (PyCFunction)Line_get_p1, METH_NOARGS, "Get the first point of the line."},
    {"get_p2", (PyCFunction)Line_get_p2, METH_NOARGS, "Get the second point of the line."},
    {NULL} /* Sentinel */
};

/* Line docstring */
static char Py_Line_doc[] = "Line class.";

/* __Str__ method */
static PyObject *Line_str(Py_Line *self)
{
    return PyUnicode_FromFormat(self->line->to_string().c_str());
}

/* Properties */
static PyGetSetDef Py_Line_getseters[] = {
    {"p1", (getter)Line_get_p1, NULL, "First point of the line.", NULL},
    {"p2", (getter)Line_get_p2, NULL, "Second point of the line.", NULL},
    {"m", (getter)Line_get_m, NULL, "Slope of the line.", NULL},
    {"b", (getter)Line_get_b, NULL, "Y-intercept of the line.", NULL},
    {NULL} /* Sentinel */
};

/* Line type definition */
static PyTypeObject Py_LineType = {
    PyVarObject_HEAD_INIT(NULL, 0) "Line", /* tp_name */
    sizeof(Py_Line),                       /* tp_basicsize */
    0,                                     /* tp_itemsize */
    /* methods */
    (destructor)Line_dealloc, /* tp_dealloc */
    0,                        /* tp_print */
    0,                        /* tp_getattr */
    0,                        /* tp_setattr */
    0,                        /* tp_reserved */
    0,                        /* tp_repr */
    0,                        /* tp_as_number */
    0,                        /* tp_as_sequence */
    0,                        /* tp_as_mapping */
    0,                        /* tp_hash */
    0,                        /* tp_call */
    (reprfunc)Line_str,       /* tp_str */
    0,                        /* tp_getattro */
    0,                        /* tp_setattro */
    0,                        /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,       /* tp_flags */
    Py_Line_doc,              /* tp_doc */
    0,                        /* tp_traverse */
    0,                        /* tp_clear */
    0,                        /* tp_richcompare */
    0,                        /* tp_weaklistoffset */
    0,                        /* tp_iter */
    0,                        /* tp_iternext */
    Py_Line_methods,          /* tp_methods */
    0,                        /* tp_members */
    Py_Line_getseters,        /* tp_getset */
    0,                        /* tp_base */
    0,                        /* tp_dict */
    0,                        /* tp_descr_get */
    0,                        /* tp_descr_set */
    0,                        /* tp_dictoffset */
    (initproc)Line_init,      /* tp_init */
    0,                        /* tp_alloc */
    Line_new,                 /* tp_new */
};

static PyObject *Line_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    Py_Line *self;
    self = (Py_Line *)type->tp_alloc(type, 0);
    return (PyObject *)self;
}

static int Line_init(Py_Line *self, PyObject *args, PyObject *kwds)
{
    // arugments validation
    // check only either {p1, p2} or {m, b} in kwds
    if (kwds == NULL || PyDict_Size(kwds) != 2)
    {
        PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use {p1, p2} or {m, b}.\n for example: Line(p1=(1,2), p2=(3,4)) or Line(m=1, b=2)");
        return -1;
    }
    // if p1 and p2 exist in kwds
    if (PyDict_Contains(kwds, PyUnicode_FromString("p1")) && PyDict_Contains(kwds, PyUnicode_FromString("p2")))
    {
        // get p1 and p2
        PyObject *p1_obj = PyDict_GetItem(kwds, PyUnicode_FromString("p1"));
        PyObject *p2_obj = PyDict_GetItem(kwds, PyUnicode_FromString("p2"));
        // // check if p1 and p2 are iterable
        // if (!PySequence_Check(p1_obj) || !PySequence_Check(p2_obj))
        // {
        //     PyErr_SetString(PyExc_ValueError, "Two points must be iterable.");
        //     return -1;
        // }
        // // check if p1 and p2 are of length 2
        // if (PySequence_Length(p1_obj) != 2 || PySequence_Length(p2_obj) != 2)
        // {
        //     PyErr_SetString(PyExc_ValueError, "Two points must be of length 2.");
        //     return -1;
        // }

        // get p1 and p2
        double p1[2] = {PyFloat_AsDouble(PySequence_GetItem(p1_obj, 0)), PyFloat_AsDouble(PySequence_GetItem(p1_obj, 1))};
        double p2[2] = {PyFloat_AsDouble(PySequence_GetItem(p2_obj, 0)), PyFloat_AsDouble(PySequence_GetItem(p2_obj, 1))};
        // create line
        self->line = new Line(p1, p2);
        return 0;
    }
    // if m and b exist in kwds
    if (PyDict_Contains(kwds, PyUnicode_FromString("m")) && PyDict_Contains(kwds, PyUnicode_FromString("b")))
    {
        // get m and b
        PyObject *m_obj = PyDict_GetItem(kwds, PyUnicode_FromString("m"));
        PyObject *b_obj = PyDict_GetItem(kwds, PyUnicode_FromString("b"));

        // get m and b
        double m = PyFloat_AsDouble(m_obj);
        double b = PyFloat_AsDouble(b_obj);
        // create line
        self->line = new Line(m, b);
        return 0;
    }
    // if neither p1 and p2 nor m and b exist in kwds
    PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use {p1, p2} or {m, b}.\n for example: Line(p1=(1,2), p2=(3,4)) or Line(m=1, b=2)");
    return -1;
}

static void Line_dealloc(Py_Line *self)
{
    delete self->line;
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Line_solve(Py_Line *self, PyObject *args, PyObject *kwds)
{
    // arugments validation
    // check only either x(number) or y(number) in kwds
    if (kwds == NULL || PyDict_Size(kwds) != 1)
    {
        PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use x(number) or y(number).\n for example: line.solve(x=1) or line.solve(y=1)");
        return NULL;
    }
    // if x exist in kwds
    if (PyDict_Contains(kwds, PyUnicode_FromString("x")))
    {
        // get x
        double x = PyFloat_AsDouble(PyDict_GetItem(kwds, PyUnicode_FromString("x")));
        // solve
        return Py_BuildValue("d", self->line->solve(x));
    }
    // if y exist in kwds
    if (PyDict_Contains(kwds, PyUnicode_FromString("y")))
    {
        // get y
        double y = PyFloat_AsDouble(PyDict_GetItem(kwds, PyUnicode_FromString("y")));
        // solve
        return Py_BuildValue("d", self->line->solve_x(y));
    }
    // if neither x nor y exist in kwds
    PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use x(number) or y(number).\n for example: line.solve(x=1) or line.solve(y=1)");
    return NULL;
}

static PyObject *Line_crossed_by(Py_Line *self, PyObject *args)
{
    // arguments validation
    // iterable[number, number]

    PyObject *p_obj = NULL;
    if (!PyArg_ParseTuple(args, "O", &p_obj))
    {
        PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use iterable[number, number].");
        return NULL;
    }

    // get p
    double p[2] = {PyFloat_AsDouble(PySequence_GetItem(p_obj, 0)), PyFloat_AsDouble(PySequence_GetItem(p_obj, 1))};
    return Py_BuildValue("i", self->line->crossed_by(p));
}

static PyObject *Line_distance_to(Py_Line *self, PyObject *args)
{
    // arguments validation
    // iterable[number, number]

    PyObject *p_obj = NULL;
    if (!PyArg_ParseTuple(args, "O", &p_obj))
    {
        PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use iterable[number, number].");
        return NULL;
    }

    // get p
    double p[2] = {PyFloat_AsDouble(PySequence_GetItem(p_obj, 0)), PyFloat_AsDouble(PySequence_GetItem(p_obj, 1))};
    return Py_BuildValue("d", self->line->distance_to(p));
}

static PyObject *Line_intersection(Py_Line *self, PyObject *args)
{
    // arguments validation
    // Py_Line

    Py_Line *line_obj = NULL;
    if (!PyArg_ParseTuple(args, "O!", &Py_LineType, &line_obj))
    {
        PyErr_SetString(PyExc_ValueError, "Invalid arguments. Use Line.");
        return NULL;
    }
    double p[2];
    if (self->line->intersection((*line_obj->line), p))
    {
        return Py_BuildValue("(dd)", p[0], p[1]);
    }
    else
    {
        Py_RETURN_NONE;
    }
}

static PyObject *Line_get_points(Py_Line *self, void *closure)
{
    double p1[2];
    double p2[2];
    self->line->get_points(p1, p2);
    return Py_BuildValue("((dd)(dd))", p1[0], p1[1], p2[0], p2[1]);
}

static PyObject *Line_get_p1(Py_Line *self, void *closure)
{
    double p1[2];
    self->line->get_p1(p1);
    return Py_BuildValue("(dd)", p1[0], p1[1]);
}

static PyObject *Line_get_p2(Py_Line *self, void *closure)
{
    double p2[2];
    self->line->get_p2(p2);
    return Py_BuildValue("(dd)", p2[0], p2[1]);
}

static PyObject *Line_get_m(Py_Line *self, void *closure)
{
    return Py_BuildValue("d", self->line->get_m());
}

static PyObject *Line_get_b(Py_Line *self, void *closure)
{
    return Py_BuildValue("d", self->line->get_b());
}

/* define module */
static struct PyModuleDef FastLine = {
    PyModuleDef_HEAD_INIT,
    "FastLine",                                                                               /* name of module */
    "FastLine provides line operations like intersection, distance, etc implemented in C++.", /* module documentation, may be NULL */
    -1,                                                                                       /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    NULL};

PyMODINIT_FUNC PyInit_FastLine(void)
{
    PyObject *m;

    m = PyModule_Create(&FastLine);
    if (m == NULL)
        return NULL;

    // PyReady
    if (PyType_Ready(&Py_LineType) < 0)
        return NULL;

    // add Line to module
    Py_INCREF(&Py_LineType);
    PyModule_AddObject(m, "Line", (PyObject *)&Py_LineType);

    return m;
}