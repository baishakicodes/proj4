# Project 4 


## Details

In this project we will re implement some standard unix utilities.  In particular We'll be making clones of 'wc', 'sort', 'uniq', 'shuf', and 'tr'.

## wc 

in other words word count should implement the standard -c, -l, -w, -L options as well as a new -u option. Without any arguments it should print out the line, word, and byte counts, just as the systems wc.

## sort

must sort the lines of the file while worrying about the options -r (sort descending), -u(don't print duplicates), and -f (ignore the case).

## uniq

for this the only options that need to work are -c (show the count before each line), -d (only show duplicated lines), and -u (only print unique lines).

## shuf

This just permutes the lines of the input. each permutation must be equally likely to be selected, should implement the options -e, -i, -n.

## tr

This translates the characters from one set to another set. The only options needed to worry about here are -c , -d. Also the escape sequences '\\', '\n','\t'.
