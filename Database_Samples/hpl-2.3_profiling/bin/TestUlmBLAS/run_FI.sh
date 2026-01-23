#!/usr/bin/env bash

SETTINGS_FILE="settings.txt"
COMPARE_SCRIPT="./compare_hpl.sh"
GOLDEN_FILE="testrun_golden"
FAULTY_FILE="testrun"

CSV_OUT="results.csv"

# CSV header
echo "fault_id,probability,failed,passed_correct,passed_wrong_sdc" > "$CSV_OUT"

# Read static settings once
seed=$(sed -n '1p' "$SETTINGS_FILE")
cycle=$(sed -n '4p' "$SETTINGS_FILE")
prerun=$(sed -n '5p' "$SETTINGS_FILE")
range_start=$(sed -n '6p' "$SETTINGS_FILE")
range_end=$(sed -n '7p' "$SETTINGS_FILE")

# Loop over fault IDs
for fault_id in {1..21}; do
    # Probability sweep: 0 → 1 step 0.05
    for prob in $(seq 0 0.05 1); do

        # Update settings.txt
        cat > "$SETTINGS_FILE" <<EOF
$seed
$fault_id
$prob
$cycle
$prerun
$range_start
$range_end
EOF

        echo "Running ID=$fault_id, prob=$prob"

        # Run faulty experiment
        mpirun -n 4 xhpl > "$FAULTY_FILE"

        # Run comparison
        summary=$($COMPARE_SCRIPT "$GOLDEN_FILE" "$FAULTY_FILE")

        # Extract numbers from comparison output
        failed=$(echo "$summary" | grep "FAILED (detected)" | awk '{print $NF}')
        passed_correct=$(echo "$summary" | grep "PASSED, correct" | awk '{print $NF}')
        passed_wrong=$(echo "$summary" | grep "PASSED, wrong" | awk '{print $NF}')

        # Append to CSV
        echo "$fault_id,$prob,$failed,$passed_correct,$passed_wrong" >> "$CSV_OUT"

    done
done

echo "Sweep complete. Results written to $CSV_OUT"

