# MyString Project

## Description
`MyString` is an extensible string class implementation designed to demonstrate functionality compatible with Python, with the ability to wrap C++ code using the `pybind11` library. This project provides a `MyString` class that supports numerous overloaded operators and methods for working with strings.

The `MyString` class was developed in C++ and then wrapped for Python usage, allowing the combination of high-performance C++ code with the simplicity and convenience of Python.

This project was developed as an educational exercise for the "Object-Oriented Programming" course at Peter the Great St. Petersburg Polytechnic University (SPbPU) and is not intended for ongoing support or modification.

## Main Features
- Support for constructors to create strings from various data types (C-strings, `std::string`, characters, etc.)
- Overloaded operators:
  - **String concatenation (`+`, `+=`)**
  - **Assignment (`=`)**
  - **Comparison (`==`, `!=`, `<`, `>`, `<=`, `>=`)**
  - **Indexing (`[]`)**
- String manipulation methods:
  - `insert`, `append`, `replace`, `erase`, `substr`, `find`, etc.
- Wrappers for input/output operators `<<` and `>>`, implemented using Python methods (`__str__` and `read_from_string`).
- Automatic string adaptation for both Python and C++ through `pybind11`.

## Requirements
- **C++ Compiler** (e.g., `g++`, `clang++`, or `MSVC` for Windows)
- **Python 3.7+**
- **pybind11**: A library for creating Python bindings for C++ code.
  
  Install `pybind11`:
  ```bash
  pip install pybind11
  ```

## Build and Installation
1. **Clone the repository**:
   ```bash
   git clone ...
   cd mystring_project
   ```

2. **Build and create `.pyd` or `.so` file**:
   
   For Windows with MSVC:
   ```bash
   cl /LD /EHsc /I "C:\path\to\pybind11\include" /I "C:\path\to\Python\Include" my_string_wrapper.cpp my_string.cpp /link /LIBPATH:"C:\path\to\Python\libs" python311.lib /OUT:my_string.pyd
   ```
   
   For Linux/Unix:
   ```bash
   g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) my_string.cpp my_string_wrapper.cpp -o my_string$(python3-config --extension-suffix)
   ```

3. **Run tests**:
   
   After successfully building and creating the `my_string.pyd` or `my_string.so` file, run the tests:
   ```bash
   python testing_lib.py
   ```

## Usage Examples
Once installed successfully, the `MyString` class can be used in Python:

```python
import my_string

# Creating MyString objects
s1 = my_string.MyString("Hello")
s2 = my_string.MyString(" World")
s3 = s1 + s2  # String concatenation

print(s3)  # Expected output: Hello World

# Using the += operator
s1 += "!!!"
print(s1)  # Expected output: Hello!!!

# Finding a substring
index = s1.find("!!!")
print(f"Index of '!!!': {index}")  # Expected output: 5

# Using the read_from_string method to read a string
s4 = my_string.MyString()
s4.read_from_string("Python is awesome")
print(s4)  # Expected output: Python is awesome

# Erasing a substring
s4.erase(6, 9)
print(s4)  # Expected output: Python
```

## Testing
The `unittest` framework is used for testing. The `testing_lib.py` file contains tests to validate all wrapped methods and operators:

### Run tests:
```bash
python testing_lib.py
```

Example test output:
```
test_addition (__main__.TestMyString) ... OK
test_assign_operations (__main__.TestMyString) ... OK
test_find_method (__main__.TestMyString) ... OK
test_insert_and_erase (__main__.TestMyString) ... OK
test_read_from_string (__main__.TestMyString) ... OK
...
```

## Project Structure
```
mystring_project/
├── my_string.h               # C++ header file for MyString class
├── my_string.cpp             # Main implementation of MyString methods
├── my_string_wrapper.cpp     # Wrapper file for pybind11
├── testing_lib.py            # Python tests
├── README.md                 # Project documentation
└── oop1.vcxproj              # Visual Studio project configuration file
```

## License
This project is copyright-free for educational purposes.

