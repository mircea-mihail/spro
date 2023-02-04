# spro: Shell-Productivity
spro, short for Shell Productivity, is a terminal application meant to track your productive hours

# Usage
```
Usage: spro [OPTION]...
Bash tool to track your progress while studying

Options:
    -s, --start <TITLE>   starts the timer and sets the session title as TITLE
    -e, --end             stops the timer
    -t, --table <DAY>     prints the progress table for the day <DAY> is optional
                          if no <DAY> is given, the current day is implied
    -b, --balance <DAY>   prints the total progress of a given day (format: 11Jan2022)
                          if no <DAY> is given, the current day is implied
    -c, --current         prints the current progress (how long has it been since -s without using -e)
    -w, --week            does a -t on every file within the past 7 days
                          and displays a total amount of hours worked during that time
```
