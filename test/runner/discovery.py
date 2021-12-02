import os
from typing import Optional


class Project:
    def __init__(self, directory_name: str, directory_path: str, project_path: str):
        self.directory_name: str = directory_name
        self.directory_path: str = directory_path
        self.project_path: str = project_path


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
