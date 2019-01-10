# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A word with 45 characters. No word is longer than 45 characters in the dictionary.

Pneumonoultramicroscopicsilicovolcanoconiosis - is a word invented by the president of the National Puzzlers' League as a synonym for the disease known as silicosis.
Pneumonoultramicroscopicsilicovolcanoconiosis - is the longest word in the English language published in a dictionary, the Oxford English Dictionary.

## According to its man page, what does `getrusage` do?

getrusage - get resource usage.
int getrusage(int who, struct rusage *usage);
who is RUSAGE_SELF in speller.c - Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members:

           struct rusage {
               struct timeval ru_utime; /* user CPU time used */
               struct timeval ru_stime; /* system CPU time used */
               long   ru_maxrss;        /* maximum resident set size */
               long   ru_ixrss;         /* integral shared memory size */
               long   ru_idrss;         /* integral unshared data size */
               long   ru_isrss;         /* integral unshared stack size */
               long   ru_minflt;        /* page reclaims (soft page faults) */
               long   ru_majflt;        /* page faults (hard page faults) */
               long   ru_nswap;         /* swaps */
               long   ru_inblock;       /* block input operations */
               long   ru_oublock;       /* block output operations */
               long   ru_msgsnd;        /* IPC messages sent */
               long   ru_msgrcv;        /* IPC messages received */
               long   ru_nsignals;      /* signals received */
               long   ru_nvcsw;         /* voluntary context switches */
               long   ru_nivcsw;        /* involuntary context switches */
           };

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To not make copies of variables in stack, preventing stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

We read file character by character until EOF.
Check if it is an alphabetic letter or apostrophe '\'' (not in index 0) so we could build a word. Check so no word is longer than 45 characters.
We ignore words with numbers
Word terminated with nul character '\0' and checked for spelling

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf - read in a formatted string.
A string in C is merely an array of characters. The length of a string is determined by a terminating null character: '\0'.
So fscanf will read "words" containing numbers and other characters which are not allowed in our program.
We assume that in check will only be passed strings with alphabetical characters and/or apostrophes.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To show that these const cannot be modified by the program in any way (word, dictionary)
