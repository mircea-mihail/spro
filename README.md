# spro: Shell-Productivity
Spro, short for Shell Productivity, is a terminal application meant to track your productive hours.

## Installation
It's very important to create a .spro directory in your home directory!

By default, spro will install in /usr/local/bin.
This can be changed by running `$make INSTALL_DIR=custom_dir install`, where `custom_dir` is the directory you want to install in.
```
$ mkdir ~/.spro
$ git clone https://github.com/mircea-mihail/spro
$ cd spro
$ sudo make install
```

To uninstall simply run
```
$ sudo make uninstall
```

## Usage
```
Usage: spro [OPTION]...
Bash tool to track your progress while studying

Options:
    -s, --start <TITLE>           starts the timer and sets the session title as TITLE
    -e, --end                     stops the timer
    -t, --table <DAY>             prints the progress table for the day <DAY> is optional
                                  if no <DAY> is given, the current day is implied
    -w, --week                    does a -t on every file within the past 7 days
                                  and displays a total amount of hours worked during that time
    -d, --delete <LINE> <DAY>     deletes the line in the given file
                                  if no <DAY> is given, the current day is implied
    -b, --balance <DAY>           prints the total progress of a given day (format: 11Jan2022)
                                  if no <DAY> is given, the current day is implied
                                  the current progress (-c) is not taken into account
    -c, --current                 prints the current progress (how long has it been since -s without using -e)

```

## Examples

Start the timer for developing a project:

```
spro -s project development
```

Stop the timer and display the table for today's progress:

```
spro -et
```

Print the table for today's progress:

```
spro -t
```

Print the table for the progress made on the 19th of February 2023:

```
spro -t 19Feb2023
```

Print the progress made during last week:

```
spro -w
```

## Inspiration
The idea for this whole project came from my desire to track my productivity during a term. I would write on a piece of paper the time when I started learning for a particular exam, and the time when I stopped and at the end of the day I would add it all up. As this whole thing would usually be pretty tedious to do and also quite time consuming, I ended up automating this whole process in C++.
