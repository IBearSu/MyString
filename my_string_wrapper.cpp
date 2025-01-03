#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include "my_string.h"

namespace py = pybind11;

// Direct call of operators << and >>  is not possible in Python, 
// because Python does not have built-in analogs of these operators for random objects. 
// Instead, Python uses the __str__() method to output a string, 
// and custom methods to read from the string.

// To solve this problem we have to:
// 1) 
// Wrapping for operator<<
std::string my_string_to_str(const MyString& myStr) {
    std::ostringstream oss; // Creating string output stream
    oss << myStr;  // Using MyString friend operator<< to write myStr in string stream
    return oss.str(); // Transform string stream into string and return it
}

// Wrapping for operator>>
void my_string_from_str(MyString& myStr, const std::string& input) {
    std::istringstream iss(input); // Creating string input stream
    iss >> myStr;  // Using MyString friend operator>> to write data to myStr
}

PYBIND11_MODULE(MyString, m) {
    py::class_<MyString>(m, "MyString")
        // Constructors
        .def(py::init<>())  // Default constructor
        .def(py::init<const char*>(), py::arg("string"))  // Constructor from C-string
        .def(py::init<const std::string&>(), py::arg("std_string"))  // Constructor from std::string
        .def(py::init<const char*, size_t>(), py::arg("string"), py::arg("count")) // Constructor from C-string and count
        .def(py::init<size_t, char>(), py::arg("count"), py::arg("symbol"))  // Constructor with count and char symbol
        .def(py::init<const MyString&>(), py::arg("source"))  // Copy constructor

        // Operators
        // Syntaxis explanation:
        // MyString is return type for operator+
        // (MyString::*) is pointer to MyString method
        //.def("method_name", &Class::method_name), & takes pointer to method c_str

        // operator+
        .def("__add__", static_cast<MyString(MyString::*)(const MyString&) const>(&MyString::operator+))  // MyString + MyString
        .def("__add__", static_cast<MyString(MyString::*)(const char*) const>(&MyString::operator+))  // MyString + C-string
        .def("__add__", static_cast<MyString(MyString::*)(const std::string&) const>(&MyString::operator+))  // MyString + std::string

        // operator+=
        .def("__iadd__", static_cast<MyString & (MyString::*)(const char*)>(&MyString::operator+=))  // MyString += C-string
        .def("__iadd__", static_cast<MyString & (MyString::*)(const std::string&)>(&MyString::operator+=))  // MyString += std::string
        .def("__iadd__", static_cast<MyString & (MyString::*)(const MyString&)>(&MyString::operator+=))  // MyString += MyString

        // operator=
        .def("__assign__", static_cast<MyString & (MyString::*)(const char*)>(&MyString::operator=))  // MyString = C-string
        .def("__assign__", static_cast<MyString & (MyString::*)(const MyString&)>(&MyString::operator=))  // MyString = MyString
        .def("__assign__", static_cast<MyString & (MyString::*)(const std::string&)>(&MyString::operator=))  // MyString = std::string
        .def("__assign__", static_cast<MyString & (MyString::*)(char)>(&MyString::operator=))  // MyString = char

        // operator[]
        .def("__getitem__", static_cast<const char& (MyString::*)(size_t) const>(&MyString::operator[])) //const operator[]
        .def("__setitem__", static_cast<char& (MyString::*)(size_t)>(&MyString::operator[]))  // unconst operator[]

        // compare operators
        .def("__eq__", static_cast<bool (MyString::*)(const MyString&) const>(&MyString::operator==))
        .def("__ne__", static_cast<bool (MyString::*)(const MyString&) const>(&MyString::operator!=))
        .def("__lt__", static_cast<bool (MyString::*)(const MyString&) const>(&MyString::operator<))
        .def("__gt__", static_cast<bool (MyString::*)(const MyString&) const>(&MyString::operator>))
        .def("__le__", static_cast<bool (MyString::*)(const MyString&) const>(&MyString::operator<=))
        .def("__ge__", static_cast<bool (MyString::*)(const MyString&) const>(&MyString::operator>=))

        // I/O operators
        .def("__str__", &my_string_to_str)
        .def("read_from_string", &my_string_from_str)


        // functional methods
        .def("c_str", &MyString::c_str)
        .def("data", &MyString::data)
        .def("length", &MyString::length)
        .def("__len__", &MyString::length)
        .def("size", &MyString::size)
        .def("empty", &MyString::empty)
        .def("capacity", &MyString::capacity)
        .def("shrink_to_fit", &MyString::shrink_to_fit)
        .def("erase", &MyString::erase, py::arg("index"), py::arg("count"))
        .def("clear", &MyString::clear)

        .def("insert", static_cast<void (MyString::*)(int, int, char)>(&MyString::insert), 
            py::arg("index"), py::arg("count"), py::arg("symbol"))
        .def("insert", static_cast<void (MyString::*)(int, const char*)>(&MyString::insert), 
            py::arg("index"), py::arg("string"))
        .def("insert", static_cast<void (MyString::*)(int, const char*, int)>(&MyString::insert), 
            py::arg("index"), py::arg("string"), py::arg("count"))
        .def("insert", static_cast<void (MyString::*)(int, const std::string&)>(&MyString::insert), 
            py::arg("index"), py::arg("std_string"))
        .def("insert", static_cast<void (MyString::*)(int, const std::string&, int)>(&MyString::insert), 
            py::arg("index"), py::arg("std_string"), py::arg("count"))  
        
        .def("append", static_cast<void (MyString::*)(int, char)>(&MyString::append), 
            py::arg("count"), py::arg("symbol"))
        .def("append", static_cast<void (MyString::*)(const char*)>(&MyString::append), 
            py::arg("string"))
        .def("append", static_cast<void (MyString::*)(const char*, int, int)>(&MyString::append), 
            py::arg("string"), py::arg("index"), py::arg("count"))
        .def("append", static_cast<void (MyString::*)(const std::string&)>(&MyString::append), 
            py::arg("std_string"))
        .def("append", static_cast<void (MyString::*)(const std::string&, int, int)>(&MyString::append), 
            py::arg("std_string"), py::arg("index"), py::arg("count"))

        .def("replace", static_cast<void (MyString::*)(int, int, const char*)>(&MyString::replace), 
            py::arg("index"), py::arg("count"),py::arg("string"))
        .def("replace", static_cast<void (MyString::*)(int, int, const std::string&)>(&MyString::replace), 
            py::arg("index"), py::arg("count"),py::arg("std_string"))
        
        .def("substr", static_cast<MyString(MyString::*)(int) const>(&MyString::substr),
            py::arg("index"))
        .def("substr", static_cast<MyString(MyString::*)(int, int) const>(&MyString::substr),
            py::arg("index"), py::arg("count"))

        .def("find", static_cast<int (MyString::*)(const char*) const>(&MyString::find),
            py::arg("string"))
        .def("find", static_cast<int (MyString::*)(const char*, int) const>(&MyString::find),
            py::arg("string"), py::arg("start_index"))
        .def("find", static_cast<int (MyString::*)(const std::string&) const>(&MyString::find),
            py::arg("std_string"))
        .def("find", static_cast<int (MyString::*)(const std::string&, int) const>(&MyString::find),
            py::arg("std_string"), py::arg("start_index"))
        ;
}
