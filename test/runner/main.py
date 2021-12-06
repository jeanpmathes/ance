import tempfile
from typing import Optional

import ance
import discovery


class TestRun:
    def __init__(self, test: discovery.Test, is_valid: bool, compile_output: str, result: Optional[str]):
        self.test = test
        self.is_valid = is_valid
        self.compile_output = compile_output
        self.result = result

    def is_passing(self) -> bool:
        if self.is_valid == self.test.is_valid:
            return self.test.expected_result is None or self.result == self.test.expected_result
        return False

    def create_fail_message(self) -> str:
        if self.is_passing():
            return ""

        if self.is_valid != self.test.is_valid:
            if self.test.is_valid:
                return "expected: valid, actual: invalid"
            else:
                return "expected: invalid, actual: valid"
        else:
            return f"expected: {self.test.expected_result}, actual: {self.result}"

    def print_info(self):
        if self.is_passing():
            return

        if self.is_valid != self.test.is_valid and self.test.is_valid:
            print("\n\nCompile error:\n")
            print(self.compile_output)


def run_test(test: discovery.Test) -> TestRun:
    with tempfile.TemporaryDirectory() as temp:
        output_path: str = temp

        compile_result, compile_output = ance.compile_project(test.project_path, output_path)

        is_valid: bool = (compile_result == 0)
        if not is_valid:
            return TestRun(test, is_valid, compile_output, None)

        run_result, run_output = ance.run_project(output_path, "test")
        return TestRun(test, is_valid, compile_output, run_output)


projects: list = discovery.discover_projects("../ance")
tests: list = discovery.create_tests(projects)

test_runs = []
passing_count: int = 0

for test_case in tests:
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