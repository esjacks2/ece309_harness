#!/bin/bash

#!/bin/bash

echo "Running functional test..."

printf "hello\ncalc 5 + 3\ntesting\nhistory\nexit\n" | ./harness

echo
echo "Running memory leak test..."

printf "hello\ncalc 5 + 3\ntesting\nhistory\nexit\n" | \
valgrind --leak-check=full --error-exitcode=1 ./harness