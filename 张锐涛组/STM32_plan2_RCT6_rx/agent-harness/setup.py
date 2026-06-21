from setuptools import setup, find_namespace_packages

setup(
    name="cli-anything-keil",
    version="1.0.0",
    description="CLI harness for Keil MDK-ARM (Vision) — build, flash, clean STM32 projects from the command line.",
    author="cli-anything",
    python_requires=">=3.8",
    packages=find_namespace_packages(include=["cli_anything.*"]),
    install_requires=[
        "click>=8.0",
    ],
    extras_require={
        "repl": ["click-repl>=0.3.0"],
    },
    entry_points={
        "console_scripts": [
            "cli-anything-keil = cli_anything.keil.keil_cli:main",
        ],
    },
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: Microsoft :: Windows",
        "Topic :: Software Development :: Embedded Systems",
        "Topic :: Scientific/Engineering :: Electronic Design Automation (EDA)",
    ],
)
