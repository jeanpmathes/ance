import tempfile

import ance
import discovery


def run_test(test: discovery.Project):
    with tempfile.TemporaryDirectory() as temp:
        output_path: str = temp

        compile_result: int = ance.compile_project(project.project_path, output_path)
        if compile_result != 0:
            print(f"Compilation of {test.directory_name} failed")
            exit(1)

        run_result, run_output = ance.run_project(output_path, "test")
        print(f"Exited with status: {run_result}")
        print(f"Output: {run_output}")


projects: list = discovery.discover_projects("../ance")
print(f"Discovered {len(projects)} test projects")

for project in projects:
    run_test(project)
