CMPS 3600 OS
Jordan Nicholas
Lab02

Both programs utilize signal handlers, global variables, a sleep function, 
and an infinite loop in order to indefinitely display "Hello World!" followed
by "Turing was right!" once every second. Both programs run infinitely using
a global variable, starting as 0, which flips between 1 and 0 everytime a
message is displayed. The global variable is also used to determine whether
the second message, "Turing was right!", should be displayed, and it should be
displayed after the first message. The only differences between the two 
programs is that the second program has another handler that runs when the
SIGINT signal is sent by pressing CTRL+C while the program is running, and it
also has a global variable counter that increments everytime an alarm is
recieved so that when the SIGINT signal is sent it will display how many
alarms went off.
