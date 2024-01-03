# Elephant

- [Description](#description)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

## Description

elephant is command-line tool to manage a to-do list.

Remember: "An elephant never forgets".

## Requirements

- gcc
- make

## Installation

> Warning: Unix-like systems only

```console
$ cd path/to/elephant
$ make all
$ cd build
$ sudo mv ./elephant /usr/local/bin
```

## Usage

### Add a new task

```console
$ elephant add "Task description"
```

### Remove a task

```console
$ elephant rm TASK_ID
```

### List all tasks in to-do list

```console
$ elephant list
```

## Contributing

If you would like to contribute to this project just create a pull request which I will try to review as soon as
possible.