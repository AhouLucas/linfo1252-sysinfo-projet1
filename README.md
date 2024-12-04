# linfo1252-sysinfo-projet1
LINFO1252 Systèmes Informatiques - Projet 1


## Build

```
make    # Compile all target
make <target>    # Compile specific target
make clean  # Clean bin/ directory
```

## Structure
```
linfo1252-sysinfo-projet1/
├── csv/                # Directory for CSV output files
├── src/                # Directory for source files
│   ├── philosophe.c    # Source file for the philosopher problem
│   ├── prodcons.c      # Source file for the producer-consumer problem
│   └── ...             # Other source files
├── experiments.sh      # Script to run experiments and collect data
├── plot.py             # Script to plot the collected data
├── Makefile            # Makefile for building the project
└── README.md           # Project documentation
```