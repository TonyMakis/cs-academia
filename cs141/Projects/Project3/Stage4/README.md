# Stage 4

Extend stage 3 so that it does the same thing, but instead of deleting, substituting or inserting just a single character, do it for up to 3 characters. (You don't need to do the substring search for each of those.) This should be in addition to your output for stage 3:

>Because this can take an incredibly long time for longer words, do this incrementally:

1. Note that if the original word matches you will not do any of this work and the word will be printed out in all capital letters. You should have already checked delete/substitute/insert for one character in the previous stage.  If the word matched at any of those points, it would be printed out in all capital letters and you are done with it.

2. If so far for a word there was no match, next do delete/substitute/insert (in that order) for **two** characters.  If a word matches print it out in all capital letters and you are done with that word.  

3. If you *still* don't have a match, lastly try delete/substitute/insert this time for **three** characters, printing it out in all capital letters if you find a match.  

## My Solution in Action

__**TODO:**__
>This stage is still incomplete => it is still just stage 3. This is the bonus stage, and at the time I decided against completing it. Aside from other things to work on, I felt that the writeup is a little vague.
>
>Checking for two characters for instance could mean that we check for say removing two characters in a row and checking if the that subsequent word is a match, but should we be proceeding to check the removal of every set of two characters *possible* in the word, or simply a check a pair of characters sequentially, iterating through the word once?
>
