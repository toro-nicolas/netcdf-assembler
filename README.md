# 📚 netcdf-assembler 🗺️


## Table of contents 📑
- [Description](https://github.com/toro-nicolas/netcdf-assembler/blob/main/README.md#description-)
- [Usage](https://github.com/toro-nicolas/netcdf-assembler/blob/main/README.md#usage-%EF%B8%8F)
- [Compilation](https://github.com/toro-nicolas/netcdf-assembler/blob/main/README.md#compilation-%EF%B8%8F)
- [Documentation](https://github.com/toro-nicolas/netcdf-assembler/blob/main/README.md#documentation-)
- [Code mandatory](https://github.com/toro-nicolas/netcdf-assembler/blob/main/README.md#code-mandatory-)
- [Contributors](https://github.com/toro-nicolas/netcdf-assembler/blob/main/README.md#contributors-)


## Description 📝
The **netcdf-assembler** is a project from my internship at [Seagnal](https://www.seagnal.fr/), during my **2nd year** in [**EPITECH**](https://www.epitech.eu/) Grand Ecole program.  
Its purpose is to create in [**C++**](https://en.wikipedia.org/wiki/C%2B%2B) a program for assembling multiple [NetCDF](https://en.wikipedia.org/wiki/NetCDF) (and [GRIB](https://en.wikipedia.org/wiki/GRIB)) files into one large NetCDF file.


## Usage ⚔️
You can run netcdf-assembler like this :
```sh
./netcdf-assembler result_file.nc part1.nc part2.nc part3.nc
```

For more information, please see the help section.
```sh
> ./netcdf-assembler --help
Usage: ./netcdf-assembler output_file files

DESCRIPTION
        Assembles multiple NetCDF (and GRIB) files into one large NetCDF file.
```


## Compilation 🛠️
[**NetCDF lib**](https://docs.unidata.ucar.edu/netcdf-c/current/) is required to compile the project.

You can compile the project with this command :
```sh
make
```

If you want to debug the program, you can compile the project with this :
```sh
make debug 
```

If you want clean the project, you can run this command :
```sh
make fclean
```

You can clean and compile the project with ```make re``` and for debugging ```make re_debug```


## Documentation 📚
The documentation is accessible [here](https://toro-nicolas.github.io/netcdf-assembler/html/).

You can generate the documentation with this command :
```sh
make doc
```
You need multiple package for generate them :
- doxygen
- doxygen-latex
- doxygen-doxywizard
- graphviz


## Code mandatory 📦
- You'll need to create a branch where you'll push your code. Once you've completed your tasks on this branch, we'll work together to merge it and check that everything works.
- Every function you add must be documented and code-style with Seagnal's coding style.
- If the github actions don't succeed, then ask yourself some questions
- Each commit will contain ```[+]``` or ```[-]``` or ```[~]``` followed by a message
    - ```[+]``` : Add feature
    - ```[-]``` : Delete feature
    - ```[~]``` : Edit feature

**Of course, in exceptional cases, we may depart from these rules.**


## Contributors 👤
This project was carried out alone by [**Nicolas TORO**](https://github.com/toro-nicolas).
