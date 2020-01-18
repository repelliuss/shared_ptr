<p align="center">
  <img width="200" height="200" src="https://b.allthepics.net/rpsLogo.png">
</p>

# rps::shared_ptr
> C++ [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr) implementation for fun!

<p align="center">
  <img width="470" height="380" src="https://b.allthepics.net/shared_ptrExample.png">
</p>

## Table of contents
* [General Info](#general-info)
* [Example](#example)
* [Features](#features)
* [Usage](#usage)

## General Info
*rps::shared_ptr* is for educational purposes. It's syntax is mostly identical **prior to C++17**. This library doesn't support aliasing constructor, relations with other types of *rps::shared_ptr*s, relation with unique_ptr and relation with weak_ptr.

## Example
```cpp
using namespace rps;
shared_ptr<int> ptr(new int(7));
shared_ptr<int> array_ptr(new int[10], default_delete<int[]>());
```

## Features
* *rps::shared_ptr* directly uses 8-bit whereas std::shared_ptr uses 16-bit.
* Light-weight, so faster.
* Names are descriptive so it is easier to follow and learn.
* *rps::shared_ptr* uses same syntax as std::shared_ptr to use it quickly.

## Usage
1. Clone this repository to your project.
2. `#include <repelliuss/shared_ptr>` and you are good to go.
