import tempfile

import ance

with tempfile.TemporaryDirectory() as temp:
    project_path: str = "../ance/basic/test.ance"
    output_path: str = temp

    compile_result: int = ance.compile_project(project_path, output_path)
    if compile_result != 0:
        print("Compilation failed")
        exit(1)

    run_result, run_output = ance.run_project(output_path, "test")
    print(f"Exited with status: {run_result}")
    print(f"Output: {run_output}")
