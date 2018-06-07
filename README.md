# AutomaticDifferentiation

This automatic differentiation library was implemented as a senior project in C++ with reverse mode automatic differentiation approach and was tested on various machine learning models.

## Installation

1. Under `AutoDiff` directory,

    if you are working on a linux system run:
    
        > make makefile_linux
        
    if you are working on a MacOS system run:
    
        > make makefile_mac

2. Copy `autodiff.so` file under your workspace directory

3. Import `autodiff.h` file which is under `AutoDiff` directory

## Usage

1. Define your input parameters and your result expression as Var objects.

```cpp
Var a;
Var b;
Var res;
```

2. Assign your input parameters as input by using `makeInput` function.

```cpp
a.makeInput();
b.makeInput();
```

3. Create your actual expression

```cpp
res=(a*b)+3*b;
```

4. Call `result` function to create the computational graph of expression.

```cpp
res.result();
```

5. After that, you can find differential of `res` with respect to inputs with different numerical values. Call `findDiff` function and assign it to a `map<Var*, float>`.

```cpp
a = 5;
b = 3;
map<Var*, float> diffs = res.findDiff();
float diff_wrt_a = diffs[&a];
float diff_wrt_b = diffs[&b];
```
