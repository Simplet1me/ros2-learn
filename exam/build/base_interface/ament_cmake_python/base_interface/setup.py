from setuptools import find_packages
from setuptools import setup

setup(
    name='base_interface',
    version='0.0.0',
    packages=find_packages(
        include=('base_interface', 'base_interface.*')),
)
