import os.path
import subprocess

compiler_path: str = '../../cmake-build-debug/src/ance.exe'


def compile_project(project_path: str, output_path: str) -> int:
    ance_c = subprocess.run([compiler_path, project_path, output_path], capture_output=True)
    return ance_c.returncode


def run_project(project_path: str, project_name: str) -> (int, str):
    path: str = os.path.join(project_path, 'bin', f'{project_name}.exe')
    project = subprocess.run([path], capture_output=True, encoding='ascii')

    result: int = project.returncode
    output: str = project.stdout

    return result, output
