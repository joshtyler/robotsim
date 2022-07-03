#!/bin/bash
set -e


if [[ $# -ne 2 ]]; then
	echo "ERROR: Incorrect number of arguments"
	echo "Usage: $0 [path to executable to test] [path to tests directory]"
	exit 1
fi

PROG=$1
TEST_DIR=$2

TMP_FILE=$(mktemp)

TESTS_RUN=0
TESTS_FAILED=0

for F in "${TEST_DIR}"/*.in; do
	TESTS_RUN=$((TESTS_RUN+1))

	# For now ignore return code, just use program output
	"${PROG}" < "${F}" > "${TMP_FILE}" || true

	FILENAME_NOEXT=${F%.*}
	GOLDEN_OUTPUT_FILENAME="${FILENAME_NOEXT}.out"
	FILENAME_NOPATH_NOEXT=${F##*/}
	RETURN_CODE=0
	diff "${TMP_FILE}" "${GOLDEN_OUTPUT_FILENAME}" > /dev/null || RETURN_CODE=$?
	if [[ ${RETURN_CODE} -eq 0 ]]; then
		echo "Test PASSED: ${FILENAME_NOPATH_NOEXT}"
	else
		TESTS_FAILED=$((TESTS_FAILED+1))
		echo "Test FAILED: ${FILENAME_NOPATH_NOEXT}"
		echo "Expected output:"
		cat "${GOLDEN_OUTPUT_FILENAME}"
		echo "Actual output:"
		cat "${TMP_FILE}"
	fi
done

if [[ "${TESTS_FAILED}" -eq 0 ]]; then
	echo "SUCCESS: All (${TESTS_RUN}) tests passed"
else
	echo "FAILURE: ${TESTS_FAILED} of ${TESTS_RUN} tests failed"
	exit 1
fi
