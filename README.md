 # 42's Cub3D project


ft_containers is a project where you have to reimplement STL containers such as `map`, `vector`, `stack`.

 ### Project tasks include

 * Creating templated classes for `vector`, `map` and `stack` that contains all the functions and operations of the actual STL containers.
 * Implementing self-balancing binary trees such as AVL tree to speed up key value lookups for `map`.
 * 

### Installation
```
git clone https://github.com/kazemsami/ft_containers.git
```
```
$ cd ft_containers
$ make
```
#### If for example you have already built the progam and would like to run it on a docker container
`$ make re` which will force clean all files and redo the build.

### Usage
`$ ./ft_containers`
#### To compare results with the actual STL containers
```
./ft_containers 42 > ft_cont && ./std_containers 42 > std_cont && diff ft_cont std_cont
```
