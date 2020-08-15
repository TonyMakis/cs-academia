# Project 3: IKEA Words

## Background Info

[IKEA](https://www.ikea.com/us/en/) products are listed in Swedish, even in their American branch dept. stores. It is often interesting how similar the Swedish product names are to words in English that mean something __completely__ different than the tagged object (an example of this being used to comedic and punny ends [here](https://www.youtube.com/watch?v=7T2oje4cYxw)). As someone who is Swedish, this would be completely nonsensical.

## Project Description

We will explore the similarities between the Swedish product names and English words that sound similar to them, although they may bear no resemblance to what the product actually is. More details in each stage of development.

## Project Structure

This is a four-phase development; the stages each have their own writeups, and should be programmed in order. There are three files being provided to us:

- binarySearch.c => basic implementation of a binary search
- IKEAwords.txt => A bunch of IKEA products (1,764) as strings (Swedish, with all characters as letters in American English)
- dictionary.txt => An English dictionary of 40,444 words (longest word is 21 chars.)

## Restrictions for this Project

We were asked to utilize binarySearch for certain search operatoins; other than this there weren't any extra requirements :) (This seems like a good idea, since the strings are sorted alphabetically in each file, so we can keep splitting the dataset in half and searching for a string in O(log(n)) time complexity).

Any further, atomic requirements are described in the different Stages!
