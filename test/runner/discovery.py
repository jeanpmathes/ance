import os
import re
from typing import Optional


class Project:
    def __init__(self, directory_name: str, directory_path: str, project_path: str):
        self.directory_name: str = directory_name
        self.directory_path: str = directory_path
        self.project_path: str = project_path


class Test:
    def __init__(self, test_name: str, project_path: str, is_valid: bool, expected_result: Optional[str]):
        self.test_name: str = test_name
        self.project_path: str = project_path
        self.is_valid: bool = is_valid
        self.expected_result: Optional[str] = expected_result


def discover_projects(root_path: str):
    projects: list = []

    for entry in os.scandir(root_path):
        if entry.is_dir():
            potential_project: Project = create_project(entry)
            if potential_project is not None:
                projects.append(potential_project)

    return projects


def create_project(directory: os.DirEntry) -> Optional[Project]:
    for entry in os.scandir(directory.path):
        if entry.is_file() and os.path.splitext(entry.path)[1] == ".ance":
            return Project(directory.name, directory.path, entry.path)


def create_tests(projects: list) -> list:
    tests: list = []

    for project in projects:
        test: Test = create_test(project)
        if test is not None:
            tests.append(test)

    return tests


def unescape_str(s: str) -> str:
    return s \
        .replace("\\n", "\n") \
        .replace("\\t", "\t") \
        .replace("\\0", "\0")


def create_test(project: Project) -> Optional[Test]:
    code_path: str = os.path.join(project.directory_path, "test.nc")
    if not os.path.exists(code_path):
        return None

    is_valid: bool
    expected_result: Optional[str] = None

    with open(code_path, "r") as code_file:
        idx: int = 0
        for line in code_file:
            if idx == 0:
                if re.match("^// *valid *$", line):
                    is_valid = True
                elif re.match("^// *invalid *$", line):
                    is_valid = False
                else:
                    return None
            elif idx == 1:
                match: re.Match = re.match("^// *o: *\"(?P<result>.*)\" *$", line)
                if match is not None:
                    expected_result = unescape_str(match.group("result").rstrip('\n'))
            else:
                break

            idx += 1

        return Test(project.directory_name, project.project_path, is_valid, expected_result)
