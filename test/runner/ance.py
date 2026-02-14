import os.path
import subprocess

working_directory: str = os.path.abspath('../..')
compiler_path: str = os.path.abspath('../../cmake-build-debug/src/ance.exe')


def compile_project(project_dir_path: str) -> (int, str):
    project_path = os.path.join(project_dir_path, 'test.ance')
    ance_c = subprocess.run([compiler_path, project_path], capture_output=True, encoding='utf-8', cwd=working_directory)
    return ance_c.returncode, ance_c.stdout + ance_c.stderr


def run_project(project_path: str, target_triple: str, project_name: str) -> (int, str):
    path: str = os.path.join(project_path, 'bld', target_triple, 'bin', f'{project_name}.exe')
    project = subprocess.run([path], capture_output=True, encoding='utf-8')

    result: int = project.returncode
    output: str = project.stdout

    return result, output
