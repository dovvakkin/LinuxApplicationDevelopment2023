GREEN="\033[0;32m"
RESET="\033[0m"

scripts="test/gdb"
gold_output="test/gdb/gold_output"

set -e

gdb --batch --quiet --command "$scripts/test_range_1_12.gdb" --args range \
    | grep @@@ \
    | cut -c 4- > range_1_12.out

cmp range_1_12.out "$gold_output/range_1_12.out"
echo -e "${GREEN}[gdb] test_range_1_12 passed ${RESET}"

gdb --batch --quiet --command "$scripts/test_range_-100_100_3.gdb" --args range \
    | grep @@@ \
    | cut -c 4- > range_-100_100_3.out

cmp range_-100_100_3.out "$gold_output/range_-100_100_3.out"
echo -e "${GREEN}[gdb] test_range_-100_100_3 passed ${RESET}"
