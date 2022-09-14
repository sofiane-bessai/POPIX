# POPIX

> POPIX is a compiler from POP optimized program to language C with fixed point arithmetic.

Project carried out under the supervision of M.Martel (Teacher/researcher) at the Mathematics and Physics laboratory (LAMPS) at the University of Perpignan Via Domitia.

This compiler takes as input a program optimized by POP a precision tuning software (developed by Dorra Ben Khalifa), it converts the program into C language using a fixed point arithmetic library (developed by Hanane Benmaghnia)

## Building

### Dependencies

The project requires `bison` and `flex` installed

### Compiling

To build the project run the provided Makefile:

```shell
make
```

## Running

Run the `popix` executable.

No options implemented for now

Example: 

```shell
popix <algorithm_path>
```

## Licensing

POPIX is under the MIT Licence, specified in `LICENCE`.
The copyright notice in `LICENCE` must be included in all projects using POPIX as well as binaries of POPIX or projects using POPIX.

## Contact

You can contact me at :

Sofiane Bessaï (sofiane.bessai@etudiant.univ-perp.fr)
