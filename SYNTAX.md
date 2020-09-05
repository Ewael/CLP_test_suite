# Syntax

We're going to create a really basic interpreter. The interpreter has a few
commands, that it can run, with a few arguments.

For example:

```sh
greet # Say hello !
greet ; # This works too
exit # Quit the interpreter
print "A_string" # Valid
print "A_string" "Another_one" # Invalid
add 3 4 # Prints 7
print "I'm_gonna_exit_now" ; exit # Valid
greet ; print "exit" ; exit # Valid, greets, prints "exit" and exits
```

## Notes

* Each "program" can only be one line long. Any input with a '\n' will not be
tested nor should induce any kind of behavior.

* Even though it looks disgusting, spaces between a command and a semicolon
are important !

* For now, strings cannot contain spaces. This'll come later :P
