#!/bin/bash

OUT="cardozo.h"

append_file() {
    echo "" >> $OUT
    echo "// >>> $1" >> $OUT
    grep -vE '^\s*#pragma once|^\s*#include "' "$1" >> $OUT
}

echo "/* Cardozo - Linear Algebra Library */" > $OUT
echo "#ifndef CARDOZO_H" >> $OUT
echo "#define CARDOZO_H" >> $OUT

echo "#include <vector>" >> $OUT
echo "#include <memory>" >> $OUT
echo "#include <cmath>" >> $OUT
echo "#include <iostream>" >> $OUT
echo "#include <iomanip>" >> $OUT
echo "#include <stdexcept>" >> $OUT
echo "#include <cassert>" >> $OUT
echo "#include <array>" >> $OUT
echo "#include <sstream>" >> $OUT

append_file "headers/dense_cr.h"

# StackCR is independent
append_file "headers/stack_cr.h"

append_file "headers/matrix.h"
append_file "src/matrix.hpp" 

append_file "headers/vector.h"

append_file "headers/algos.h"
append_file "src/algos.hpp" 

append_file "headers/sparse_cr.h"

echo "" >> $OUT
echo "#endif // CARDOZO_H" >> $OUT

echo "" >> $OUT
echo "#ifdef CARDOZO_IMPLEMENTATION" >> $OUT

append_file "src/dense_cr.cpp"

echo "" >> $OUT
echo "#endif // CARDOZO_IMPLEMENTATION" >> $OUT

echo "Done! generated $OUT"
