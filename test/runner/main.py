import tempfile
import shutil
import os
import sys
from typing import Optional

import ance
import discovery

COMPILE_VALID = 0
COMPILE_INVALID = 1
COMPILE_ERROR = 100


class TestRun:
    def __init__(self, test: discovery.Test,
                 compile_result: int, compile_output: str,
                 exit_success: bool, result: Optional[str]):
        self.test = test
        self.is_compiling = compile_result != COMPILE_ERROR
        self.is_valid = compile_result == COMPILE_VALID
        self.compile_output = compile_output
        self.exit_success = exit_success
        self.result = result

    def is_passing(self) -> bool:
        if not self.is_compiling:
            return False

        if self.is_valid == self.test.is_valid:
            if self.is_valid and not self.exit_success:
                return False
            return self.test.expected_result is None or self.result == self.test.expected_result
        return False

    def create_fail_message(self) -> str:
        if self.is_passing():
            return ""

        if not self.is_compiling:
            return "unexpected compiler behaviour"

        if self.is_valid != self.test.is_valid:
            if self.test.is_valid:
                return "expected: valid, actual: invalid"
            else:
                return "expected: invalid, actual: valid"
        else:
            if not self.exit_success:
                return "exit code indicates failure"

            return f"expected: {self.test.expected_result}, actual: {self.result}"

    def print_info(self):
        if self.is_passing() or not self.is_compiling:
            return

        if self.is_valid != self.test.is_valid and self.test.is_valid:
            print("\n\nCompile error:\n")
            print(self.compile_output)


if len(sys.argv) != 2:
    print("Expected target triple as argument")
    exit(1)

target_triple = sys.argv[1]


def run_test(test: discovery.Test) -> TestRun:
    with tempfile.TemporaryDirectory() as temp:
        temp_project_dir: str = os.path.join(temp, test.test_name)
        shutil.copytree(test.project_dir_path, temp_project_dir)

        compile_result, compile_output = ance.compile_project(temp_project_dir)

        if compile_result != COMPILE_VALID and compile_result != COMPILE_INVALID:
            compile_result = COMPILE_ERROR

        if compile_result != COMPILE_VALID:
            return TestRun(test, compile_result, compile_output, False, None)

        run_result, run_output = ance.run_project(temp_project_dir, target_triple, "test")
        return TestRun(test, compile_result, compile_output, run_result == 0, run_output)


projects: list = discovery.discover_projects("../ance")
tests: list = discovery.create_tests(projects)

test_runs = []
passing_count: int = 0

for idx, test_case in enumerate(tests):
    print(f"Running test {test_case.test_name}... ({idx + 1}/{len(tests)})")
    run: TestRun = run_test(test_case)
    test_runs.append(run)

    if run.is_passing():
        passing_count += 1

print("----------- ance test results -----------")
print(f"{passing_count}/{len(tests)} passing")

for run in test_runs:
    if not run.is_passing():
        print(f"{run.test.test_name} failed - {run.create_fail_message()}")
        run.print_info()
