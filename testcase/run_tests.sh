#!/bin/bash
# BSQ test runner — compares actual output to expected for each test case

BSQ=../bsq
PASS=0
FAIL=0
BUG=0

run_test() {
	local num="$1"
	local desc="$2"
	local expected="$3"
	local file="testcase_${num}.txt"

	actual=$(${BSQ} "${file}" 2>&1)
	if [ "$actual" = "$expected" ]; then
		echo "[PASS] testcase_${num}: ${desc}"
		PASS=$((PASS + 1))
	else
		echo "[FAIL] testcase_${num}: ${desc}"
		echo "  expected: $(echo "$expected" | head -3 | cat -A)"
		echo "  actual:   $(echo "$actual"   | head -3 | cat -A)"
		FAIL=$((FAIL + 1))
	fi
}

cd "$(dirname "$0")"

# --- INVALID / ERROR CASES (expect: "map error") ---
run_test  1  "rows=0 in header"                          "map error"
run_test  2  "negative rows in header (-1)"              "map error"
run_test  3  "no number before special chars"            "map error"
run_test  4  "INT_MAX+1 overflow in rows"                "map error"
run_test  5  "huge number overflows to positive int"     "map error"
run_test  6  "only 2 special chars after number (i<3)"   "map error"
run_test  7  "duplicate special chars (obstacle==full)"  "map error"
run_test  8  "all 3 special chars identical"             "map error"
run_test  9  "non-printable char as obstacle"            "map error"
run_test 10  "header says 9 but map has 10 lines"        "map error"
run_test 11  "header says 9 but map has 8 lines"         "map error"
run_test 12  "header says 1 but map has 0 lines"         "map error"
run_test 13  "lines with different lengths"              "map error"
run_test 14  "empty line (length 0) inside map"          "map error"
run_test 15  "invalid char on map (not empty/obstacle)"  "map error"
run_test 16  "empty file"                                "map error"
run_test 17  "file is only a newline"                    "map error"

# --- VALID CASES ---
run_test 18  "1x1 empty cell -> filled with full char"   "x"
run_test 19  "1x1 obstacle -> no square, unchanged"      "o"
run_test 20  "3x3 all empty -> entire 3x3 square"        "$(printf 'xxx\nxxx\nxxx')"
run_test 21  "3x3 all obstacles -> no square, unchanged" "$(printf 'ooo\nooo\nooo')"
run_test 22  "space as empty char"                       "$(printf 'x  \n o \n   ')"
run_test 23  "digit as special char (obstacle='0' full='1')" "$(printf '.11\n011\n...')"
run_test 24  "top-left preference among equal squares"   "$(printf 'xxxxo...\nxxxx....\nxxxx....\nxxxx....')"
run_test 25  "standard example_file.txt"                 "$(printf '.....xxxxxxx...............\n....oxxxxxxx...............\n.....xxxxxxxo..............\n.....xxxxxxx...............\n....oxxxxxxx...............\n.....xxxxxxx...o...........\n.....xxxxxxx...............\n......o..............o.....\n..o.......o................')"

echo ""
echo "Results: ${PASS} passed, ${FAIL} failed"
