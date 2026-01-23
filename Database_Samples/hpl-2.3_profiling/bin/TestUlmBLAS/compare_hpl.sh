#!/usr/bin/env bash

# Default filenames (used if no arguments are given)
golden="${1:-testrun_golden}"
faulty="${2:-testrun}"

# Extract only PASSED / FAILED in order
mapfile -t gold_status < <(grep -o "PASSED\|FAILED" "$golden")
mapfile -t fault_status < <(grep -o "PASSED\|FAILED" "$faulty")

if [ "${#gold_status[@]}" -ne "${#fault_status[@]}" ]; then
    echo "ERROR: number of test cases does not match"
    echo "Golden: ${#gold_status[@]}"
    echo "Faulty: ${#fault_status[@]}"
    exit 1
fi

failed=0
passed_correct=0
passed_wrong=0

for ((i=0; i<${#gold_status[@]}; i++)); do
    g=${gold_status[$i]}
    f=${fault_status[$i]}

    if [[ "$f" == "FAILED" ]]; then
        ((failed++))
    else
        if [[ "$g" == "PASSED" ]]; then
            ((passed_correct++))
        else
            ((passed_wrong++))
        fi
    fi
done

total=${#gold_status[@]}

echo "================================"
echo "HPL comparison summary"
echo "================================"
echo "Golden file           : $golden"
echo "Faulty file           : $faulty"
echo "Total test cases      : $total"
echo "FAILED (detected)     : $failed"
echo "PASSED, correct       : $passed_correct"
echo "PASSED, wrong (SDC)   : $passed_wrong"
echo "================================"
