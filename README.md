# NGLang
NGLang is a programming language designed for the NGos

## Requirements
> gcc/clang or other CXX compiler that compiles to C++17

# Build
```sh
cmake . -B build
cmake --build build
```
(Are you planning to use a non-general purpose programming language?)

# Syntax

## Creating a Variable
```sh
<type> <name>, <value>
```
### Example
```nglang
int foo, 5
string bar, "I make a variable!"
```
## Looping
```nglang
while <condition> {
  ...code
}
```
### Example
```nglang
int res, 0

while res<10 {
  res += 1
}
```
