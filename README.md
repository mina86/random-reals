# Random Reals

This repository accompanies [Generating random
reals](https://mina86.com/2016/random-reals/) article which describes
problems with existing common ways of generating random floating point
numbers given an integer random number generator.

The `src` directory contains benchmarks and tests mentioned in the
article.

The `make-real.h` header file is a stand-alone library which can be
used to construct well-distributed floating point numbers (single and
double precision numbers are supported) from unsigned integers.
